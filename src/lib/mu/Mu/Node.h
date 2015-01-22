#ifndef __Mu__Node__h__
#define __Mu__Node__h__
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
#include <Mu/NodeFunc.h>
#include <Mu/Value.h>
#include <Mu/config.h>
#include <pthread.h>
#include <stdarg.h>
#include <stl_ext/block_alloc_arena.h>
#include <string>

namespace Mu {

class Symbol;
class Type;
class Node;
class Thread;

//
//  Using these macros instead of actually calling the functions
//  directly will allow the NodeFunc signature to change without
//  rewriting the code.
//

#ifdef MU_DEPRECATED_MACROS
#define NODE_DECLARAION(NAME,TYPE) void NAME(const Mu::Node&,Mu::Thread&,TYPE*)
#define NODE_DECLARATION(NAME,TYPE) void NAME(const Mu::Node&,Mu::Thread&,TYPE*)
#define NODE_THIS node_
#define NODE_THREAD thread_
#define NODE_IMPLEMENTATION(NAME,TYPE) \
    void NAME(const Mu::Node& NODE_THIS, Mu::Thread& NODE_THREAD, TYPE* ret_)
#define NODE_EVAL() (NODE_THIS.eval(NODE_THREAD))
#define NODE_DATA(X) (static_cast<const Mu::DataNode&>(NODE_THIS)._data.as<X>())
//#define NODE_DATA(X) (static_cast<const Mu::DataNode&>(NODE_THIS)._data._ ## X)
#define NODE_EVAL_VALUE(N,T) ((N)->type()->nodeEval((N),(T)))
#define NODE_NUM_ARGS() (NODE_THIS.numArgs())

#define NODE_ARG(N,T) (Mu::evalNodeFunc<T>(NODE_THIS.argNode(N)->func(), *NODE_THIS.argNode(N), NODE_THREAD))
#define NODE_ARG_OBJECT(N,T) (Mu::evalNodeFunc<T*>(NODE_THIS.argNode(N)->func(), *NODE_THIS.argNode(N), NODE_THREAD))
#define NODE_RETURN(X) return X
#define NODE_ANY_TYPE_ARG(N) NODE_EVAL_VALUE(NODE_THIS.argNode(N), NODE_THREAD)
#endif

//
//  New style macros for declaring interpreted nodes
//
//  Examples:
// 
//  MU_NODE_IMPLEMENTATION(f_plus_s, int)
//  {
//      MU_NODE_DECLARE_ARG(float, arg0, 0);
//      MU_NODE_DECLARE_ARG(StringType::String*, arg1, 1);
//      MU_NODE_RETURN(atof(arg1->c_str()) + arg0);
//  }
//
//      -or-
//
//  MU_NODE_IMPLEMENTATION(f_plus_s, int)
//  {
//      float arg0;
//      StringType::String* arg1;
//      MU_NODE_SET_ARG(arg0, 0);
//      MU_NODE_SET_ARG(arg1, 1);
//      MU_NODE_RETURN(atof(arg1->c_str()) + arg0);
//  }
//
//  In which case arg0 will be of type float and arg1 will be a StringType::String*
//

#define MU_NODE_THIS node_
#define MU_NODE_THREAD thread_
#define MU_NODE_RLOC ret_

#define MU_NODE_DECLARATION(NAME,TYPE) void NAME(const Mu::Node&,Mu::Thread&,TYPE*)
#define MU_NODE_GENERIC_DECLARATION(NAME) void NAME(const Mu::Node&,Mu::Thread&,Pointer)
#define MU_NODE_IMPLEMENTATION(NAME,TYPE) \
    void NAME(const Mu::Node& MU_NODE_THIS, Mu::Thread& MU_NODE_THREAD, TYPE* MU_NODE_RLOC)
#define MU_NODE_GENERIC_IMPLEMENTATION(NAME) \
    void NAME(const Mu::Node& MU_NODE_THIS, Mu::Thread& MU_NODE_THREAD, Pointer MU_NODE_RLOC)

#define MU_NODE_NUM_ARGS (MU_NODE_THIS.numArgs())

#define MU_NODE_DECLARE_ARG(T,V,N) \
    T V; (*MU_NODE_THIS.argNode(N)->func())(*MU_NODE_THIS.argNode(N), MU_NODE_THREAD, &V)

#define MU_NODE_DECLARE_TYPE_ARG(T,V,N) \
    Mu::ValuePointer V = (Mu::ValuePointer)alloca(T->size()); \
    (*MU_NODE_THIS.argNode(N)->func())(*MU_NODE_THIS.argNode(N), MU_NODE_THREAD, V)

#define MU_NODE_SET_ARG(V,N) \
    (*MU_NODE_THIS.argNode(N)->func())(*MU_NODE_THIS.argNode(N), MU_NODE_THREAD, &V)

#define MU_NODE_SET_RETURN(V) \
    (*MU_NODE_RLOC) = V

#define MU_NODE_DATA(X) (static_cast<const Mu::DataNode&>(X).value())

#define MU_NODE_RETURN(X) MU_NODE_SET_RETURN(X); return
#define MU_NODE_EVAL_VALUE(P,N,T) ((N)->type()->nodeEval((P),(N),(T)))
#define MU_NODE_ANY_TYPE_ARG(N) { Value v; MU_NODE_EVAL_VALUE(addressOf(v), MU_NODE_THIS.argNode(N), MU_NODE_THREAD); }


//
//  class Node
//
//  Expression trees are constructed using Nodes. Each node has a
//  function associated with it which returns a Value (see
//  Value.h). In addition, the Node instance indicates which symbol
//  generated it and therefor what its return Value type will be.
//
//  Note-- there are no virtual functions in this class. You can't
//  hold on to data that needs to be destroyed when the node is
//  destroyed.
//

class Node
{
  public:
    MU_GC_STUBBORN_NEW_DELETE

    Node() : _symbol(0), _argv(0), _func(0)		{}
    Node(int nArgs, NodeFunc f, const Symbol* s)	{ init(nArgs,f,s); }
    Node(Node** args, const Symbol* s) : _argv(args), _symbol(s), _func(0) {}
    ~Node();

    void  deleteSelf();

    //
    //	Evaluate and return the i'th argument's Value
    //

    size_t		numArgs() const;
    const Node*		argNode(int i) const { return _argv[i]; }

    Node**              argv() const { return _argv; }
    void                releaseArgv() { _argv = 0; }

    void                eval(Thread& t, ValuePointer p) const
                        { (*_func)(*this,t,p); }

    void                evalArg(int i, Thread &t, ValuePointer p) const
                        { _argv[i]->eval(t, p); }

    //
    //	The Type of the Node's return Value
    //

    const Type*		type() const;

    //
    //	Return the symbol whichgenerated this Node
    //

    const Symbol*	symbol() const { return _symbol; }

    //
    //	Returns a reference to the node function
    //

    NodeFunc		func() const { return _func; }

    void                set(const Symbol* s, NodeFunc f)
                        { _symbol = s; _func = f; }

    //
    //  Unique identifier as a string
    //

    String              mangledId() const;

    //
    //  Mark all in tree as unchanging stubborn objects
    //


    // PUT THIS BACK TO PROTECTED
  public:
    void		init(int,NodeFunc,const Symbol*);
    //void		setArgs(Node*,...);
    void		setArgs(Node**,int);
    void		setArg(Node*,int);

    Node*		argNode(int i) { return _argv[i]; }
    void                markChangeEnd();

  private:
    const Symbol*	_symbol;
    NodeFunc		_func;
    Node**		_argv;		// always null terminated

    friend class NodeAssembler;
    friend class NodeVisitor;
    friend class NodePatch;
    friend class NodeSimplifier;
    friend class Thread;
};


//
//  class AnnotatedNode
//
//  A Node which holds source code information for debugging. This is
//  also the base class for ASTNode which holds pre-interpretable
//  abstract representation of as-of-yet unresolved expressions.
//

class AnnotatedNode : public Node
{
  public:
    MU_GC_NEW_DELETE
    AnnotatedNode();
    AnnotatedNode(int numArgs, NodeFunc F, const Symbol* s,
                  unsigned short linenum,
                  unsigned short charnum,
                  Name file);

    virtual ~AnnotatedNode();

    unsigned short linenum() const { return _line; }
    unsigned short charnum() const { return _char; }
    Name sourceFileName() const { return _sourceFile; }

  private:
    unsigned short _line;
    unsigned short _char;
    Name _sourceFile;
};


//
//  class DataNode
//
//  DataNode is a special type of Node which contans a Value. This
//  Node type is necessary for leaf nodes in the expression tree
//  (constants).
//

class DataNode : public Node
{
  public:
    DataNode() : Node(), _data() { assert(_data._Pointer == 0); }
    DataNode(int numArgs, NodeFunc func, const Symbol *symbol);
    DataNode(Node** args, const Symbol* s);
    ~DataNode() {}

    //
    //	The additional data
    //

    Value		_data;
};

template <class T>
class TypedDataNode : public Node
{
  public:
    TypedDataNode() : Node(), _value() {}
    TypedDataNode(int numArgs, NodeFunc func, const Symbol *symbol) : Node(numArgs,func,symbol), _value()  {}
    TypedDataNode(Node** args, const Symbol* s) : Node(args,s), _value()  {}
    ~TypedDataNode() {}

    T _value;
};

} // namespace Mu

#endif // __Mu__Node__h__
