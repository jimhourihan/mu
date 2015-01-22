/* -*- mode: C++ -*-
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
//----------------------------------------------------------------------
//
//  NOTES:
//
//  The GLR parser cannot have any lexer-parser feedback or shared
//  state because the GLR parser can branch. During the branching no
//  actions are performed, rather they are queued up until the
//  surviving branch is selected or branches are merged.
//
//  To incorporate the existing syntax into this new one, a few areas
//  were identified that involved feedback. In each case the either
//  the ambiguity is allowed to exist in the AST or if possible the
//  ambiguity is resolved with a keyword. For example the type
//  modifiers are no longer "general" in this grammar and are
//  considered keywords.
// 

*/

%code requires {
#define IN_GRAMMAR
#ifdef _MSC_VER
#define NOMINMAX
#endif
struct YYLTYPE;
#include "FlexLexer.h"
#include "ASTBuild.h"
#include <Mu/Environment.h>
#include <Mu/Thread.h>
#include <Mu/Type.h>
#include <iostream>
#include <limits>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stl_ext/stl_ext_algo.h>
#include <string.h>
}

%union
{
    int               _token;
    Mu::int64         _int;
    char              _char;
    double            _float;
    char              _op[4];
    Mu::Name::Ref     _name;
    Mu::AST::ASTNode* _node;
    Mu::AST::Pattern* _pattern;
    Mu::Object*       _object;
}

%code {

using namespace std;
using namespace Mu;

Mu::AST::ASTNode* GLRastmerge (const YYSTYPE&, const YYSTYPE&);
int  MUGLRYYlex(void*, YYLTYPE*, MUGLRYYFlexLexer*);
void GLRParseError(YYLTYPE*, MUGLRYYFlexLexer*, const char *,...);
void GLRModuleLocationError(YYLTYPE*, MUGLRYYFlexLexer*, const char *,...);
void GLRParseWarning(YYLTYPE*, MUGLRYYFlexLexer*, const char *,...);

#define yyFlexLexer MUGLRYYFlexLexer

#define AS (state->assembler())
#define CONTEXT (static_cast<Mu::GLRContext*>(AS->context()))

#ifdef yyerror
#undef yyerror
#endif
#define yyerror GLRParseError
}


//
//  Bison Options
//  -------------
//
//  Make it reentrant (pure) GLR and define a pure parser parameter
//

%glr-parser
%pure-parser
%error-verbose
%parse-param {MUGLRYYFlexLexer* state}
%lex-param   {MUGLRYYFlexLexer* state}

//

%token <_object>        MU_STRINGCONST
%token <_float>         MU_FLOATCONST
%token <_int>           MU_BOOLCONST
%token <_int>           MU_CHARCONST
%token <_int>           MU_INTCONST
%token <_name>          MU_IDENTIFIER
%token <_symbol>        MU_SYMBOL
%token <_symbol>        MU_TYPEMODIFIER
%token <_op>            MU_EQUALS
%token <_op>            MU_GREATEREQUALS
%token <_op>            MU_LESSEQUALS
%token <_op>            MU_LOGICAND
%token <_op>            MU_LOGICOR
%token <_op>            MU_LSHIFT
%token <_op>            MU_NOTEQUALS
%token <_op>            MU_OP_ASSIGN
%token <_op>            MU_EQ
%token <_op>            MU_NEQ
%token <_op>            MU_OP_INC
%token <_op>            MU_OP_SYMASSIGN
%token <_op>            MU_RSHIFT
%token <_token>         MU_KIND_KEY
%token <_token>         MU_TYPE_KEY
%token <_token>         MU_ALIAS
%token <_token>         MU_ARROW
%token <_token>         MU_BREAK
%token <_token>         MU_CASE
%token <_token>         MU_CATCH
%token <_token>         MU_CLASS
%token <_token>         MU_CONST
%token <_token>         MU_CONTINUE
%token <_token>         MU_DO
%token <_token>         MU_DOCUMENTATION
%token <_token>         MU_DOUBLECOLON
%token <_token>         MU_DOUBLEDOT
%token <_token>         MU_ELLIPSIS
%token <_token>         MU_ELSE
%token <_token>         MU_FOR
%token <_token>         MU_FOREACH
%token <_token>         MU_FORINDEX
%token <_token>         MU_FUNCTION
%token <_token>         MU_GLOBAL
%token <_token>         MU_IF
%token <_token>         MU_OF
%token <_token>         MU_IN
%token <_token>         MU_INTERFACE
%token <_token>         MU_LAMBDA
%token <_token>         MU_LET
%token <_token>         MU_METHOD
%token <_token>         MU_MODULE
%token <_token>         MU_NIL
%token <_token>         MU_OPERATOR
%token <_token>         MU_QUADRUPLEDOT
%token <_token>         MU_DOUBLEARROW
%token <_token>         MU_REPEAT
%token <_token>         MU_REQUIRE
%token <_token>         MU_RETURN
%token <_token>         MU_STRUCT
%token <_token>         MU_TEMPLATE
%token <_token>         MU_THEN
%token <_token>         MU_THROW
%token <_token>         MU_TRY
%token <_token>         MU_UNION
%token <_token>         MU_USE
%token <_token>         MU_VAR
%token <_token>         MU_NEW
%token <_token>         MU_WHILE
%token <_token>         MU_YIELD

%type <_node>          type
%type <_node>          type_list
%type <_node>          type_list_opt
%type <_node>          unary_type
%type <_node>          arrow_type
%type <_node>          postfix_type
%type <_node>          primary_type
%type <_node>          kind
%type <_node>          kind_opt
%type <_node>          kind_list
%type <_node>          kind_list_opt
%type <_node>          unary_kind
%type <_node>          postfix_kind
%type <_node>          primary_kind
%type <_node>          dimension_list
%type <_node>          type_parameter
%type <_node>          type_parameter_list
%type <_node>          type_parameter_clause
%type <_node>          variant_constructor
%type <_node>          variant_constructor_list
%type <_node>          variant_type_declaration
%type <_node>          field_declaration
%type <_node>          field_declarations
%type <_node>          field_declaration_list
%type <_node>          record_type_declaration
%type <_node>          class_type_declaration
%type <_node>          type_declaration
%type <_node>          identifier
%type <_node>          aggregate_value
%type <_node>          aggregate_initializer
%type <_node>          aggregate_initializer_list
%type <_node>          aggregate_initializer_block
%type <_node>          scoped_identifier
%type <_node>          scoped_identifier_list
%type <_node>          expression
%type <_node>          value_expression
%type <_node>          constant
%type <_node>          constant_suffix
%type <_node>          application_expression
%type <_node>          postfix_value_expression
%type <_node>          postfix_expression
%type <_node>          primary_expression
%type <_node>          block_expression
%type <_node>          unary_expression
%type <_node>          additive_expression
%type <_node>          multiplicative_expression
%type <_node>          require_expression
%type <_node>          relational_expression
%type <_node>          equality_expression
%type <_node>          tuple_expression
%type <_node>          conditional_expression
%type <_node>          cons_expression
%type <_node>          lambda_expression
%type <_node>          logical_AND_expression
%type <_node>          logical_OR_expression
%type <_node>          expression_sequence
%type <_node>          expression_sequence_let
%type <_node>          expression_sequence_require
%type <_node>          expression_sequence_expression
%type <_node>          expression_sequence_declaration_list
%type <_node>          expression_sequence_declaration
%type <_node>          let_expression
%type <_node>          argument_opt
%type <_node>          argument_opt_list
%type <_node>          argument_list
%type <_node>          list_element_list
%type <_node>          let_pattern
%type <_node>          let_pattern_list
%type <_node>          case_pattern
%type <_node>          case_pattern_list
%type <_node>          variable_declation
%type <_node>          variable_initializer
%type <_node>          variable_initializer_list
%type <_node>          parameter
%type <_node>          parameter_list
%type <_node>          function_declaration
%type <_node>          module_declaration
%type <_pattern>       pattern
%type <_pattern>       pattern_list
%type <_pattern>       cons_pattern
%type <_pattern>       primary_pattern
%type <_token>         comma_opt
%type <_token>         semicolon_opt
%type <_token>         type_operator_declaration
%type <_op>            naked_operator

%start compilation_unit

%%

compilation_unit:

    ':' type                    
    { 
        cout << "result => type";

        Mu::AST::ASTNode* anode = $2;

        if (anode) 
        {
            cout << " => ";
            anode->print(cout);
        }

        cout << endl;
    } 

    | '#' kind                  
    { 
        cout << "result => kind";

        Mu::AST::ASTNode* anode = $2;

        if (anode) 
        {
            cout << " => ";
            anode->print(cout);
        }

        cout << endl;
    }

    | type_operator_declaration { cout << "result => type operator" << endl; }
    | error                     { cout << "result => error" << endl; }

    /*| function_declaration      { cout << "result => function" << endl; } 
    | module_declaration 
    {
        cout << "result => module" << endl; 
    } 
     | type_declaration          { cout << "result => type_declaration" << endl; }
    */

    | expression_sequence
    { 
        cout << "result => expression";
        Mu::AST::ASTNode* anode = $1;

        if (anode) 
        {
            cout << " => ";
            anode->printAnnotated(cout);
        }

        cout << endl;

        if (anode)
        {
            if (Mu::Node* n = anode->resolveSymbolConstant(*AS, anode->resolve(*AS)))
            {
                Mu::Thread* t = AS->process()->newApplicationThread();
                Mu::Value v;

                try
                {
                    v = n->eval(*t);
                }
                catch (exception& e)
                {
                    cerr << "ERROR: uncaught exception: " << e.what() << endl;
                }
                catch (...)
                {
                    cerr << "ERROR: unknown exception" << endl;
                }

                const Mu::Type* type = n->type();

                type->output(cout);
                cout << " => ";
                type->outputValue(cout, v);
                cout << endl;

                AS->process()->releaseApplicationThread(t);
            }
            else
            {
                cout << "error => not resolved" << endl;
            }
        }
    }
;

//----------------------------------------------------------------------

module_declaration:
    MU_MODULE identifier block_expression { $$ = astModuleDecl(@$, $2, $3); }
    | MU_MODULE identifier type_parameter_clause block_expression { $$ = 0; }
;

//----------------------------------------------------------------------

identifier: 
    MU_IDENTIFIER { $$ = astRefIdentifier(@$, $1); }
;

scoped_identifier:
    identifier
    | scoped_identifier '.' identifier { $$ = astScopeOp(@$, $1, $3); }
;

scoped_identifier_list:
    scoped_identifier 
    | scoped_identifier ',' scoped_identifier_list { $1->append($3); }
;

//----------------------------------------------------------------------

kind:
    unary_kind { $$ = 0; } 
;

kind_opt:
    /* empty */ { $$ = 0; }
    | kind { $$ = 0; }
;

kind_list:
    kind { $$ = 0; } 
    | kind_list ',' kind { $$ = 0; }
;

kind_list_opt:
    /* empty */ { $$ = 0; }
    | kind_list { $$ = 0; }
;

unary_kind:
    postfix_kind { $$ = 0; } 
;

postfix_kind:
    primary_kind                            { $$ = 0; }
    | postfix_kind '[' kind_opt ']'         { $$ = 0; }
    | postfix_kind '[' dimension_list ']'   { $$ = 0; }
;   

primary_kind:
    '*'                                     { $$ = 0; }
    | '(' kind_list ')'                     { $$ = 0; } /* parens or tuple */
    | '[' kind ';' kind_list_opt ']'        { $$ = 0; } 
    | '[' kind ']'                          { $$ = 0; }
;

//----------------------------------------------------------------------

type_parameter:
    kind identifier { $$ = 0; }
;

type_parameter_list:
    type_parameter { $$ = 0; }
    | type_parameter_list ',' type_parameter { $$ = 0; }
;

type_parameter_clause:
    '[' type_parameter_list ']' { $$ = 0; }
;

type_list:
    type
    | type_list ',' type                    { $$ = $1->append($3); }
;

type_list_opt:
    /* empty */                             { $$ = 0; }
    | type_list
;

type:
    arrow_type
;

arrow_type:
    unary_type
    | '(' type_list_opt ')' MU_ARROW type   { $$ = astTypeFunction(@$, $5, $2); }
;

unary_type:
    postfix_type
    | MU_TYPEMODIFIER postfix_type          { $$ = 0; } /* type modifier */
    | type_parameter_clause postfix_type    { $$ = 0; } /* parameterized type expr "[*A] A" */
;

postfix_type:
    primary_type
    | postfix_type '[' type_list_opt ']'    { $$ = astIndexedType(@$, $1, $3); } /* "a[]" or "a[type]" or "a[t1,t2]" */
    | postfix_type '[' dimension_list ']'   { $$ = astTypeFixedArray(@$, $1, $3); }
;   

primary_type:
    identifier                              { $$ = astTypeIdentifier(@$, $1); }
    | '(' type_list ')'                     { $$ = astTypeTuple(@$, $2); } /* "(t)" or "(a,b)" */
    | '[' type ']'                          { $$ = astTypeList(@$, $2); }
    | '(' type ';' type_list_opt ')'        { $$ = astTypeFunction(@$, $2, $4); } 
//  | '{' field_declarations '}'            { $$ = 0; }  // "{int a; int b}" structural record type 
;

dimension_list:
    MU_INTCONST                             { $$ = astConstant(@$, MU_INTCONST, Mu::Value($1)); }
    | dimension_list ',' MU_INTCONST        { $$ = $1->append(astConstant(@$, MU_INTCONST, Mu::Value($3))); }
;

//----------------------------------------------------------------------

variant_constructor:
    identifier                              { $$ = 0; }
    | identifier type                       { $$ = 0; }
;

variant_constructor_list:
    variant_constructor
    | variant_constructor_list '|' variant_constructor { $$ = 0; }
;

variant_type_declaration:
    MU_UNION identifier '{' variant_constructor_list '}'   { $$ = 0; }
    | MU_UNION type_parameter_clause identifier '{' variant_constructor_list '}'   { $$ = 0; }
;

field_declaration:
    type identifier { $$ = fieldDecl(@$, $1, $2); }
    | function_declaration
    | type_declaration
;

field_declaration_list:
    field_declaration
    | field_declaration_list ';' field_declaration { $$ = $1->append($3); }
;

field_declarations:
    /* empty */ { $$ = 0; }
    | field_declaration_list
    | field_declaration_list ';' { $$ = $1; }
;

//----------------------------------------------------------------------

record_type_declaration:
    MU_STRUCT identifier '{' field_declarations '}'   { $$ = recordDecl(@$, $2, $4); }
    | MU_STRUCT type_parameter_clause identifier '{' field_declarations '}'   { $$ = 0; }
;

//----------------------------------------------------------------------

class_type_declaration:
    MU_CLASS identifier '{' field_declarations '}'   { $$ = classDecl(@$, $2, $4); }
    | MU_CLASS type_parameter_clause identifier '{' field_declarations '}'   { $$ = 0; }
;

//----------------------------------------------------------------------

type_declaration:
    variant_type_declaration { $$ = 0; }
    | record_type_declaration
    | class_type_declaration
;

//----------------------------------------------------------------------

parameter:
    type identifier { $$ = astParamDecl(@$, $1, $2, 0); }
;

parameter_list:
    /* empty */ { $$ = 0; }
    | parameter
    | parameter_list ',' parameter { $$ = $1->append($3); }
;

function_declaration:
    MU_FUNCTION identifier '(' parameter_list ')' expression { $$ = 0; }
    | MU_FUNCTION identifier '(' type ';' parameter_list ')' expression { $$ = astFuncDecl(@$, $2, $4, $6, $8); }
    | MU_FUNCTION identifier '(' parameter_list ')' MU_ARROW type expression { $$ = astFuncDecl(@$, $2, $7, $4, $8); }
    | MU_FUNCTION identifier type_parameter_clause '(' parameter_list ')' expression { $$ = 0; }
    | MU_FUNCTION identifier type_parameter_clause '(' type ';' parameter_list ')' expression { $$ = 0; }
    | MU_FUNCTION identifier type_parameter_clause '(' parameter_list ')' MU_ARROW type expression { $$ = 0; }
;

type_operator_declaration:
    MU_FUNCTION identifier '[' kind ';' type_parameter_list ']' expression { $$ = 0; }
    | MU_FUNCTION identifier '[' type_parameter_list ']' MU_ARROW kind expression { $$ = 0; }
;

//----------------------------------------------------------------------

argument_opt:
    /* empty */ { $$ = 0; }
    | expression 
;

argument_opt_list:
    argument_opt
    | argument_opt_list ',' argument_opt { $$ = $1->append($3); }
;

argument_list:
    expression
    | argument_list ',' expression { $$ = $1->append($3); }
;

list_element_list:
    expression
    | list_element_list ',' expression { $$ = $1->append($3); }
;

comma_opt:
    /* empty */ { $$ = 0; }
    | ','       { $$ = 0; }
;

semicolon_opt:
    /* empty */ { $$ = 0; }
    | ';'       { $$ = 0; }
;

//----------------------------------------------------------------------

variable_initializer:
    identifier '=' expression { $$ = astVarInitializer(@$, $1, $3); }
;

variable_initializer_list:
    variable_initializer
    | variable_initializer_list ',' variable_initializer { $$ = $1->append($3); }
;

variable_declation:
    type variable_initializer_list { $$ = astVarDeclaration(@$, $1, $2); }
;

//----------------------------------------------------------------------

pattern:
    cons_pattern
;

cons_pattern:
    primary_pattern
    | cons_pattern ':' primary_pattern { $$ = astConsPattern(@$, $1, $3); }
;

primary_pattern:
    identifier                      { $$ = astNamePattern(@$, $1); }
    | scoped_identifier identifier  { $$ = astConstructorPattern(@$, $1, $2); }
    | constant_suffix               { $$ = astConstantPattern(@$, $1); }
    | '-' constant_suffix           { $$ = astConstantPattern(@$, $2, true); }
    | '_'                           { $$ = astMatchAnyPattern(@$); }
    | '(' pattern_list ')'          { $$ = astCompoundPattern(@$, $2, AST::CompoundPattern::Tuple); }
    | '{' pattern_list '}'          { $$ = astCompoundPattern(@$, $2, AST::CompoundPattern::Struct); }
    | '[' pattern_list ']'          { $$ = astCompoundPattern(@$, $2, AST::CompoundPattern::List); }
;

pattern_list:
    pattern 
    | pattern_list ',' pattern { $$ = $1->appendPattern($3); }
;

let_pattern:
    pattern '=' conditional_expression { $$ = astPatternEquality(@$, $1, $3); }
;

let_pattern_list:
    let_pattern
    | let_pattern_list ',' let_pattern { $$ = $1->append($3); }
;

case_pattern:
    pattern MU_ARROW expression { $$ = astCasePattern(@$, $1, $3); }
;

case_pattern_list:
    case_pattern
    | case_pattern_list ',' case_pattern { $$ = $1->append($3); }
;

//----------------------------------------------------------------------
//
//  Sequence experssion incorporates statement-like expessions to make it
//  C-like. To have only the expression language expression_sequence
//  would use expression in place of expression_sequence_expression and the
//  orphaned non-terminals would be removed.
//

expression_sequence:
    expression_sequence_expression
    | expression_sequence_declaration_list
    | expression_sequence ';' expression_sequence_expression { $$ = $1->append($3); }
    | expression_sequence ';' expression_sequence_declaration_list { $$ = $1->append($3); }
;

expression_sequence_declaration_list:
    expression_sequence_declaration
    | expression_sequence_declaration_list expression_sequence_declaration { $$ = $1->append($2); }
;

expression_sequence_declaration:
    function_declaration
    | type_declaration { $$ = 0; }
    | module_declaration 
;

expression_sequence_expression:
    expression
    | variable_declation
    | expression_sequence_let
    | expression_sequence_require
;

expression_sequence_let:
    MU_LET let_pattern_list { $$ = astLetExpr(@$, $2); }
;

expression_sequence_require:
    MU_REQUIRE scoped_identifier_list { $$ = astRequireExpr(@$, $2, MU_REQUIRE); }
    | MU_USE scoped_identifier_list { $$ = astRequireExpr(@$, $2, MU_USE); }
;

//---------------------------------------------------------------------- 
//
//  Top of expression language 
//

tuple_expression:
    expression
    | tuple_expression ',' expression { $$ = astTuple(@$, $1, $3); }
;

expression: 
    require_expression
;

require_expression:
    let_expression
    | MU_REQUIRE scoped_identifier_list MU_IN require_expression { $$ = astRequireExpr(@$, $2, MU_REQUIRE, $4); }
    | MU_USE scoped_identifier_list MU_IN require_expression { $$ = astRequireExpr(@$, $2, MU_USE, $4); }
;

let_expression:
    conditional_expression
    | MU_LET let_pattern_list MU_IN let_expression { $$ = astLetExpr(@$, $2, $4); }
;

conditional_expression:
    cons_expression
    | MU_IF cons_expression MU_THEN cons_expression MU_ELSE cons_expression { $$ = astConditional(@$, $2, $4, $6); }
    | MU_CASE cons_expression MU_OF '{' case_pattern_list '}' { $$ = astCaseExpr(@$, $2, $5); }
;

cons_expression:
    lambda_expression
    | lambda_expression ':' cons_expression { $$ = astApply2(@$, "cons", $1->append($3), CONTEXT); }
;

lambda_expression:
    logical_OR_expression
    | MU_FUNCTION '(' type ';' parameter_list ')' expression { $$ = astFuncDecl(@$, 0, $3, $5, $7); }
;

logical_OR_expression:
    logical_AND_expression
    | logical_OR_expression MU_LOGICOR logical_AND_expression { $$ = astApply2(@$, "||", $1->append($3), CONTEXT); }
;

logical_AND_expression:
    equality_expression 
    | logical_AND_expression MU_LOGICAND equality_expression { $$ = astApply2(@$, "&&", $1->append($3), CONTEXT); }
;

equality_expression:
    relational_expression 
    | equality_expression MU_EQUALS relational_expression    { $$ = astApply2(@$, "==", $1->append($3), CONTEXT); }
    | equality_expression MU_NOTEQUALS relational_expression { $$ = astApply2(@$, "!=", $1->append($3), CONTEXT); }
    | equality_expression MU_EQ relational_expression        { $$ = astApply2(@$, "eq", $1->append($3), CONTEXT); }
    | equality_expression MU_NEQ relational_expression       { $$ = astApply2(@$, "neq", $1->append($3), CONTEXT); }
;

relational_expression:
    additive_expression 
    | relational_expression '>' additive_expression             { $$ = astApply2(@$, ">", $1->append($3), CONTEXT); }
    | relational_expression '<' additive_expression             { $$ = astApply2(@$, "<", $1->append($3), CONTEXT); }
    | relational_expression MU_LESSEQUALS additive_expression   { $$ = astApply2(@$, "<=", $1->append($3), CONTEXT); }
    | relational_expression MU_GREATEREQUALS additive_expression { $$ = astApply2(@$, ">=", $1->append($3), CONTEXT); }
;

additive_expression:
    multiplicative_expression
    | additive_expression '+' multiplicative_expression { $$ = astApply2(@$, "+", $1->append($3), CONTEXT); }
    | additive_expression '-' multiplicative_expression { $$ = astApply2(@$, "-", $1->append($3), CONTEXT); }
;

multiplicative_expression:
    unary_expression
    | multiplicative_expression '*' unary_expression { $$ = astApply2(@$, "*", $1->append($3), CONTEXT); }
    | multiplicative_expression '/' unary_expression { $$ = astApply2(@$, "/", $1->append($3), CONTEXT); }
    | multiplicative_expression '%' unary_expression { $$ = astApply2(@$, "%", $1->append($3), CONTEXT); }
;

unary_expression:
    application_expression
    | '-' application_expression { $$ = astApply2(@$, "-", $2, CONTEXT); }
    | '!' application_expression { $$ = astApply2(@$, "!", $2, CONTEXT); }
    | '~' application_expression { $$ = astApply2(@$, "~", $2, CONTEXT); }
    | '+' application_expression { $$ = astApply2(@$, "+", $2, CONTEXT); }
    | MU_OP_INC application_expression { $$ = astApply2(@$, "pre++", $2, CONTEXT); }
;

//
//  application_expression has 7 reduce/reduce conflicts that eventually
//  end up here. The correct resolution is to try both results and see
//  which one succeeds. If they both succeed then its ambiguous and
//  therefor an error.
//
application_expression:
    postfix_value_expression %merge <GLRastmerge>
    | application_expression '(' argument_opt_list ')' %merge <GLRastmerge> { $$ = astExprApply(@$, $1, $3); }
    | type '(' argument_opt_list ')' %merge <GLRastmerge> { $$ = astExprApply(@$, $1, $3); }
;

postfix_value_expression:
    value_expression
    | postfix_expression
    | postfix_expression MU_OP_INC { $$ = astApply2(@$, "post++", $1, CONTEXT); }
    | postfix_value_expression '.' postfix_expression { $$ = astScopeOp(@$, $1, $3); }
;

postfix_expression:
    primary_expression
    | postfix_expression '[' argument_list ']' { $$ = astIndexedExpr(@$, $1, $3); }
;

block_expression:
    '{' expression_sequence semicolon_opt '}'     { $$ = astEndSequenceExpr(@$, $2); }
;

primary_expression:
    identifier
    | block_expression
    | '(' tuple_expression ')'                      { $$ = astEndTuple(@$, $2); }
    | '[' list_element_list comma_opt ']'           { $$ = astList(@$, $2); }
    | '(' naked_operator ')'                        { $$ = astRefIdentifier2(@$, $2, CONTEXT); }
;

value_expression:
    constant_suffix
    | aggregate_value
    | MU_NIL  { $$ = astConstant(@$, MU_NIL, Mu::Value()); }
;

//
//  NOTE: one reduce/reduce is naked_operator and primary_kind (*). This is
//  resolved by just letting the GLR parser parse enough tokens to kill one
//  of the parsing threads.
//
naked_operator:
      '+' { $$[0] = '+'; $$[1] = 0; }
    | '-' { $$[0] = '-'; $$[1] = 0; }
    | '/' { $$[0] = '/'; $$[1] = 0; }
    | '*' { $$[0] = '*'; $$[1] = 0; }
    | '%' { $$[0] = '%'; $$[1] = 0; }
    | '^' { $$[0] = '^'; $$[1] = 0; }
    | '|' { $$[0] = '|'; $$[1] = 0; }
    | '&' { $$[0] = '&'; $$[1] = 0; }
    | '<' { $$[0] = '<'; $$[1] = 0; }
    | '>' { $$[0] = '>'; $$[1] = 0; }
    | ':' { $$[0] = ':'; $$[1] = 0; }
    | '[' ']' { $$[0] = '['; $$[1] = ']'; $$[2] = 0; }
    | MU_LESSEQUALS
    | MU_GREATEREQUALS
    | MU_LSHIFT
    | MU_RSHIFT
    | MU_EQUALS
    | MU_NOTEQUALS
    | MU_EQ
    | MU_NEQ
;

aggregate_initializer:
    expression %dprec 1
    | aggregate_initializer_block %dprec 2 { $$ = astAggregateValueExpr(@$, 0, $1); }
;

aggregate_initializer_list:
    aggregate_initializer
    | aggregate_initializer_list ',' aggregate_initializer { $$ = $1->append($3); }
;

aggregate_initializer_block:
    '{' aggregate_initializer_list '}' { $$ = $2; }
;

aggregate_value:
    type aggregate_initializer_block { $$ = astAggregateValueExpr(@$, $1, $2); }
;

constant_suffix:
      constant
      | constant identifier { $$ = astApply(@$, static_cast<Mu::AST::RefIdentifier*>($2)->name, $1); }
;

constant:
    MU_FLOATCONST           { $$ = astConstant(@$, MU_FLOATCONST, Mu::Value($1)); }
    | MU_INTCONST           { $$ = astConstant(@$, MU_INTCONST, Mu::Value($1)); }
    | MU_BOOLCONST          { $$ = astConstant(@$, MU_BOOLCONST, Mu::Value($1)); }
    | MU_STRINGCONST        { $$ = astConstant(@$, MU_STRINGCONST, Mu::Value($1)); }
    | MU_CHARCONST          { $$ = astConstant(@$, MU_CHARCONST, Mu::Value($1)); }
;

//----------------------------------------------------------------------
%%

Mu::AST::ASTNode* 
GLRastmerge(const YYSTYPE& a, const YYSTYPE& b)
{
    if (AST::ExprApply* ep = dynamic_cast<AST::ExprApply*>(b._node))
    {
        if (dynamic_cast<AST::TypeIdentifier*>(ep->expression))
        {
            //
            //  This is both:
            //
            //      id (args)   -and-   type (args)
            //
            //  where type is a just a type identifier. In that case
            //  we can let the "a" branch resolve it since both
            //  are valid. This will allow the "b" branch to be reclaimed
            //  by the GC as soon as possible.
            //

            return a._node;
        }
    }

    return astMerge(a._node, b._node);
}

void
GLRParseError(YYLTYPE* loc, MUGLRYYFlexLexer* lexer, const char *text, ...)
{
    char temp[256];

    va_list ap;
    va_start(ap,text);
    vsprintf(temp,text,ap);
    va_end(ap);

    lexer->assembler()->reportError(temp);
}

void
GLRModuleLocationError(YYLTYPE* loc, MUGLRYYFlexLexer* state, const char *text, ...)
{
    const Mu::Environment::SearchPath& paths = Mu::Environment::modulePath();

    for (int i=0; i < paths.size(); i++)
    {
        const Mu::String& p = paths[i];

        GLRParseError(loc, state, "Can't locate module named \"%s\" in %s.", 
                      text, p.c_str());
    }
}


void
GLRParseWarning(YYLTYPE* loc, MUGLRYYFlexLexer* lexer, const char *text, ...)
{
    char temp[256];

    va_list ap;
    va_start(ap,text);
    vsprintf(temp,text,ap);
    va_end(ap);

    lexer->assembler()->reportWarning(temp);
}

int
yylex(void* lvalp, YYLTYPE* loc, MUGLRYYFlexLexer* lexer)
{
    lexer->setYYSTYPE(lvalp);
    lexer->setYYLTYPE(loc);
    return lexer->yylex();
}

namespace Mu {

Mu::Process*
GLRParse(const char *sourceName, Mu::NodeAssembler *assembler)
{
    //
    //  Initialize state
    //

    ::yydebug = 0;
    yyFlexLexer lexer(&assembler->context()->inputStream(),
                      &assembler->context()->outputStream());

    lexer.init(sourceName, assembler);
    assembler->allowUnresolvedCalls(false);

    //
    //  Call the yacc parser
    //

    if (yyparse(&lexer)) return 0;

    //
    //  Patch any unresolved symbols
    //

    assembler->patchUnresolved();

    //
    //  Finish
    //

    return assembler->process();
}   

} // namespace Mu



