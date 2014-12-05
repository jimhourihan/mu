#ifndef __Mu__Unresolved__h__
#define __Mu__Unresolved__h__
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
#include <Mu/Symbol.h>
#include <Mu/Type.h>

namespace Mu {

class UnresolvedSymbol : public Symbol
{
public:
    UnresolvedSymbol(Context* context, const char*);
    virtual ~UnresolvedSymbol();
    virtual const Type* nodeReturnType(const Node*) const;
};

class UnresolvedType : public Type
{
  public:
    UnresolvedType(Context* context);

    virtual Object* newObject() const;
    virtual Value   nodeEval(const Node*,Thread &t) const;
    virtual void    nodeEval(void*, const Node*,Thread &t) const;
    virtual void    outputValue(std::ostream&,Value&) const;
};

class UnresolvedCall : public UnresolvedSymbol
{
public:
    UnresolvedCall(Context*);
    virtual ~UnresolvedCall();
};

class UnresolvedCast : public UnresolvedSymbol
{
public:
    UnresolvedCast(Context*);
    virtual ~UnresolvedCast();
};

class UnresolvedConstructor : public UnresolvedSymbol
{
public:
    UnresolvedConstructor(Context*);
    virtual ~UnresolvedConstructor();
};

class UnresolvedReference : public UnresolvedSymbol
{
public:
    UnresolvedReference(Context*);
    virtual ~UnresolvedReference();
};

class UnresolvedDereference : public UnresolvedSymbol
{
public:
    UnresolvedDereference(Context*);
    virtual ~UnresolvedDereference();
};

class UnresolvedMemberReference : public UnresolvedSymbol
{
public:
    UnresolvedMemberReference(Context*);
    virtual ~UnresolvedMemberReference();
};

class UnresolvedMemberCall : public UnresolvedSymbol
{
public:
    UnresolvedMemberCall(Context*);
    virtual ~UnresolvedMemberCall();
};

class UnresolvedStackReference : public UnresolvedSymbol
{
public:
    UnresolvedStackReference(Context*);
    virtual ~UnresolvedStackReference();
};

class UnresolvedStackDereference : public UnresolvedSymbol
{
public:
    UnresolvedStackDereference(Context*);
    virtual ~UnresolvedStackDereference();
};

class UnresolvedDeclaration : public UnresolvedSymbol
{
public:
    UnresolvedDeclaration(Context*);
    virtual ~UnresolvedDeclaration();
};

class UnresolvedStackDeclaration : public UnresolvedDeclaration
{
public:
    UnresolvedStackDeclaration(Context*);
    virtual ~UnresolvedStackDeclaration();
};

class UnresolvedAssignment : public UnresolvedSymbol
{
public:
    UnresolvedAssignment(Context*);
    virtual ~UnresolvedAssignment();
};

} // namespace Mu

#endif // __Mu__Unresolved__h__
