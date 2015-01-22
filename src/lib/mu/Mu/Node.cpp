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

#include <Mu/config.h>
#include <Mu/Node.h>
#include <Mu/Symbol.h>
#include <Mu/Type.h>
#include <assert.h>
#include <iostream>
#include <stdio.h>

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

namespace Mu {

static int initialized  = 0;

void
Node::deleteSelf()
{
#if defined(MU_USE_BASE_COLLECTOR) | defined(MU_USE_NO_COLLECTOR)
    if (this)
    {
        if (symbol()->usesDataNode()) delete (DataNode*)this;
        else delete this;
    }
#endif
}

void 
Node::init(int numArgs, NodeFunc func, const Symbol *symbol)
{
    if ( numArgs )
    {
#if defined(MU_USE_BASE_COLLECTOR) || defined(MU_USE_NO_COLLECTOR)
	_argv = new Node*[numArgs+1];
#endif

#ifdef MU_USE_BOEHM_COLLECTOR
        _argv = (Node**)(MU_GC_ALLOC((numArgs+1) * sizeof(Node*)));
#endif

        memset(_argv, 0, sizeof(Node*) * (numArgs+1));
    }
    else
    {
	_argv = 0;
    }

    _symbol    = symbol;
    _func      = func;
}    

Node::~Node()
{
    //assert(_argv != reinterpret_cast<Node**>(MU_DELETED));

    if ( _argv )
    {
	for (Node **arg=_argv; *arg; arg++) 
        {
            Node* n = *arg;
            if (n->_symbol->_datanode) delete (DataNode*)n;
            else delete n;
            *arg = NULL;
        }

#if defined(MU_USE_BASE_COLLECTOR) || defined(MU_USE_NO_COLLECTOR)
        delete [] _argv;
#endif
    }

    //_argv = reinterpret_cast<Node**>(MU_DELETED);
    _argv = NULL;
}


const Type* 
Node::type() const
{
    return _symbol ? _symbol->nodeReturnType(this) : 0;
}

size_t
Node::numArgs() const
{
    if (_argv)
    {
	int count=0;
	for (Node **n=_argv; *n; n++,count++);
	return count;
    }
    else
    {
	return 0;
    }
}

String
Node::mangledId() const
{
    char temp[80];
    snprintf(temp, 80, "n%zx", size_t(this) >> 4);
    return temp;
}

void 
Node::setArgs(Node **args, int numArgs)
{
    for (int i=numArgs;i--;) _argv[i] = args[i];
}

void 
Node::setArg(Node *arg, int index)
{
    _argv[index] = arg;
}


void
Node::markChangeEnd()
{
    if (_argv) for (Node** p = _argv; *p; p++) (*p)->markChangeEnd();
    MU_GC_END_CHANGE_STUBBORN(this);
}

AnnotatedNode::AnnotatedNode()
    : Node(),
      _line(0),
      _char(0),
      _sourceFile()
{
}

AnnotatedNode::AnnotatedNode(int numArgs, NodeFunc F, const Symbol* s,
                             unsigned short linenum,
                             unsigned short charnum,
                             Name file)

    : Node(numArgs, F, s),
      _line(linenum),
      _char(charnum),
      _sourceFile(file)
{
}


AnnotatedNode::~AnnotatedNode() {}

} // namespace Mu

