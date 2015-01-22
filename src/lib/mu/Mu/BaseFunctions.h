#ifndef __Mu__BaseFunctions__h__
#define __Mu__BaseFunctions__h__
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

#include <Mu/Node.h>
#include <Mu/Function.h>

namespace Mu {

class Class;
class Variable;
class LocalVariable;
class GlobalVariable;
class FunctionObject;
class Process;

//
//  BaseFunctions
//
//  These are Functions which implement basic nodes required for
//  evaluation. These may not map to all languages, however, so a
//  variant of these is necessary for any language. For example,
//  BlockNode doesn't return a value so functional languages like Lisp
//  would not need them (Lisp would want progn or prog1, etc).
//
//  When Mu is configured with NodeFunc as a union, the complexity of
//  these functions in increased. For example, SimpleBlock must
//  correctly handle return values from any of the possible function
//  return types. This is not as trivial as it seems because using the
//  NodeFunc union lets the compiler assume things about register
//  allocation and return value location.
//

//
//  class NoOpFunction
//
//  No operation. Returns void.
//

class NoOp : public Function
{
  public:
    NoOp(Context* context, const char *name);
    static MU_NODE_DECLARATION(node,void);
};


//
//  class SimpleBlock
//
//  Evaluates its arguments sequentially and returns void.
//

class SimpleBlock : public Function
{
  public:
    SimpleBlock(Context* context, const char *name);
    virtual NodeFunc func(Node* node=0) const;
    virtual const Type* nodeReturnType(const Node*) const;
};

//
//  class FrameBlock
//
//  Evaluates its arguments sequentially, returns void. FrameBlock
//  also manages local variables which are in its scope. This means it
//  modifies the run-time stack.
//
//  The Node data to the FrameBlock must return an _int
//  value. This will determine the number of automatic variables that
//  are allocated.
//

class FixedFrameBlock : public Function
{
  public:
    FixedFrameBlock(Context* context, const char* name);
    virtual NodeFunc func(Node* node=0) const;
    virtual const Type* nodeReturnType(const Node*) const;
    static MU_NODE_DECLARATION(node,void);
};


//
//  class DynamicCast
//
//  Cast up from a base class to a derived class or from a class to an
//  interface (or interface to a class). Throws a BadDynamicCast
//  exception if it fails.
//

class DynamicCast : public Function
{
  public:
    DynamicCast(Context* context, const char* name);
    virtual const Type*	nodeReturnType(const Node*) const;
    static MU_NODE_DECLARATION(node,Pointer);
};

//
//  class DynamicActivation
//
//  Function activation via a FunctionObject
//

class DynamicActivation : public Function
{
  public:
    DynamicActivation(Context* context, const String& returnType, 
                      const STLVector<String>::Type& args);

    virtual NodeFunc func(Node* node=0) const;
};


//
//  class ReturnFromFunction
//
//  Implements the typical "return" statement
//

class ReturnFromFunction : public Function
{
  public:
    ReturnFromFunction(Context* context, const char* name, bool arg=true);
    virtual const Type* nodeReturnType(const Node*) const;
    virtual NodeFunc func(Node* node=0) const;
};

//
//  class TailFuseReturn
//
//  Perform tail-call optimization.
//

class TailFuseReturn : public Function
{
  public:
    TailFuseReturn(Context* context, const char* name);
    virtual const Type* nodeReturnType(const Node*) const;
    virtual NodeFunc func(Node* node=0) const;
};

//
//  Curry
//
//  Decides how best to curry a function (from the user's standpoint.
//  (uses either partial apply or partial eval)
//

class Curry : public Function
{
  public:
    Curry(Context* context, const char* name);
    virtual ~Curry();
    virtual const Type*	nodeReturnType(const Node*) const;
    static MU_NODE_DECLARATION(node,Pointer);
    static FunctionObject* evaluate(Thread&,
                                    FunctionObject*,
                                    const Function::ArgumentVector&,
                                    const std::vector<bool>&,
                                    bool);
};


class DynamicPartialApplication  : public Function
{
  public:
    DynamicPartialApplication(Context* context, const char* name);
    virtual ~DynamicPartialApplication();
    virtual const Type*	nodeReturnType(const Node*) const;
    static MU_NODE_DECLARATION(node,Pointer);
};


class DynamicPartialEvaluate  : public Function
{
  public:
    DynamicPartialEvaluate(Context* context, const char* name);
    virtual ~DynamicPartialEvaluate();
    virtual const Type*	nodeReturnType(const Node*) const;
    static MU_NODE_DECLARATION(node,Pointer);
};


//
//  Conditional Expression for non-primitive types
//

class NonPrimitiveCondExr : public Function
{
  public:
    NonPrimitiveCondExr(Context* context, const char* name);
    virtual ~NonPrimitiveCondExr();
    virtual const Type*	nodeReturnType(const Node*) const;
    static MU_NODE_DECLARATION(node,Pointer);
};

//
//  Match on VariantType
//

class VariantMatch : public Function
{
  public:
    VariantMatch(Context* context, const char* name);
    virtual ~VariantMatch();
    static MU_NODE_DECLARATION(node,void);

};

//
//  Assign as reference
//

class AssignAsReference : public Function
{
public:
    AssignAsReference(Context*);
    virtual ~AssignAsReference();
    virtual const Type*	nodeReturnType(const Node*) const;
};

//
//  PatternTest
//  See ALSO: VariantTagType::upcast which may jump with PatternFail
//

class PatternTest : public Function
{
  public:
    PatternTest(Context*);
    virtual ~PatternTest();
    static MU_NODE_DECLARATION(node,bool);
};

//
//  BoolPatternTest
//

class BoolPatternTest : public Function
{
  public:
    BoolPatternTest(Context*);
    virtual ~BoolPatternTest();
    static MU_NODE_DECLARATION(node,bool);
};

//
//  Case test
//

class CaseTest : public Function
{
  public:
    CaseTest(Context*);
    virtual ~CaseTest();
    static MU_NODE_DECLARATION(node, bool);
};

//
//  Pattern Block
//
//  Non-case patterns 
//

class PatternBlock : public Function
{
  public:
    PatternBlock(Context* context, const char *name);
    virtual NodeFunc func(Node* node=0) const;
    virtual const Type* nodeReturnType(const Node*) const;
};

//
//  Other Base Functions
//

namespace BaseFunctions {

MU_NODE_DECLARATION(dereference, Pointer);
MU_NODE_DECLARATION(assign, Pointer);
MU_NODE_DECLARATION(eq, bool);
MU_NODE_DECLARATION(neq, bool);
MU_NODE_DECLARATION(print, void);
MU_NODE_DECLARATION(hash, int);
MU_NODE_DECLARATION(unresolved, void);
MU_NODE_DECLARATION(abstract, void);
MU_NODE_DECLARATION(classAllocate, Pointer);
MU_NODE_DECLARATION(objIdent, Pointer);
MU_NODE_GENERIC_DECLARATION(constantAnySize);
MU_NODE_DECLARATION(referenceStack, Pointer);
MU_NODE_GENERIC_DECLARATION(dereferenceStack);
MU_NODE_DECLARATION(referenceGlobal, Pointer);
MU_NODE_GENERIC_DECLARATION(dereferenceGlobal);
MU_NODE_GENERIC_DECLARATION(callMethod);
MU_NODE_GENERIC_DECLARATION(dereferenceClassMember);
MU_NODE_GENERIC_DECLARATION(referenceMember);
MU_NODE_DECLARATION(variantConstructor, Pointer);
MU_NODE_GENERIC_DECLARATION(dynamicActivation);
MU_NODE_GENERIC_DECLARATION(functionActivation);

} // namespace BaseFunctions
} // namespace Mu

#endif // __Mu__BaseFunctions__h__

