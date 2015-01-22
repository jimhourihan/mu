#ifndef __MuParse__AST__
#define __MuParse__AST__
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
//     * Neither the name of Mu nor the names of its
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

#include <Mu/NodeAssembler.h>
#include <iostream>

namespace Mu {
namespace AST {

//
// forward declarations
//

class TypeExpr;

//
//  Types
//

struct Location
{
    int first_line;
    int first_column;
    int last_line;
    int last_column;
};

class ASTNode
{
  public:
    typedef NodeAssembler::NodeList NodeList;

    MU_GC_NEW_DELETE;
    ASTNode(const Location& loc);
    virtual ~ASTNode();

    Location location;
    ASTNode* next;

    bool isTuple : 1;       // temp state during parsing
    bool isSequence : 1;

    ASTNode* append(ASTNode*);

    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
    void printList(std::ostream&, char sep=',') const;
    void printListAnnotated(std::ostream&, char sep=',') const;

    virtual Node* resolve(NodeAssembler&) const;
    virtual Node* resolveInternal(NodeAssembler&) const;

    NodeList nodeListFromASTList(NodeAssembler&, ASTNode*) const;

    static void error(NodeAssembler&, const ASTNode*, const char* msg, ...);

    Node* resolveSymbolConstant(NodeAssembler&, Node*) const;

    Node* errorReturn(NodeAssembler&, const std::string& msg) const;

  private:
    ASTNode()
        : next(0),
          isTuple(false),
          isSequence(false)
        {
            location.first_line = 0;
            location.first_column = 0;
            location.last_line = 0;
            location.last_column = 0;
        }
    friend class MergeNode;
};

//----------------------------------------------------------------------

class Pattern : public ASTNode
{
  public:
    Pattern(const Location& loc) :ASTNode(loc) {}
    Pattern* appendPattern(Pattern* p) { return (Pattern*)append(p); }

    virtual NodeAssembler::Pattern* resolvePattern(NodeAssembler&) const;
};

//
//  X
//

class NamePattern : public Pattern
{
  public:
    NamePattern(const Location& loc, ASTNode* n)
        :Pattern(loc), name(n) {}
    ASTNode* name;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
    virtual NodeAssembler::Pattern* resolvePattern(NodeAssembler&) const;
};

//
//  T.C X
//

class ConstructorPattern : public Pattern
{
  public:
    ConstructorPattern(const Location& loc, ASTNode* cons, ASTNode* n)
        :Pattern(loc), 
         constructor(cons),
         name(n) {}
    ASTNode* name;
    ASTNode* constructor;
    virtual NodeAssembler::Pattern* resolvePattern(NodeAssembler&) const;
};

//
//  Pattern that matches a constant
//

class ConstantPattern : public Pattern
{
  public:
    ConstantPattern(const Location& loc, ASTNode* expr, bool negate=false)
        :Pattern(loc), 
         expression(expr),
         unary_minus(negate) {}
    ASTNode* expression;
    bool unary_minus;
    virtual NodeAssembler::Pattern* resolvePattern(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

//
//  Pattern that matches anything
//

class MatchAnyPattern : public Pattern
{
  public:
    MatchAnyPattern(const Location& loc)
        :Pattern(loc) {}
    virtual NodeAssembler::Pattern* resolvePattern(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
};

//
//  {pattern, ...} or (pattern, ...) or [pattern, ...]
//

class CompoundPattern : public Pattern
{
  public:
    enum Type { Tuple, List, Struct };

    CompoundPattern(const Location& loc, Pattern* pats, Type t)
        :Pattern(loc), patterns(pats) {}
    Type type;
    Pattern* patterns;
    virtual NodeAssembler::Pattern* resolvePattern(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
};

//
//  Cons pattern
//

class ConsPattern : public Pattern
{
  public:
    ConsPattern(const Location& loc, Pattern* h, Pattern* l)
        : Pattern(loc), head(h), list(l) {}
    Pattern* head;
    Pattern* list;
    virtual NodeAssembler::Pattern* resolvePattern(NodeAssembler&) const;
};

//
//  Pattern equality
//

class PatternEquality : public ASTNode
{
  public:
    PatternEquality(const Location& loc, Pattern* p, ASTNode* expr)
        : ASTNode(loc), pattern(p), expression(expr) {}
    Pattern* pattern;
    ASTNode* expression;
    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

//
//  Case pattern used by case expression and statement
//

class CasePattern : public ASTNode
{
  public:
    CasePattern(const Location& loc, Pattern* p, ASTNode* expr)
        : ASTNode(loc), pattern(p), expression(expr) {}
    Pattern* pattern;
    ASTNode* expression;
    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

//----------------------------------------------------------------------

//
//  GLR Merge result
//

class MergeNode : public ASTNode
{
  public:
    MergeNode(ASTNode* a, ASTNode *b)
        : ASTNode(), node0(a), node1(b) {}

    ASTNode* node0;
    ASTNode* node1;

    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

//
//  expr.expr
//

class ScopeOperator : public ASTNode
{
  public:
    ScopeOperator(const Location& loc, ASTNode* l, ASTNode *r)
        : ASTNode(loc), left(l), right(r) {}
    ASTNode* left;
    ASTNode* right;

    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

//
//  reference identifier
//

class RefIdentifier : public ASTNode
{
  public:
    RefIdentifier(const Location& loc, const Name& n)
        : ASTNode(loc), name(n) {}
    Name name;

    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
    virtual Node* resolveInternal(NodeAssembler&) const;
};

//
//  Any constant or nil (token would be MU_NIL)
//

class Constant : public ASTNode
{
  public:
    Constant(const Location& loc, unsigned int token, Value v) 
        : ASTNode(loc), value(v), type(token) {}
    unsigned int type;
    Value value;

    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
    virtual Node* resolveInternal(NodeAssembler&) const;
};


//
//  identifier(expr, ...)
//

class Apply : public ASTNode
{
  public:
    Apply(const Location& l, const Name& n, ASTNode* a)
        : ASTNode(l), name(n), args(a)  {}

    Name name;
    ASTNode* args;

    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
    virtual Node* resolveInternal(NodeAssembler&) const;
};

//
//  expr(expr,...)
//

class ExprApply : public ASTNode
{
  public:
    ExprApply(const Location& l, ASTNode* expr, ASTNode* a)
        : ASTNode(l), expression(expr), args(a) {}

    ASTNode* expression;
    ASTNode* args;

    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
    virtual Node* resolveInternal(NodeAssembler&) const;
};


//
//  expr[expr]
//

class IndexedExpr : public ASTNode
{
  public:
    IndexedExpr(const Location& l, ASTNode* expr, ASTNode* a)
        : ASTNode(l), expression(expr), args(a) {}

    ASTNode* expression;
    ASTNode* args;

    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
    virtual Node* resolveInternal(NodeAssembler&) const;
};

//
//  if expr then expr else expr
//

class ConditionalExpr : public ASTNode
{
  public:
    ConditionalExpr(const Location& l, ASTNode* e1, ASTNode* e2, ASTNode* e3)
        : ASTNode(l), condition(e1), thenexpr(e2), elseexpr(e3) {}
    ASTNode* condition;
    ASTNode* thenexpr;
    ASTNode* elseexpr;

    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
    virtual Node* resolveInternal(NodeAssembler&) const;
};

//
//  [expr, ...]
//

class ListExpr : public ASTNode
{
  public:
    ListExpr(const Location& l, ASTNode* a)
        : ASTNode(l), args(a) {}
    ASTNode* args;

    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
    virtual Node* resolveInternal(NodeAssembler&) const;
};

//
//  (expr, expr, ...)
//

class TupleExpr : public ASTNode
{
  public:
    TupleExpr(const Location& l, ASTNode* a)
        : ASTNode(l), args(a) { isTuple = true; }
    ASTNode* args;

    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
    virtual Node* resolveInternal(NodeAssembler&) const;
};

//
//  expr ; expr ; expr ; ...
//

class SequenceExpr : public ASTNode
{
  public:
    SequenceExpr(const Location& l, ASTNode* a)
        : ASTNode(l), args(a) { isSequence = true; }
    ASTNode* args;

    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
    virtual Node* resolveInternal(NodeAssembler&) const;
};

//
//  let patterns in expression
//

class LetExpr : public ASTNode
{
  public:
    LetExpr(const Location& l, ASTNode* pats, ASTNode* expr)
        : ASTNode(l), assignments(pats), expression(expr) {}

    ASTNode* assignments;
    ASTNode* expression;

    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

//
//  module expression
//  ("require" | "use") scoped_identifier_list
//  | ("require" | "use") scoped_identifier_list in expr
//

class RequireExpr : public ASTNode
{
  public:
    RequireExpr(const Location& l, ASTNode* names, bool use_, ASTNode* expr = 0)
        : ASTNode(l), identifiers(names), use(use_), expression(expr) {}

    bool use;
    ASTNode* identifiers;
    ASTNode* expression;

    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};


//
//  case expr of { P1 -> E1, P2 -> E2, P3 -> E3, _ -> DE }
//

class CaseExpr : public ASTNode
{
  public:
    CaseExpr(const Location& l, ASTNode* expr, ASTNode* pats)
        : ASTNode(l), expression(expr), patterns(pats) {}

    ASTNode* expression;
    ASTNode* patterns;

    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

//
//  type '{' aggregate_initializer_list '}'
//

class AggregateValueExpr : public ASTNode
{
  public:
    AggregateValueExpr(const Location& l, ASTNode* typeValue, ASTNode* initList)
        : ASTNode(l), type(typeValue), list(initList) {}

    ASTNode* type;
    ASTNode* list;

    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

//
//  VariableInitializer
//

class VariableInitializer : public ASTNode
{
  public:
    VariableInitializer(const Location& l, ASTNode* id, ASTNode* expr)
        : ASTNode(l), identifier(id), expression(expr) {}
    ASTNode* identifier;
    ASTNode* expression;

    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

//
//  annotated variable declaration
//

class VariableDeclaration : public ASTNode
{
  public:
    VariableDeclaration(const Location& l, TypeExpr* t, ASTNode* inits)
        : ASTNode(l), type(t), initializers(inits) {}
    TypeExpr* type;
    ASTNode* initializers;

    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

//----------------------------------------------------------------------
//  Type Declarations

class ParamDecl : public ASTNode
{
  public:
    ParamDecl(const Location& l, ASTNode* t, ASTNode* pname, ASTNode* val)
        : ASTNode(l), type(t), name(pname), value(val) {}

    ASTNode* type;
    ASTNode* name;
    ASTNode* value;

    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

class FunctionDecl : public ASTNode
{
  public:
    FunctionDecl(const Location& l,
                 ASTNode* nam,
                 TypeExpr* rtype,
                 ASTNode* params,
                 ASTNode* bod)
        : ASTNode(l),
          name(nam),
          returnType(rtype),
          parameters(params),
          body(bod) {}

    ASTNode* name;
    TypeExpr* returnType;
    ASTNode* parameters;
    ASTNode* body;

    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

//
//  Module Declaration
//

class ModuleDecl : public ASTNode
{
  public:
    ModuleDecl(const Location& l, ASTNode* n, ASTNode* bod)
        : ASTNode(l), name(n), body(bod) {}

    ASTNode* name;
    ASTNode* body;

    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

//----------------------------------------------------------------------
//  Type Level ASTNodes

//
// Base for type expressions
//

class TypeExpr : public ASTNode
{
  public:
    TypeExpr(const Location& l) : ASTNode(l) {}
};


class TypeIdentifier : public TypeExpr
{
  public:
    TypeIdentifier(const Location& l, const Name& n) : TypeExpr(l), name(n) {}
    Name name;

    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

class TupleType : public TypeExpr
{
  public:
    TupleType(const Location& l, TypeExpr* comps) 
        : TypeExpr(l), components(comps) {}
    TypeExpr* components;

    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

class ListType : public TypeExpr
{
  public:
    ListType(const Location& l, TypeExpr* etype) 
        : TypeExpr(l), elementType(etype) {}
    TypeExpr* elementType;

    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

class FuncType : public TypeExpr
{
  public:
    FuncType(const Location& l, TypeExpr* rtype, TypeExpr* atypes) 
        : TypeExpr(l), returnType(rtype), argTypes(atypes) {}
    TypeExpr* returnType;
    TypeExpr* argTypes;

    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

class FixedArrayType : public TypeExpr
{
  public:
    FixedArrayType(const Location& l, TypeExpr* etype, ASTNode* dims)
        : TypeExpr(l), elementType(etype), dimensions(dims) {}

    TypeExpr* elementType;
    ASTNode* dimensions;

    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

class DynamicArrayType : public TypeExpr
{
  public:
    DynamicArrayType(const Location& l, TypeExpr* etype)
        : TypeExpr(l), elementType(etype) {}

    TypeExpr* elementType;

    virtual Node* resolveInternal(NodeAssembler&) const;
    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
};

//----------------------------------------------------------------------

class FieldDecl : public ASTNode
{
  public:
    FieldDecl(const Location& loc, ASTNode* fname, ASTNode* ftype)
        : ASTNode(loc), name(fname), type(ftype) {}

    ASTNode* name;
    ASTNode* type;

    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
    virtual Node* resolveInternal(NodeAssembler&) const;
};

class RecordTypeDecl : public ASTNode
{
  public:
    RecordTypeDecl(const Location& loc, const std::string& rname, ASTNode* f)
        : ASTNode(loc), name(rname), members(f) {}

    std::string name;
    ASTNode* members;

    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
    virtual Node* resolveInternal(NodeAssembler&) const;
};

class ClassTypeDecl : public ASTNode
{
  public:
    ClassTypeDecl(const Location& loc, const std::string& rname, ASTNode* f)
        : ASTNode(loc), name(rname), members(f) {}

    std::string name;
    ASTNode* members;

    virtual void print(std::ostream&) const;
    virtual void printAnnotated(std::ostream&) const;
    virtual Node* resolveInternal(NodeAssembler&) const;
};

} // AST
} // Mu

#endif
