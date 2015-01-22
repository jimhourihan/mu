%{
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
//"alias"                 { as->charNum()+=yyleng; return MU_ALIAS; }
//"type"                  { as->charNum()+=yyleng; return MU_TYPE_KEY; }
//"kind"                  { as->charNum()+=yyleng; return MU_KIND_KEY; }
*/
#include "GrammarDefs.h"
#include <iostream>
#include <sstream>
#include <Mu/config.h>
#include <Mu/utf8_v2/checked.h>
using namespace std;

#if MU_FLEX_MINOR_VERSION >= 33
#define YY_NO_UNISTD_H
#endif

#define yydebug MUGLRYYdebug
extern int	yydebug;
#define LVAL reinterpret_cast<YYSTYPE*>(_yystype)

%}

%option always-interactive
%option noyywrap
%option c++

Identifier		[A-Za-z_][A-Za-z_0-9]*
NewLine 		\r?[\n]
WhiteSpace		[[:blank:]]+
NonWhiteSpace		[^[:blank:]]+
FloatNumA 		[[:digit:]]*\.[[:digit:]]+([Ee][+-]?[[:digit:]]+)?
FloatNumB 		[[:digit:]]+\.?([Ee][+-]?[[:digit:]]+)?
IntNum			[[:digit:]]+
HexNum			0x[[:xdigit:]]+
UnicodeEsc		\\u[[:xdigit:]][[:xdigit:]][[:xdigit:]][[:xdigit:]]+
CUnicodeEsc             \'\\u[[:xdigit:]][[:xdigit:]][[:xdigit:]][[:xdigit:]]+\'
OctalEsc		\\[0-3][0-7][0-7]

%x COMMENT
%x STRING
%x VERBATIM
%x IDMODE
%x CHAR

%%

{WhiteSpace}            { loc()->last_column += yyleng;		}
{NewLine}               { loc()->last_line++; loc()->last_column=0;	}

"true" |
"false"			{ 
			    loc()->last_column++; 
			    LVAL->_int = *yytext == 't'; 
			    return MU_BOOLCONST; 
			}

"nil"			{ loc()->last_column+=yyleng; return MU_NIL; }

"_"                     { loc()->last_column+=yyleng; return '_'; }
"if"			{ loc()->last_column+=yyleng; return MU_IF; }
"of"			{ loc()->last_column+=yyleng; return MU_OF; }
"in"			{ loc()->last_column+=yyleng; return MU_IN; }
"else"			{ loc()->last_column+=yyleng; return MU_ELSE; }
"then"			{ loc()->last_column+=yyleng; return MU_THEN; }
"case"			{ loc()->last_column+=yyleng; return MU_CASE; }
"do"			{ loc()->last_column+=yyleng; return MU_DO; }
"for"			{ loc()->last_column+=yyleng; return MU_FOR; }
"let"                   { loc()->last_column+=yyleng; return MU_LET; }
"var"                   { loc()->last_column+=yyleng; return MU_VAR; }
"new"                   { loc()->last_column+=yyleng; return MU_NEW; }
"for_each"		{ loc()->last_column+=yyleng; return MU_FOREACH; }
"for_index"		{ loc()->last_column+=yyleng; return MU_FORINDEX; }
"repeat"		{ loc()->last_column+=yyleng; return MU_REPEAT; }
"while"			{ loc()->last_column+=yyleng; return MU_WHILE; }
"break"			{ loc()->last_column+=yyleng; return MU_BREAK; }
"continue"		{ loc()->last_column+=yyleng; return MU_CONTINUE; }
"try"			{ loc()->last_column+=yyleng; return MU_TRY; }
"catch"			{ loc()->last_column+=yyleng; return MU_CATCH; }
"const"			{ loc()->last_column+=yyleng; return MU_CONST; }
"throw"			{ loc()->last_column+=yyleng; return MU_THROW; }
"return"		{ loc()->last_column+=yyleng; return MU_RETURN; }
"require"		{ loc()->last_column+=yyleng; return MU_REQUIRE; }
"use"			{ loc()->last_column+=yyleng; return MU_USE; }
"global"		{ loc()->last_column+=yyleng; return MU_GLOBAL; }
"yield"                 { loc()->last_column+=yyleng; return MU_YIELD; }
"class:"                { loc()->last_column+=yyleng; return MU_CLASS; }
"struct:"               { loc()->last_column+=yyleng; return MU_STRUCT; }
"interface:"            { loc()->last_column+=yyleng; return MU_INTERFACE; }
"method:"               { loc()->last_column+=yyleng; return MU_METHOD; }
"module:"               { loc()->last_column+=yyleng; return MU_MODULE; }
"function:"|"\\:"	{ loc()->last_column+=yyleng; return MU_FUNCTION; }
"documentation:"	{ loc()->last_column+=yyleng; return MU_DOCUMENTATION; }
"union:"                { loc()->last_column+=yyleng; return MU_UNION; }
"type:"                 { loc()->last_column+=yyleng; return MU_TYPE_KEY; }
"alias:"                { loc()->last_column+=yyleng; return MU_ALIAS; }
"operator:"		{ loc()->last_column+=yyleng; BEGIN IDMODE; return MU_OPERATOR; }

<IDMODE>{WhiteSpace}	{ loc()->last_column+=yyleng; }
<IDMODE>{NewLine}	{ loc()->last_line++; loc()->last_column=0; }
<IDMODE>{NonWhiteSpace}	{ 
			  loc()->last_column+=yyleng; 
			  LVAL->_name = as->context()->internName(yytext).nameRef();
			  BEGIN 0;
			  return MU_IDENTIFIER;
			}

\(			{ loc()->last_column++; return '('; }
\)			{ loc()->last_column++; return ')'; }

"//".*{NewLine}		{ loc()->last_line++; loc()->last_column=0;		    }
"/*"			{ loc()->last_column += yyleng; BEGIN COMMENT;	    }
<COMMENT>{NewLine}	{ loc()->last_line++; loc()->last_column=0;		    }
<COMMENT>"*/"		{ loc()->last_column += yyleng; BEGIN 0;		    }
<COMMENT>.		{ loc()->last_column++;				    }

"\"\"\""                { loc()->last_column++; yyNewString(); BEGIN VERBATIM; }

<VERBATIM>{UnicodeEsc}	{ 
			  loc()->last_column += yyleng; 
			  unsigned int u = strtol(yytext+2,(char**)0,16);
			  yyAddToString(u); 
			}

<VERBATIM>{OctalEsc}	{ 
			  loc()->last_column += yyleng; 
			  unsigned int u = strtol(yytext+1,(char**)0,8);
			  yyAddToString(u); 
			}

<VERBATIM>{NewLine}     { loc()->last_line++; loc()->last_column=0; yyAddToString('\n'); }
<VERBATIM>"\\r"         { loc()->last_column += yyleng; yyAddToString('\r'); }
<VERBATIM>"\\\\"	{ loc()->last_column += yyleng; yyAddToString('\\'); }
<VERBATIM>"\\\""	{ loc()->last_column += yyleng; yyAddToString('"'); }

<VERBATIM>"\"\"\""	{ 
			  loc()->last_column++; 
                          BEGIN 0;

                          LVAL->_object = yyReturnString();
                          return MU_STRINGCONST; 
			}

<VERBATIM>.		{ loc()->last_column++; yyAddToString(*yytext);}

"\""			{ loc()->last_column++; yyNewString(); BEGIN STRING; }

<STRING>{UnicodeEsc}	{ 
			  loc()->last_column += yyleng; 
                          Mu::UTF32Char u = strtol(yytext+2,(char**)0,16);
			  yyAddToString(u); 
			}

<STRING>{OctalEsc}	{ 
			  loc()->last_column += yyleng; 
                          Mu::UTF32Char u = strtol(yytext+1,(char**)0,8);
			  yyAddToString(u); 
			}

<STRING>{NewLine}       { loc()->last_line++; loc()->last_column=0; yyAddToString('\n'); }
<STRING>"\\b"		{ loc()->last_column += yyleng; yyAddToString('\b'); }
<STRING>"\\t"		{ loc()->last_column += yyleng; yyAddToString('\t'); }
<STRING>"\\n"		{ loc()->last_column += yyleng; yyAddToString('\n'); }
<STRING>"\\f"		{ loc()->last_column += yyleng; yyAddToString('\f'); }
<STRING>"\\r"		{ loc()->last_column += yyleng; yyAddToString('\r'); }
<STRING>"\\\""		{ loc()->last_column += yyleng; yyAddToString('"'); }
<STRING>"\'"		{ loc()->last_column += yyleng; yyAddToString('\''); }
<STRING>"\\\\"		{ loc()->last_column += yyleng; yyAddToString('\\'); }

<STRING>"\""		{ 
			  loc()->last_column++; 
                          BEGIN 0;

                          LVAL->_object = yyReturnString();
                          return MU_STRINGCONST; 
			}

<STRING>.		{ loc()->last_column++; yyAddToString(*yytext);}

{IntNum} |
{HexNum}		{
			    LVAL->_int   = strtoll(yytext,0,0);
			    loc()->last_column += yyleng;
			    return MU_INTCONST;
			}

{FloatNumA} |
{FloatNumB}             {
			    LVAL->_float = atof(yytext);
			    loc()->last_column += yyleng;
			    return MU_FLOATCONST;
			}


\'\\[btnfr\\]\'         {
                            switch (yytext[2])
                            {
                              case 'b': LVAL->_int = int('\b'); break;
                              case 't': LVAL->_int = int('\t'); break;
                              case 'n': LVAL->_int = int('\n'); break;
                              case 'f': LVAL->_int = int('\f'); break;
                              case 'r': LVAL->_int = int('\r'); break;
                              default:
                                  LVAL->_int = yytext[2]; break;
                            }

                            loc()->last_column += yyleng;
                            return MU_CHARCONST;
                        }

{CUnicodeEsc}           { 
                            loc()->last_column += yyleng; 
                            unsigned int u = strtol(yytext+3,(char**)0,16);
                            LVAL->_int = u;
                            return MU_CHARCONST;
                        }

\'[^\']{1,4}\' |         
\'\\\'\'                {
                            loc()->last_column += 1; 

                            if (!strcmp(yytext, "\'\\\'\'"))
                            {
                                LVAL->_int = '\'';
                            }
                            else
                            {
                                try
                                {
                                    char* t = yytext + 1;
                                    char* e = t + yyleng - 2;
                                    LVAL->_int = utf8::next(t, e);

                                    // bad
                                    if (t != e) LVAL->_int = -1;
                                }
                                catch (std::exception &exc)
                                {
                                    cerr << "ERROR: " << exc.what() << endl;
                                    LVAL->_int = -1;
                                }
                            }

                            return MU_CHARCONST;
                        }

"{%%debug%%}"           {
			    yydebug=!yydebug;
			    loc()->last_column += yyleng;
			}

".."                    {
			    loc()->last_column += yyleng;
			    return MU_DOUBLEDOT;
                        }

"..."			{ 
			    loc()->last_column += yyleng;
			    return MU_ELLIPSIS;
			}

"...."			{ 
			    loc()->last_column += yyleng;
			    return MU_QUADRUPLEDOT;
			}
"++" |
"--"			{ 
			    loc()->last_column += yyleng; 
			    strcpy(LVAL->_op,yytext);
			    return MU_OP_INC;
			}

":="			{
			    loc()->last_column += yyleng; 
			    strcpy(LVAL->_op,yytext);
			    return MU_OP_SYMASSIGN;
			}

"+="  | 
"-="  | 
"*="  | 
"/="  | 
"%="  | 
"&="  | 
"^="  | 
"|="  | 
"<<=" | 
">>="			{	
			    loc()->last_column += yyleng; 
			    strcpy(LVAL->_op,yytext);
			    return MU_OP_ASSIGN;
			}

"eq"			{ loc()->last_column+=yyleng; strcpy(LVAL->_op,yytext); return MU_EQ; }
"neq"			{ loc()->last_column+=yyleng; strcpy(LVAL->_op,yytext); return MU_NEQ; }

"=>"			{ loc()->last_column += yyleng; return MU_DOUBLEARROW; }
"->"			{ loc()->last_column += yyleng; return MU_ARROW; }

">>"			{   loc()->last_column += yyleng; return MU_RSHIFT; }
"<<"			{   loc()->last_column += yyleng; return MU_LSHIFT; }
"<="			{   loc()->last_column += yyleng; return MU_LESSEQUALS;	}
">="			{   loc()->last_column += yyleng; return MU_GREATEREQUALS;  }
"=="			{   loc()->last_column += yyleng; return MU_EQUALS;		}
"!="			{   loc()->last_column += yyleng; return MU_NOTEQUALS;	}
"&&"			{   loc()->last_column += yyleng; return MU_LOGICAND;	}
"||"			{   loc()->last_column += yyleng; return MU_LOGICOR;	}
">"			{   loc()->last_column++; return int('>'); }
"<"			{   loc()->last_column++; return int('<'); }

{Identifier}		{
			    loc()->last_column += yyleng;
			    return yyIdentifier(yytext);
			}

<<EOF>>			{
			    yyterminate();
			}

.			{
                            loc()->last_column++;
			    return *yytext;
			}

%%

int
yyFlexLexer::yyIdentifier(const char *text)
{
    LVAL->_name = as->context()->internName(text).nameRef();
    return MU_IDENTIFIER;
}


void 
yyFlexLexer::yyNewString()
{
#if COMPILER == GCC2_96
    stringBuffer = "";
#else
    stringBuffer.clear();
#endif
}

void 
yyFlexLexer::yyAddToString(Mu::UTF32Char c)
{
    if (c >= 127)
    {
        utf8::utf32to8(&c, &c+1, back_inserter(stringBuffer));
    }
    else
    {
        stringBuffer.push_back(c);
    }
}

Mu::StringType::String*
yyFlexLexer::yyReturnString()
{
    Mu::MuLangContext* c = static_cast<Mu::MuLangContext*>(as->context());
    return c->stringType()->allocate(stringBuffer);
}

void
yyFlexLexer::init(const char* source, Mu::NodeAssembler* a)
{
    as = a; 
    as->setSourceName(source);
    as->lineNum() = 1;
    as->charNum() = 1;
}
