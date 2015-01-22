//
//  Copyright (c) 2010, Jim Hourihan
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
//     * Neither the name of Jim Hourihan nor the names of its
//       contributors may be used to endorse or promote products
//       derived from this software without specific prior written
//       permission.
// 
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
//  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
//  PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//  HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#include "GLRContext.h"
#include "Parse.h"
#include <Mu/Alias.h>
#include <Mu/BaseFunctions.h>
#include <Mu/Context.h>
#include <Mu/SymbolType.h>
#include <Mu/Exception.h>
#include <Mu/Language.h>
#include <Mu/Module.h>
#include <Mu/NilType.h>
#include <Mu/NodeAssembler.h>
#include <Mu/OpaqueType.h>
#include <Mu/Process.h>
#include <Mu/Thread.h>
#include <Mu/TypePattern.h>
#include <fstream>
#include <sstream>
#include <stdarg.h>
#include <stdio.h>

namespace Mu {
using namespace std;

GLRContext::GLRContext(const char *imp, const char *name)
    : MuLangContext(imp, name)
{
}

GLRContext::~GLRContext() {}

TypedValue
GLRContext::evalText(const char *text, 
                        const char *inputName,
                        Process* p,
                        const ModuleList& modules)
{
    if (!p) p = new Process(this);

    istream* saved_istream = _istream;

    istringstream str(text);
    setInput(str);
    NodeAssembler assembler(this, p);
    Thread* thread = assembler.thread();

    for (int i=0; i < modules.size(); i++)
    {
        assembler.pushScope(const_cast<Module*>(modules[i]), false);
    }
    
    CurrentFileScope(this, inputName);

    if (p = GLRParse(inputName, &assembler))
    {
        _istream = saved_istream;

        if (p->rootNode())
        {
            Value v = p->evaluate(thread);

            if (thread->uncaughtException())
            {
                if (Object* exc = thread->exception())
                {
                    throw TypedValue(Value(exc), exc->type());
                }
                else
                {
                    throw TypedValue();
                }
            }
            else
            {
                const Type *type = thread->returnValueType();
                return TypedValue(v, type);
            }
        }
    }
    else
    {
        _istream = saved_istream;
    }

    return TypedValue();
}

TypedValue
GLRContext::evalFile(const char *file, 
                        Process* p,
                        const ModuleList& modules)
{
    bool deleteProcess = false;

    if (!p) 
    {
        p = new Process(this);
        deleteProcess = true;
    }

    istream* saved_istream = _istream;
    ifstream infile(file);

    if (!infile)
    {
        throw StreamOpenFailureException();
    }

    setInput(infile);
    NodeAssembler assembler(this, p);
    Thread* thread = assembler.thread();

    for (int i=0; i < modules.size(); i++)
    {
        assembler.pushScope(const_cast<Module*>(modules[i]), false);
    }

    CurrentFileScope(this, file);
    
    if (p = GLRParse(file, &assembler))
    {
        _istream = saved_istream;

        if (p->rootNode())
        {
            Value v = p->evaluate(thread);

            if (thread->uncaughtException())
            {
                if (Object* exc = thread->exception())
                {
                    throw TypedValue(Value(exc), exc->type());
                }
                else
                {
                    throw TypedValue();
                }
            }
            else
            {
                const Type *type = thread->returnValueType();
                if (deleteProcess) delete p;
                return TypedValue(v, type);
            }
        }
    }
    else
    {
        _istream = saved_istream;
    }

    if (deleteProcess) delete p;
    return TypedValue();
}

Type*
GLRContext::parseType(const char *text, Process* p)
{
    if (!p) p = new Process(this);
    _typeParsingMode = true;
    istream* saved_istream = _istream;

    istringstream str(text);
    setInput(str);
    NodeAssembler assembler(this, p);

    if (p = GLRParse("internal type parser", &assembler))
    {
        _istream = saved_istream;

        if (_parsedType)
        {
            _typeParsingMode = false;
            return _parsedType;
        }
    }

    _istream = saved_istream;
    _typeParsingMode = false;
    return 0;
}


void
GLRContext::parseStream(Process* process, istream& in, const char* inputName)
{
    setInput(in);
    NodeAssembler as(this, process);
    GLRParse(inputName, &as);
}

} // Mu
