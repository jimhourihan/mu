//
//  Copyright (c) 2013, Jim Hourihan
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
//     * Neither the name of the Mu project nor the names of its
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
#include "InteractiveSession.h"
#include "Parse.h"
#include <Mu/NodeAssembler.h>
#include <Mu/Context.h>
#include <Mu/Process.h>
#include <Mu/Thread.h>
#include <Mu/NodeAssembler.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
using namespace std;

namespace {

int 
getline(char *buffer, int max_size)
{
    int i = 0;

    for (;i < max_size; i++)
    {
	if (!cin.eof() && !cin.fail())
	{
            char c;
	    cin.get(c);
            if (c == '\n')
            {
                buffer[i] = 0;
                return i;
            }
            else
            {
                buffer[i] = c;
            }
	}
	else
	{
	    break;
	}
    }

    if (i)
    {
	if (i != max_size) i--;
	return i;
    }
    else
    {
	return 0;
    }
}

}

namespace Mu {
using namespace std;

InteractiveSession::InteractiveSession()
{
}

void
InteractiveSession::run(Context* context, Process* process, Thread* thread)
{
    char temp[1024];
#ifndef MU_USE_READLINE
    int noReadline = 1;
#endif

    while (1)
    {
        if (feof(stdin)) 
        {
            cout << endl;
            exit(0);
        }

        char* line = 0;

        if (noReadline)
        {
            cout << "mu> " << flush;
            size_t s = getline(temp, 1024);
            if (!s) line = 0;
            else line = temp;
        }
        else
        {
#ifdef MU_USE_READLINE
            line = readline("mu> ");
#endif
        }

        if (!line || !*line) continue;

#ifdef MU_USE_READLINE
        if (!noReadline) add_history(line);
#endif

        string statement(line);
        statement.push_back(';');
        istringstream str(statement);

        context->setInput(str);
        NodeAssembler assembler(context, process);
        assembler.throwOnError(true);

        try
        {
            if (Process *p = Parse("input", &assembler))
            {
                if (p->rootNode())
                {
                    Value v = p->evaluate(thread);
                    const Type *type = thread->returnValueType();
                    
                    if (!thread->uncaughtException() &&
                        type != context->voidType() &&
                        !type->isTypePattern())
                    {
                        type->output(cout);
                        cout << " => ";
                        type->outputValue(cout,v);
                        cout << endl << flush;
                    }
                }
            }
            else
            {
                cout << "nil" << endl;
            }
        }
        catch (...)
        {
            cout << "=> ERROR" << endl;
        }
    }
}

} // Mu

