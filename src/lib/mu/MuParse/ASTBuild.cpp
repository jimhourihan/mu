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
#include <iostream>
#include <MuParse/Grammar.h>
#include <MuParse/AST.h>

namespace Mu {
using namespace AST;

MergeNode* 
astMerge(ASTNode* a, ASTNode* b)
{
    return new MergeNode(a, b);
}

ScopeOperator* 
astScopeOp(const YYLTYPE& l, ASTNode* left, ASTNode* right)
{
    return new ScopeOperator( (const Location&)l, left, right);
}

RefIdentifier* 
astRefIdentifier(const YYLTYPE& l, const Name& n)
{
    return new RefIdentifier( (const Location&)l, n);
}

RefIdentifier* 
astRefIdentifier2(const YYLTYPE& l, const char* n, GLRContext* c)
{
    return new RefIdentifier( (const Location&)l, c->internName(n));
}

Constant* 
astConstant(const YYLTYPE& l, unsigned int token, const Value& v)
{
    return new Constant( (const Location&)l, token, v);
}

Apply* 
astApply(const YYLTYPE& l, Name name, ASTNode* args)
{
    return new Apply( (const Location&)l, name, args);
}

Apply* 
astApply2(const YYLTYPE& l, const char* name, ASTNode* args, GLRContext* c)
{
    return new Apply( (const Location&)l, 
                               c->internName(name), 
                               args);
}

ConditionalExpr*
astConditional(const YYLTYPE& l, ASTNode* e1, ASTNode* e2, ASTNode* e3)
{
    return new ConditionalExpr((const Location&)l, e1, e2, e3);
}

TupleExpr*
astTuple(const YYLTYPE& l, ASTNode* a, ASTNode* b)
{
    if (a->isTuple)
    {
        TupleExpr* t = static_cast<TupleExpr*>(a);
        t->args->append(b);
        return t;
    }
    else
    {
        return new TupleExpr((const Location&)l, a->append(b));
    }
}

ASTNode*
astEndTuple(const YYLTYPE& l, ASTNode* e)
{
    e->isTuple = false;
    return e;
}

ListExpr*
astList(const YYLTYPE& l, ASTNode* e)
{
    return new ListExpr((const Location&)l, e);
}

ASTNode*
astSequenceExpr(const YYLTYPE& l, ASTNode* a, ASTNode* b)
{
    if (!a) return b;

    if (a->isSequence)
    {
        SequenceExpr* s = static_cast<SequenceExpr*>(a);
        s->args->append(b);
        return s;
    }
    else
    {
        return new SequenceExpr((const Location&)l, a->append(b));
    }
}

ASTNode* 
astEndSequenceExpr(const YYLTYPE& l, AST::ASTNode* a)
{
    if (a->isSequence)
    {
        a->isSequence = false;
        return a;
    }
    else
    {
        SequenceExpr* s = new SequenceExpr((const Location&)l, a);
        s->isSequence = false;
        return s;
    }
}

ASTNode* 
astExprApply(const YYLTYPE& l, ASTNode* expr, ASTNode* args)
{
    if (RefIdentifier* rid = dynamic_cast<RefIdentifier*>(expr))
    {
        //
        //  Simplify this into an Apply, the expr is just a identifier ref
        //

        return astApply(l, rid->name, args);
    }
    else
    {
        return new ExprApply( (const Location&)l, expr, args);
    }
}

IndexedExpr* 
astIndexedExpr(const YYLTYPE& l, ASTNode* expr, ASTNode* args)
{
    return new IndexedExpr( (const Location&)l, expr, args);
}

RequireExpr*
astRequireExpr(const YYLTYPE& l, ASTNode* nameList, int token, ASTNode* expr)
{
    return new RequireExpr( (const Location&)l, nameList, token == MU_USE, expr);
}

Pattern* 
astNamePattern(const YYLTYPE& l, ASTNode* n)
{
    return new NamePattern( (const Location&)l, n);
}

Pattern* 
astConstructorPattern(const YYLTYPE& l, ASTNode* n, ASTNode* n2)
{
    return new ConstructorPattern( (const Location&)l, n, n2);
}

Pattern* 
astConstantPattern(const YYLTYPE& l, ASTNode* expr, bool negate)
{
    return new ConstantPattern( (const Location&)l, expr, negate);
}

Pattern* 
astMatchAnyPattern(const YYLTYPE& l)
{
    return new MatchAnyPattern( (const Location&)l);
}

Pattern* 
astCompoundPattern(const YYLTYPE& l, Pattern* args, CompoundPattern::Type t)
{
    return new CompoundPattern( (const Location&)l, args, t);
}

Pattern* 
astConsPattern(const YYLTYPE& l, Pattern* head, Pattern* list)
{
    return new ConsPattern( (const Location&)l, head, list);
}

ASTNode* 
astPatternEquality(const YYLTYPE& l, Pattern* p, ASTNode* node)
{
    return new PatternEquality( (const Location&)l, p, node);
}

AST::ASTNode* 
astCasePattern(const YYLTYPE& l, AST::Pattern* p, AST::ASTNode* node)
{
    return new CasePattern( (const Location&)l, p, node);
}

AST::ASTNode* 
astCaseExpr(const YYLTYPE& l, AST::ASTNode* e, AST::ASTNode* pats)
{
    return new CaseExpr( (const Location&)l, e, pats);
}

LetExpr* 
astLetExpr(const YYLTYPE& l, ASTNode* assign, ASTNode* expr)
{
    return new LetExpr( (const Location&)l, assign, expr);
}

VariableDeclaration*
astVarDeclaration(const YYLTYPE& l, ASTNode* t, ASTNode* ids)
{
    return new VariableDeclaration((const Location&)l, static_cast<TypeExpr*>(t), ids);
}

VariableInitializer*
astVarInitializer(const YYLTYPE& l, ASTNode* id, ASTNode* expr)
{
    return new VariableInitializer((const Location&)l, id, expr);
}

AggregateValueExpr* 
astAggregateValueExpr(const YYLTYPE& l, ASTNode* type, ASTNode* elements)
{
    return new AggregateValueExpr((const Location&)l, type, elements);
}

ParamDecl* 
astParamDecl(const YYLTYPE& l, ASTNode* type, ASTNode* name, ASTNode* value)
{
    return new ParamDecl((const Location&)l, type, name, value);
}

FunctionDecl* 
astFuncDecl(const YYLTYPE& l, ASTNode* name, ASTNode* rtype, ASTNode* params, ASTNode* body)
{
    return new FunctionDecl((const Location&)l, name, (TypeExpr*)rtype, params, body);
}

ModuleDecl* 
astModuleDecl(const YYLTYPE& l, ASTNode* name, ASTNode* body)
{
    return new ModuleDecl((const Location&)l, name, body);
}

//----------------------------------------------------------------------

TypeExpr* 
astTypeIdentifier(const YYLTYPE& l, ASTNode* i)
{
    return new TypeIdentifier( (const Location&)l, 
                               static_cast<RefIdentifier*>(i)->name );
}

TypeExpr* 
astTypeTuple(const YYLTYPE& l, ASTNode* args)
{
    if (args->next)
    {
        return new AST::TupleType((const Location&)l, static_cast<TypeExpr*>(args));
    }
    else
    {
        //
        //  This is just (type) not (type,type,...)
        //

        return static_cast<TypeExpr*>(args);
    }
}


TypeExpr* 
astTypeList(const YYLTYPE& l, ASTNode* etype)
{
    return new AST::ListType((const Location&)l, static_cast<TypeExpr*>(etype));
}

TypeExpr* 
astTypeFunction(const YYLTYPE& l, ASTNode* rtype, ASTNode* args)
{
    return new AST::FuncType((const Location&)l, 
                             static_cast<TypeExpr*>(rtype),
                             static_cast<TypeExpr*>(args));
}

TypeExpr* 
astTypeFixedArray(const YYLTYPE& l, ASTNode* etype, ASTNode* args)
{
    return new AST::FixedArrayType((const Location&)l, 
                                   static_cast<TypeExpr*>(etype),
                                   args);
}

TypeExpr*
astIndexedType(const  YYLTYPE& l, ASTNode* etype, ASTNode* args)
{
    if (args == 0)
    {
        //
        //  dynamic array
        //

        return new AST::DynamicArrayType((const Location&)l, static_cast<TypeExpr*>(etype));
    }
    else
    {
        return 0;
    }
}

FieldDecl* 
fieldDecl(const YYLTYPE& l, ASTNode* t, ASTNode* name)
{
    return new FieldDecl( (const Location&)l, name, t );
}

ClassTypeDecl* 
classDecl(const YYLTYPE& l, ASTNode* name, ASTNode* f)
{
    if (RefIdentifier* rid = dynamic_cast<RefIdentifier*>(name))
    {
        return new ClassTypeDecl( (const Location&)l, rid->name, f );
    }
}

RecordTypeDecl* 
recordDecl(const YYLTYPE& l, ASTNode* name, ASTNode* f)
{
    if (RefIdentifier* rid = dynamic_cast<RefIdentifier*>(name))
    {
        return new RecordTypeDecl( (const Location&)l, rid->name, f );
    }
}

} // Mu

