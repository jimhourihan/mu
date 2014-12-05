//
//  Copyright (c) 2009, Jim Hourihan
//  All rights reserved.
// 
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//     * Redistributions of source code must retain the above
//       copyright notice, this list of conditions and the following
//       disclaimer.
//
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials
//       provided with the distribution.
//
//     * Neither the name of the Jim Hourihan nor the names of its
//       contributors may be used to endorse or promote products
//       derived from this software without specific prior written
//       permission.
// 
//  THIS SOFTWARE IS PROVIDED BY Jim Hourihan ''AS IS'' AND ANY EXPRESS
//  OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL Jim Hourihan BE LIABLE FOR
//  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
//  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
//  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
//

#include <Mu/ClassInstance.h>
#include <Mu/GarbageCollector.h>
#include <Mu/Module.h>
#include <Mu/MachineRep.h>
#include <Mu/Process.h>
#include <Mu/Thread.h>
#include <iostream>
#include <stl_ext/block_alloc_arena.h>
#include <stl_ext/stl_ext_algo.h>

namespace Mu {
using namespace std;
using namespace stl_ext;

const Value
BasicCallEnvironment::call(const Function* F, Function::ArgumentVector& args) const
{
    Thread* athread = _thread ? _thread : _process->newApplicationThread();

    try
    {
        const Value v = _process->call(athread, F, args);
        if (!_thread) _process->releaseApplicationThread(athread);
        return v;
    }
    catch (...)
    {
        if (!_thread) _process->releaseApplicationThread(athread);
        throw;
    }
}

const Value
BasicCallEnvironment::callMethodByName(const char* F, Function::ArgumentVector& args) const
{
    Thread* athread = _thread ? _thread : _process->newApplicationThread();

    try
    {
        const Value v = athread->callMethodByName(F, args, false);
        if (!_thread) _process->releaseApplicationThread(athread);
        return v;
    }
    catch (...)
    {
        if (!_thread) _process->releaseApplicationThread(athread);
        throw;
    }
}

Process::Processes Process::_processes;

Process::Process(Context* context)
    : _rootNode(0),
      _context(context),
      _cbEnv(0)
{
    GarbageCollector::init();       // ok to call many times.
    setVaryingSize(0, 0, 0);
    _processes.push_back(this);
    pthread_mutex_init(&_threadNewMutex, 0);
}

Process::Process(Process* process)
    : _rootNode(process->rootNode()),
      _context(process->context()),
      _globals(process->globals())
{
    GarbageCollector::init();       // ok to call many times.
    setVaryingSize(process->varyingSize(0),
                   process->varyingSize(1),
                   process->varyingSize(2));

    _processes.push_back(this);
    pthread_mutex_init(&_threadNewMutex, 0);
}

Process::~Process()
{
    while (_threads.size())
    {
        _threads.front()->terminate(true);
    }

    for (int i=0; i < _processes.size(); i++)
    {
	if (_processes[i] == this)
        {
            _processes[i] = _processes.back();
            _processes.resize(_processes.size()-1);
        }
    }

    pthread_mutex_destroy(&_threadNewMutex);
}

void                    
Process::setCallEnv(const CallEnvironment* cb)
{
    _cbEnv = cb;
}

const CallEnvironment*  
Process::callEnv() const
{
    if (!_cbEnv) 
    {
        Process* p = const_cast<Process*>(this);
        p->_cbEnv = new BasicCallEnvironment(p, p->newApplicationThread());
    }

    return _cbEnv;
}

const Value
Process::call(Thread *thread,
	      const Function *f,
	      Function::ArgumentVector &args,
	      bool returnArguments)
{
    return thread->call(f, args, returnArguments);
}

const Value
Process::evaluate(Thread* thread)
{
    if (_rootNode)
    {
        thread->run(_rootNode, true);
        _returnValue = thread->returnValue();
    }

    return _returnValue;
}

Thread*
Process::newProcessThread()
{
    pthread_mutex_lock(&_threadNewMutex);
    Thread* thread = 0;

    for (int i=0; i < _processThreads.size(); i++)
    {
        if (!_processThreads[i]->isRunning())
        {
            thread = _processThreads[i];
            break;
        }
    }

    if (!thread)
    {
        Thread* thread = new Thread(this);
        _processThreads.push_back(thread);
        _threads.push_back(thread);
    }

    pthread_mutex_unlock(&_threadNewMutex);
    return thread;
}

Thread*
Process::newApplicationThread()
{
    pthread_mutex_lock(&_threadNewMutex);
    Thread* thread = new Thread(this, true);
    _applicationThreads.push_back(thread);
    _threads.push_back(thread);
    pthread_mutex_unlock(&_threadNewMutex);
    return thread;
}

void
Process::releaseApplicationThread(Thread* t)
{
    delete t;
}

void
Process::removeThread(Thread *t)
{
    pthread_mutex_lock(&_threadNewMutex);

    {
        Threads::iterator i = find(_threads.begin(), _threads.end(), t);
        if (i != _threads.end()) _threads.erase(i);
    }

    if (t->isApplicationThread())
    {
        Threads::iterator i = find(_applicationThreads.begin(), _applicationThreads.end(), t);
        if (i != _applicationThreads.end()) _applicationThreads.erase(i);
    }
    else
    {
        Threads::iterator i = find(_processThreads.begin(), _processThreads.end(), t);
        if (i != _processThreads.end()) _processThreads.erase(i);
    }

    pthread_mutex_unlock(&_threadNewMutex);
}

void
Process::clearNodes()
{
    //_rootNode->deleteSelf(); // NOTE: will leak without a collector
    _rootNode = 0;
}

//----------------------------------------------------------------------

void
Process::suspendAll()
{
    for (int i=0; i < _threads.size(); i++)
    {
        Thread* thread = _threads[i];

        if (pthread_equal(pthread_self(), thread->pthread_id()))
        {
            //
            //  Don't suspend calling thread.
            //

            continue;
        }
        else
        {
            thread->suspend();
        }
    }
}

void
Process::resumeAll()
{
    for (int i=0; i < _threads.size(); i++)
    {
        Thread* thread = _threads[i];

        if (pthread_equal(pthread_self(), thread->pthread_id()))
        {
            //
            //  Don't resume calling thread.
            //

            continue;
        }
        else
        {
            thread->resume();
        }
    }
}

Object*
Process::documentSymbol(const Symbol* s)
{
    SymbolDocumentation::iterator i = _symbolDocs.find(s);
    if (i != _symbolDocs.end()) return (*i).second;

    for (const Symbol* sym = s; sym; sym = sym->scope())
    {
        if (const Module* module = dynamic_cast<const Module*>(sym))
        {
            module->loadDocs(this, context());

            i = _symbolDocs.find(s);
            if (i != _symbolDocs.end()) return (*i).second;
            else return 0;
        }
    }

    return 0;
}

} // namespace Mu
