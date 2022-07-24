%top{
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
#include <MuLang/StringType.h>
#include <Mu/NodeAssembler.h>
#include <MuLang/MuGrammar.y.h>
#include <iostream>
#include <sstream>
#include <Mu/config.h>
#include <utf8cpp/utf8/checked.h>
namespace Mu { class location; }
%}

%{
using namespace std;
#define LVAL yylval
#define TOKEN(t) Mu::parser::token::t
#define BUMP(x) as->addChar(x)
#define BUMPLINE(x) as->addLine(x)
#define BUMPSIZE as->addChar(size())
%}

%class{
public:
    std::vector<char>  string_buffer;
    Mu::parser*        parser;
    Mu::NodeAssembler* as;
    Mu::String         stringBuffer;
    //void*            _yystype;

   Lexer(const reflex::Input& input = reflex::Input(),
         std::ostream& os = std::cout,
         Mu::parser* p    = nullptr)
       : AbstractBaseLexer(input, os)
    {
        set_debug(1);
    }

    void init(const char* source, Mu::NodeAssembler* a)
    {
        as = a; 
        as->setSourceName(source);
        as->setLine(1);
        as->setChar(1);
    }

    const char* sourceName() const { return as->sourceName().c_str(); }
    int lineNum() const { return as->lineNum(); }
    int charNum() const { return as->charNum(); }
    //Mu::NodeAssembler* assembler() { return as; }

    void yyAddToString(Mu::UTF32Char c);
    Mu::StringType::String* yyReturnString();
    int yyIdentifier(const char *text, Mu::parser::semantic_type& yylval);
}

%option always-interactive
%option noyywrap
%option c++
%option namespace="Mu"
%option bison-cc-namespace="Mu"
%option yylineno
%option bison-cc bison-bridge bison-locations

Identifier	[A-Za-z_][A-Za-z_0-9]*
NewLine 	\r?[\n]
WhiteSpace	[[:blank:]]+
NonWhiteSpace	[^[:blank:]]+
FloatNumA 	[[:digit:]]*\.[[:digit:]]+([Ee][+-]?[[:digit:]]+)?
FloatNumB 	[[:digit:]]+\.?([Ee][+-]?[[:digit:]]+)?
IntNum		[[:digit:]]+
HexNum		0x[[:xdigit:]]+
UnicodeEsc	\\u[[:xdigit:]][[:xdigit:]][[:xdigit:]][[:xdigit:]]+
CUnicodeEsc     \'\\u[[:xdigit:]][[:xdigit:]][[:xdigit:]][[:xdigit:]]+\'
OctalEsc	\\[0-3][0-7][0-7]
BOM             \xef\xbb\xbf

%x COMMENT
%x STRING
%x VERBATIM
%x IDMODE
%x CHAR

%%

{BOM}                   { /* ignore BOMs in file */ }
{WhiteSpace}            { BUMPSIZE;		        }
{NewLine}               { BUMPLINE(1); as->setChar(0);	}

"true" |
"false"			{ 
			    BUMP(1); 
			    LVAL._int = *text() == 't'; 
			    return TOKEN(MU_BOOLCONST); 
			}

"nil"			{ BUMPSIZE; return TOKEN(MU_NIL); }
"_"                     { BUMPSIZE; return '_'; }
"if"			{ BUMPSIZE; return TOKEN(MU_IF); }
"else"			{ BUMPSIZE; return TOKEN(MU_ELSE); }
"then"			{ BUMPSIZE; return TOKEN(MU_THEN); }
"case"			{ BUMPSIZE; return TOKEN(MU_CASE); }
"do"			{ BUMPSIZE; return TOKEN(MU_DO); }
"for"			{ BUMPSIZE; return TOKEN(MU_FOR); }
"let"                   { BUMPSIZE; return TOKEN(MU_LET); }
"for_each"		{ BUMPSIZE; return TOKEN(MU_FOREACH); }
"for_index"		{ BUMPSIZE; return TOKEN(MU_FORINDEX); }
"repeat"		{ BUMPSIZE; return TOKEN(MU_REPEAT); }
"while"			{ BUMPSIZE; return TOKEN(MU_WHILE); }
"break"			{ BUMPSIZE; return TOKEN(MU_BREAK); }
"continue"		{ BUMPSIZE; return TOKEN(MU_CONTINUE); }
"try"			{ BUMPSIZE; return TOKEN(MU_TRY); }
"catch"			{ BUMPSIZE; return TOKEN(MU_CATCH); }
"const"			{ BUMPSIZE; return TOKEN(MU_CONST); }
"throw"			{ BUMPSIZE; return TOKEN(MU_THROW); }
"return"		{ BUMPSIZE; return TOKEN(MU_RETURN); }
"require"		{ BUMPSIZE; return TOKEN(MU_REQUIRE); }
"use"			{ BUMPSIZE; return TOKEN(MU_USE); }
"global"		{ BUMPSIZE; return TOKEN(MU_GLOBAL); }
"yield"                 { BUMPSIZE; return TOKEN(MU_YIELD); }
"class:"                { BUMPSIZE; return TOKEN(MU_CLASS); }
"interface:"            { BUMPSIZE; return TOKEN(MU_INTERFACE); }
"method:"               { BUMPSIZE; return TOKEN(MU_METHOD); }
"module:"               { BUMPSIZE; return TOKEN(MU_MODULE); }
function:|\\:           { BUMPSIZE; return TOKEN(MU_FUNCTION); }
"documentation:"	{ BUMPSIZE; return TOKEN(MU_DOCUMENTATION); }
"union:"                { BUMPSIZE; return TOKEN(MU_UNION); }
"type:"                 { BUMPSIZE; return TOKEN(MU_TYPE_KEY); }
"alias:"                { BUMPSIZE; return TOKEN(MU_ALIAS); }
"operator:"		{ BUMPSIZE; start(IDMODE); return TOKEN(MU_OPERATOR); }

<IDMODE>{WhiteSpace}	{ BUMPSIZE; }
<IDMODE>{NewLine}	{ as->addLine(1); as->setChar(0); }
<IDMODE>{NonWhiteSpace}	{ 
			  BUMPSIZE; 
			  LVAL._name = as->context()->internName(text()).nameRef();
			  start(0);
			  return TOKEN(MU_IDENTIFIER);
			}

\(			{ BUMP(1); return '('; }
\)			{ BUMP(1); return ')'; }

"//".*{NewLine}		{ BUMPLINE(1); as->setChar(0);}
"/*"			{ BUMPSIZE; start(COMMENT);}
<COMMENT>{NewLine}	{ BUMPLINE(1); as->setChar(0);}
<COMMENT>"*/"		{ BUMPSIZE; start(0);}
<COMMENT>.		{ BUMP(1);}

"\"\"\""                { BUMP(1); stringBuffer.clear(); start(VERBATIM); }

<VERBATIM>{UnicodeEsc}	{ 
			  BUMPSIZE; 
			  unsigned int u = strtol(text()+2,(char**)0,16);
			  yyAddToString(u); 
			}

<VERBATIM>{OctalEsc}	{ 
			  BUMPSIZE; 
			  unsigned int u = strtol(text()+1,(char**)0,8);
			  yyAddToString(u); 
			}

<VERBATIM>{NewLine}     { BUMPLINE(1); as->setChar(0); yyAddToString('\n'); }
<VERBATIM>\\r           { BUMPSIZE; yyAddToString('\r'); }
<VERBATIM>\\\\          { BUMPSIZE; yyAddToString('\\'); }
<VERBATIM>\\\"          { BUMPSIZE; yyAddToString('"'); }

<VERBATIM>\"\"\"	{ 
			  BUMP(1); 
                          start(0);

                          LVAL._object = yyReturnString();
                          return TOKEN(MU_STRINGCONST); 
			}

<VERBATIM>.		{ BUMP(1); yyAddToString(*text());}

"\""			{ BUMP(1); stringBuffer.clear(); start(STRING); }

<STRING>{UnicodeEsc}	{ 
			  BUMPSIZE; 
                          Mu::UTF32Char u = strtol(text()+2,(char**)0,16);
			  yyAddToString(u); 
			}

<STRING>{OctalEsc}	{ 
			  BUMPSIZE; 
                          Mu::UTF32Char u = strtol(text()+1,(char**)0,8);
			  yyAddToString(u); 
			}

<STRING>{NewLine}       { BUMPLINE(1); as->setChar(0); yyAddToString('\n'); }
<STRING>\\b		{ BUMPSIZE; yyAddToString('\b'); }
<STRING>\\t		{ BUMPSIZE; yyAddToString('\t'); }
<STRING>\\n		{ BUMPSIZE; yyAddToString('\n'); }
<STRING>\\f		{ BUMPSIZE; yyAddToString('\f'); }
<STRING>\\r		{ BUMPSIZE; yyAddToString('\r'); }
<STRING>\\\"		{ BUMPSIZE; yyAddToString('"'); }
<STRING>\'		{ BUMPSIZE; yyAddToString('\''); }
<STRING>\\\\		{ BUMPSIZE; yyAddToString('\\'); }

<STRING>\"		{ 
			  BUMP(1); 
                          start(0);

                          LVAL._object = yyReturnString();
                          return TOKEN(MU_STRINGCONST); 
			}

<STRING>.		{ BUMP(1); yyAddToString(*text());}

{IntNum} |
{HexNum}		{
			    LVAL._int   = strtoll(text(),0,0);
			    BUMPSIZE;
			    return TOKEN(MU_INTCONST);
			}

{FloatNumA} |
{FloatNumB}             {
			    LVAL._float = atof(text());
			    BUMPSIZE;
			    return TOKEN(MU_FLOATCONST);
			}


\'\\[btnfr\\]\'         {
                            switch (text()[2])
                            {
                              case 'b': LVAL._int = int('\b'); break;
                              case 't': LVAL._int = int('\t'); break;
                              case 'n': LVAL._int = int('\n'); break;
                              case 'f': LVAL._int = int('\f'); break;
                              case 'r': LVAL._int = int('\r'); break;
                              default:
                                  LVAL._int = text()[2]; break;
                            }

                            BUMPSIZE;
                            return TOKEN(MU_CHARCONST);
                        }

{CUnicodeEsc}           { 
                            BUMPSIZE; 
                            unsigned int u = strtol(text()+3,(char**)0,16);
                            LVAL._int = u;
                            return TOKEN(MU_CHARCONST);
                        }

\'[^\']{1,4}\' |         
\'\\\'\'                {
                            BUMP(1);

                            if (!strcmp(text(), "\'\\\'\'"))
                            {
                                LVAL._int = '\'';
                            }
                            else
                            {
                                try
                                {
                                    const char* t = text() + 1;
                                    const char* e = t + size() - 2;
                                    LVAL._int = utf8::next(t, e);

                                    // bad
                                    if (t != e) LVAL._int = -1;
                                }
                                catch (std::exception &exc)
                                {
                                    cerr << "ERROR: " << exc.what() << endl;
                                    LVAL._int = -1;
                                }
                            }

                            return TOKEN(MU_CHARCONST);
                        }

"{%%debug%%}"           {
    //yydebug=!yydebug;
                            set_debug(!debug());
			    BUMPSIZE;
			}

".."                    {
			    BUMPSIZE;
			    return TOKEN(MU_DOUBLEDOT);
                        }

"..."			{ 
			    BUMPSIZE;
			    return TOKEN(MU_ELLIPSIS);
			}

"...."			{ 
			    BUMPSIZE;
			    return TOKEN(MU_QUADRUPLEDOT);
			}
"++" |
"--"			{ 
			    BUMPSIZE; 
			    strcpy(LVAL._op,text());
			    return TOKEN(MU_OP_INC);
			}

":="			{
			    BUMPSIZE; 
			    strcpy(LVAL._op,text());
			    return TOKEN(MU_OP_SYMASSIGN);
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
			    BUMPSIZE; 
			    strcpy(LVAL._op,text());
			    return TOKEN(MU_OP_ASSIGN);
			}

"eq"			{ BUMPSIZE; strcpy(LVAL._op,text()); return TOKEN(MU_EQ); }
"neq"			{ BUMPSIZE; strcpy(LVAL._op,text()); return TOKEN(MU_NEQ); }

"=>"			{ BUMPSIZE; return TOKEN(MU_DOUBLEARROW); }
"->"			{ BUMPSIZE; return TOKEN(MU_ARROW); }

">>"			{   BUMPSIZE; return TOKEN(MU_RSHIFT); }
"<<"			{   BUMPSIZE; return TOKEN(MU_LSHIFT); }
"<="			{   BUMPSIZE; return TOKEN(MU_LESSEQUALS);}
">="			{   BUMPSIZE; return TOKEN(MU_GREATEREQUALS);}
"=="			{   BUMPSIZE; return TOKEN(MU_EQUALS);}
"!="			{   BUMPSIZE; return TOKEN(MU_NOTEQUALS);}
"&&"			{   BUMPSIZE; return TOKEN(MU_LOGICAND);}
"||"			{   BUMPSIZE; return TOKEN(MU_LOGICOR);	}
">"			{   BUMP(1); return '>'; }
"<"			{   BUMP(1); return '<'; }

{Identifier}		{
			    BUMPSIZE;
			    return yyIdentifier(text(), LVAL);
			}

<<EOF>>			{
    //terminate();
                            return 0;
			}

.			{
                            BUMP(1);
			    return *text();
			}

%%

void
Mu::Lexer::yyAddToString(Mu::UTF32Char c)
{
    if (c >= 127) utf8::utf32to8(&c, &c+1, back_inserter(stringBuffer));
    else stringBuffer.push_back(c);
}

Mu::StringType::String*
Mu::Lexer::yyReturnString()
{
    Mu::MuLangContext* c = static_cast<Mu::MuLangContext*>(as->context());
    return c->stringType()->allocate(stringBuffer);
}

int
Mu::Lexer::yyIdentifier(const char *text, Mu::parser::semantic_type& yylval)
{
    //
    //	This function determines the priority that various identifiers
    //	have during parsing. For example, if there is a type and
    //	function which both have the same scope and name, then the
    //	type will be returned. 
    //

    const Mu::NodeAssembler::ScopeState* scope = as->scopeState();

    if (Mu::Name n = as->context()->lookupName(text))
    {
	Mu::Symbol*           symbol    = 0;
	Mu::Module*           module    = 0;
	Mu::Type*             type      = 0;
	Mu::SymbolicConstant* constant  = 0;
	Mu::TypeModifier*     typemod   = 0;
	Mu::Alias*            alias     = 0;
	Mu::MemberVariable*   mvar      = 0;
	Mu::GlobalVariable*   gvar      = 0;
	Mu::Construct*        construct = 0;

	if (as->prefixScope())
	{
	    if (Mu::Symbol *s = as->prefixScope()->findSymbol(n))
	    {
                bool followedAlias = false;

		while (1)
		{
		    module    = 0;
		    type      = 0;
		    alias     = 0;
		    mvar      = 0;
		    constant  = 0;

		    for (Mu::Symbol *sym = s->firstOverload();
			 sym; 
			 sym = sym->nextOverload())
		    {
			if (!type)
			{
			    if (type  = dynamic_cast<Mu::Type*>(sym))
				continue;
			}
			
			if (!module)
			{
			    if (module = dynamic_cast<Mu::Module*>(sym))
				continue;
			}

			if (!mvar)
			{
			    if (mvar = dynamic_cast<Mu::MemberVariable*>(sym))
				continue;
			}

			if (!alias)
			{
			    if (alias  = dynamic_cast<Mu::Alias*>(sym))
				continue;
			}

			if (!constant)
			{
			    if (constant = 
				dynamic_cast<Mu::SymbolicConstant*>(sym))
				continue;
			}
		    }

		    if (type)
		    {
			LVAL._type = type;
			return dynamic_cast<Mu::VariantTagType*>(type)
                            ? TOKEN(MU_TYPECONSTRUCTOR) : TOKEN(MU_TYPE);
		    }

		    if (module)
		    {
			LVAL._module = module;
			return TOKEN(MU_MODULESYMBOL);
		    }

		    if (mvar)
		    {
			LVAL._memberVar = mvar;
			return TOKEN(MU_MEMBERVARIABLE);
		    }

		    if (constant)
		    {
			LVAL._symConstant = constant;
			return TOKEN(MU_SYMBOLICCONST);
		    }

		    if (alias)
		    {
                        followedAlias = true;
			s = alias->alias();
		    }
		    else
		    {
			LVAL._symbol = s;
			return followedAlias ? TOKEN(MU_PREFIXEDSYMBOL) : TOKEN(MU_SYMBOL);
		    }
		}
	    }

	    LVAL._name = as->context()->internName(text).nameRef();
	    return TOKEN(MU_IDENTIFIER);
	}


	//
	//  If there's a type anywhere in the current scope, that must
	//  be returned. Type symbols cannot be shadowed.
	//

	//for (int i=scope.size(); i--;)
        for (const Mu::NodeAssembler::ScopeState* ss = scope; ss; ss = ss->parent)
	{
	    //
	    //  XXX Some combination of calling rv.runtime.eval (mu eval from
	    //  python) early (during the creation of an "immediate" python
	    //  minor mode) produces a situation where ss->symbol is NULL,
	    //  hence a crash.  I'm adding this check to turn the crash into an
	    //  exception since I can't figure out how to actually fix it.
	    //
	    if (ss->symbol)
	    if (Mu::Symbol *s = ss->symbol->findSymbol(n))
	    {
                bool followedAlias = false;

		while (1)
		{
		    module    = 0;
		    type      = 0;
		    alias     = 0;
		    construct = 0;
		    typemod   = 0;
		    constant  = 0;

		    for (Mu::Symbol *sym = s->firstOverload();
			 sym; 
			 sym = sym->nextOverload())
		    {
			if (!type)
			{
			    if (type = dynamic_cast<Mu::Type*>(sym))
				continue;
			}

			if (!typemod)
			{
			    if (typemod = dynamic_cast<Mu::TypeModifier*>(sym))
				continue;
			}

			if (!module)
			{
			    if (module = dynamic_cast<Mu::Module*>(sym))
				continue;
			}

			if (!constant)
			{
			    if (constant = 
				dynamic_cast<Mu::SymbolicConstant*>(sym))
				continue;
			}

			if (!alias)
			{
			    if (alias = dynamic_cast<Mu::Alias*>(sym))
				continue;
			}

			if (!construct)
			{
			    if (construct = dynamic_cast<Mu::Construct*>(sym))
				continue;
			}
		    }

		    if (type)
		    {
			LVAL._type = type;
			return dynamic_cast<Mu::VariantTagType*>(type)
                            ? TOKEN(MU_TYPECONSTRUCTOR) : TOKEN(MU_TYPE);
		    }

		    if (typemod)
		    {
			LVAL._typeModifier = typemod;
			return TOKEN(MU_TYPEMODIFIER);
		    }

		    if (module)
		    {
			LVAL._module = module;
			return TOKEN(MU_MODULESYMBOL);
		    }

		    if (constant)
		    {
			LVAL._symConstant = constant;
			return TOKEN(MU_SYMBOLICCONST);
		    }

		    if (construct)
		    {
			LVAL._construct = construct;
			return TOKEN(MU_CONSTRUCT);
		    }

		    //
		    //  Symbol found. 
		    //

		    if (Mu::Variable *v =
			dynamic_cast<Mu::Variable*>(s))
		    {
			LVAL._symbol = s;
			return followedAlias ? TOKEN(MU_PREFIXEDSYMBOL) : TOKEN(MU_SYMBOL);
		    }

		    if (alias)
		    {
			s = alias->alias();
                        followedAlias = true;
		    }
                    else
                    {
                        if (Mu::Function* f = dynamic_cast<Mu::Function*>(s))
                        {
                            if (f->scope()->name() == f->name())
                            {
                                if (Mu::Type* t = dynamic_cast<Mu::Type*>(f->scope()))
                                {
                                    //
                                    //  Constructor: return the type instead
                                    //
                                
                                    LVAL._type = t;
                                    return dynamic_cast<Mu::VariantTagType*>(t)
                                        ? TOKEN(MU_TYPECONSTRUCTOR) : TOKEN(MU_TYPE);
                                }
                            }
                        }

		    
                        LVAL._symbol = s;
                        return followedAlias ? TOKEN(MU_PREFIXEDSYMBOL) : TOKEN(MU_SYMBOL);
                    }
		}
	    }
	}
    }

    //
    //  Intern the name and give it to the parser as a generic identifier.
    //

    LVAL._name = as->context()->internName(text).nameRef();
    return TOKEN(MU_IDENTIFIER);
}
