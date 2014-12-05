#ifndef __Mu__TypePattern__h__
#define __Mu__TypePattern__h__
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

#include <Mu/Type.h>
#include <map>

namespace Mu {

union Value;

//
//  class TypePattern
//
//  A TypePattern is a type which exists to match other types in
//  argument lists or other places in the code where one or more types
//  could contextually make sense.
//
//  See also TypeVariable
//

class TypePattern : public Type
{
  public:
    TypePattern(Context* context, const char *tname);

    virtual Object*     newObject() const;
    virtual Value       nodeEval(const Node*,Thread &t) const;
    virtual void        nodeEval(void*, const Node*,Thread &t) const;
    virtual const Type*	nodeReturnType(const Node*) const;
    virtual void        outputValue(std::ostream&,Value&) const;
    virtual void        argumentAdjust(int &in,int &func) const;

    bool variadic() const { return _variadic; }
    
  protected:
    bool _variadic      : 1;
};

//
//  class MatchAnyThing
//
//  This class is named "?" and like its POSIX regexp cousin it
//  matches any one thing. 
//

class MatchAnyThing : public TypePattern
{
  public:
    MatchAnyThing(Context* context) : TypePattern(context, "?") { }
    virtual MatchResult match(const Type *, Bindings&) const;
};

//
//  class MatchAnyType
//
//  This is type matches an expression (lambda expression or function
//  object) of any type. It will not match a static or dynamic object
//  like a constant or variable.
//

class MatchAnyType : public TypePattern
{
  public:
    MatchAnyType(Context* context) : TypePattern(context, "?type") { }
    virtual MatchResult match(const Type *, Bindings&) const;
};

//
//  class VarArg
//
//  This is one a special class of types which is used primarily for
//  argument matching. In this case "..." as in the C varargs
//  argument. It not only matches anything, it will cause a matching
//  algorithm to repeatedly match anything or all arguments.
//

class VarArg : public TypePattern
{
  public:
    VarArg(Context* context) : TypePattern(context, "?varargs") { _variadic = true; }
    virtual MatchResult match(const Type *, Bindings&) const;
    virtual void argumentAdjust(int&,int&) const;
};

//
//  class OneRepeatedArg
//
//  This is another stand in for a POSIX regexp matching character "+"
//  which means match one or more of the preceding.
//

class OneRepeatedArg : public TypePattern
{
  public:
    OneRepeatedArg(Context* context) : TypePattern(context, "?+") { _variadic = true; }
    virtual MatchResult match(const Type *, Bindings&) const;
    virtual void    argumentAdjust(int&,int&) const;
};


//
//  class TwoRepeatedArg
//
//  Matches one or more 2 arguments repeated. So a,b,??+ looks for
//  functions like: foo(a,b) foo(a,b,a,b) foo(a,b,a,b,a,b) but not
//  foo(a,b,a). There must be at least 2 preceding arguments before
//  this one.
//

class TwoRepeatedArg : public TypePattern
{
  public:
    TwoRepeatedArg(Context* context) : TypePattern(context, "??+") { _variadic = true; }
    virtual MatchResult match(const Type *, Bindings&) const;
    virtual void    argumentAdjust(int&,int&) const;
};

//
//  class MatchAnyClass
//
//  Matches any object whose type is a Class. 
//

class MatchAnyClass : public TypePattern
{
  public:
    MatchAnyClass(Context* context) : TypePattern(context, "?class") { }
    virtual MatchResult match(const Type *, Bindings&) const;
};

//
//  class MatchAnyTuple
//
//  Matches any object that's a tuple
//

class MatchAnyTuple : public TypePattern
{
  public:
    MatchAnyTuple(Context* context) : TypePattern(context, "?tuple") { }
    virtual MatchResult match(const Type *, Bindings&) const;
};

//
//  class MatchAnyClassButNotTuple
//
//  Matches any class that's not a tuple
//

class MatchAnyClassButNotTuple : public TypePattern
{
  public:
    MatchAnyClassButNotTuple(Context* context) : TypePattern(context, "?class_not_tuple") { }
    virtual MatchResult match(const Type *, Bindings&) const;
};

//
//  class MatchAnyObjectButNotTuple
//
//  Matches any object that's not a tuple
//

class MatchAnyObjectButNotTuple : public TypePattern
{
  public:
    MatchAnyObjectButNotTuple(Context* context) : TypePattern(context, "?object_not_tuple") { }
    virtual MatchResult match(const Type *, Bindings&) const;
};

//
//  class MatchAnyClassButNotTupleOrList
//
//  Matches any object that's not a tuple or list
//

class MatchAnyClassButNotTupleOrList : public TypePattern
{
  public:
    MatchAnyClassButNotTupleOrList(Context* context) 
        : TypePattern(context, "?class_not_tuple_or_list") { }
    virtual MatchResult match(const Type *, Bindings&) const;
};

//
//  class MatchAnyInterface
//
//  Matches any object whose type is a Interface. 
//

class MatchAnyInterface : public TypePattern
{
  public:
    MatchAnyInterface(Context* context) : TypePattern(context, "?interface") { }
    virtual MatchResult match(const Type *, Bindings&) const;
};

//
//  class MatchAnyClassOrInterface
//
//  Matches any object whose type is a Class *or* Interface. 
//

class MatchAnyClassOrInterface : public TypePattern
{
  public:
    MatchAnyClassOrInterface(Context* context) : TypePattern(context, "?class_or_interface") { }
    virtual MatchResult match(const Type *, Bindings&) const;
};

//
//  class MatchNonPrimitiveOrNil
//

class MatchNonPrimitiveOrNil : public TypePattern
{
  public:
    MatchNonPrimitiveOrNil(Context* context) : TypePattern(context, "?non_primitive_or_nil") { }
    virtual MatchResult match(const Type *, Bindings&) const;
};

//
//  class MatchAnyReference
//
//  Matches any reference type
//

class MatchAnyReference : public TypePattern
{
  public:
    MatchAnyReference(Context* context) : TypePattern(context, "?reference") { }
    virtual MatchResult match(const Type *, Bindings&) const;
};

//
//  class MatchAnyNonPrimitiveReference
//
//  Matches any non-primitive reference type
//

class MatchAnyNonPrimitiveReference : public TypePattern
{
  public:
    MatchAnyNonPrimitiveReference(Context* context) : TypePattern(context, "?non_primitive_reference") { }
    virtual MatchResult match(const Type *, Bindings&) const;
};

//
//  class MatchAnyFunction
//
//  Matches any function type
//

class MatchAnyFunction : public TypePattern
{
  public:
    MatchAnyFunction(Context* context) : TypePattern(context, "?function") { }
    virtual MatchResult match(const Type *, Bindings&) const;
};

//
//  class MatchAnyVariant
//
//  Matches any variant type
//

class MatchAnyVariant : public TypePattern
{
  public:
    MatchAnyVariant(Context* context) : TypePattern(context, "?variant") { }
    virtual MatchResult match(const Type *, Bindings&) const;
};

//
//  Match any list
//

class MatchList : public TypePattern
{
public:
    MatchList(Context* context) : TypePattern(context, "?list") { }
    virtual MatchResult match(const Type*, Bindings&) const;
};

//
//  Match anything that is represented by a bool
//

class MatchABoolRep : public TypePattern
{
  public:
    MatchABoolRep(Context* context) : TypePattern(context, "?bool_rep") { }
    virtual MatchResult match(const Type*, Bindings&) const;
};

class MatchOpaque : public TypePattern
{
public:
    MatchOpaque(Context* c) : TypePattern(c, "?opaque") { }
    virtual MatchResult match(const Type*, Bindings&) const;
};


} // namespace Mu

#endif // __Mu__TypePattern__h__

