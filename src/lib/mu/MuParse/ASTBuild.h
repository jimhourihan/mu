#ifndef __MuParse__ASTBuild__h__
#define __MuParse__ASTBuild__h__
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
#include <MuParse/AST.h>
#include <MuParse/GrammarDefs.h>

inline const char* str(Mu::Name::Ref n) { return Mu::Name(n).c_str(); }

namespace Mu {

AST::MergeNode* astMerge(AST::ASTNode* a, AST::ASTNode* b);

AST::ScopeOperator* astScopeOp(const YYLTYPE& l, AST::ASTNode* left, AST::ASTNode* right);
AST::RefIdentifier* astRefIdentifier(const YYLTYPE& l, const Name& n);
AST::RefIdentifier* astRefIdentifier2(const YYLTYPE& l, const char* n, GLRContext* c);
AST::Constant* astConstant(const YYLTYPE& l, unsigned int token, const Value& v);
AST::Apply* astApply(const YYLTYPE& l, Name name, AST::ASTNode* args);
AST::Apply* astApply2(const YYLTYPE& l, const char* name, AST::ASTNode* args, GLRContext* c);
AST::ConditionalExpr* astConditional(const YYLTYPE& l, AST::ASTNode* e1, AST::ASTNode* e2, AST::ASTNode* e3);
AST::TupleExpr* astTuple(const YYLTYPE& l, AST::ASTNode* a, AST::ASTNode* b);
AST::ASTNode* astEndTuple(const YYLTYPE& l, AST::ASTNode* a);
AST::ListExpr* astList(const YYLTYPE& l, AST::ASTNode* e);
AST::ASTNode* astSequenceExpr(const YYLTYPE& l, AST::ASTNode* a, AST::ASTNode* b);
AST::ASTNode* astEndSequenceExpr(const YYLTYPE& l, AST::ASTNode* a);
AST::ASTNode* astExprApply(const YYLTYPE& l, AST::ASTNode* expr, AST::ASTNode* args);
AST::IndexedExpr* astIndexedExpr(const YYLTYPE& l, AST::ASTNode* expr, AST::ASTNode* args);
AST::LetExpr* astLetExpr(const YYLTYPE& l, AST::ASTNode* assign, AST::ASTNode* expr = 0);
AST::RequireExpr* astRequireExpr(const YYLTYPE& l, AST::ASTNode* nameList, int token, AST::ASTNode* expr=0);
AST::AggregateValueExpr* astAggregateValueExpr(const YYLTYPE& l, AST::ASTNode* type, AST::ASTNode* elements);
AST::ASTNode* astCaseExpr(const YYLTYPE& l, AST::ASTNode* e, AST::ASTNode* pats);

AST::VariableInitializer* astVarInitializer(const YYLTYPE& l, AST::ASTNode* id, AST::ASTNode* expr);
AST::VariableDeclaration* astVarDeclaration(const YYLTYPE& l, AST::ASTNode* t, AST::ASTNode* ids);

AST::ParamDecl* astParamDecl(const YYLTYPE& l, AST::ASTNode* type, AST::ASTNode* name, AST::ASTNode* value);
AST::FunctionDecl* astFuncDecl(const YYLTYPE& l, AST::ASTNode* name, AST::ASTNode* rtype, AST::ASTNode* params, AST::ASTNode* body);

AST::ModuleDecl* astModuleDecl(const YYLTYPE& l, AST::ASTNode* name, AST::ASTNode* body);

// Patterns

AST::Pattern* astNamePattern(const YYLTYPE& l, AST::ASTNode* n);
AST::Pattern* astConstructorPattern(const YYLTYPE& l, AST::ASTNode* n, AST::ASTNode* n2);
AST::Pattern* astConstantPattern(const YYLTYPE& l, AST::ASTNode* expr, bool negate=false);
AST::Pattern* astMatchAnyPattern(const YYLTYPE& l);
AST::Pattern* astCompoundPattern(const YYLTYPE& l, AST::Pattern* args, AST::CompoundPattern::Type);
AST::Pattern* astConsPattern(const YYLTYPE& l, AST::Pattern* head, AST::Pattern* list);

AST::ASTNode* astPatternEquality(const YYLTYPE& l, AST::Pattern* p, AST::ASTNode* node);
AST::ASTNode* astCasePattern(const YYLTYPE& l, AST::Pattern* p, AST::ASTNode* node);

AST::TypeExpr* astTypeIdentifier(const YYLTYPE& l, AST::ASTNode* ident);
AST::TypeExpr* astTypeTuple(const YYLTYPE& l, AST::ASTNode* args);
AST::TypeExpr* astTypeList(const YYLTYPE& l, AST::ASTNode* elementType);
AST::TypeExpr* astTypeFunction(const YYLTYPE& l, AST::ASTNode* rtype, AST::ASTNode* args);
AST::TypeExpr* astTypeFixedArray(const YYLTYPE& l, AST::ASTNode* etype, AST::ASTNode* args);
AST::TypeExpr* astIndexedType(const YYLTYPE& l, AST::ASTNode* etype, AST::ASTNode* args);


// Type declarations

AST::FieldDecl* fieldDecl(const YYLTYPE& l, AST::ASTNode* t, AST::ASTNode* name);
AST::ClassTypeDecl* classDecl(const YYLTYPE& l, AST::ASTNode* t, AST::ASTNode* name);
AST::RecordTypeDecl* recordDecl(const YYLTYPE& l, AST::ASTNode* t, AST::ASTNode* name);

} // Mu

#endif // __MuParse__ASTBuild__h__
