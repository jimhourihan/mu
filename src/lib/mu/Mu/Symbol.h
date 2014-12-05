#ifndef __Mu__Symbol__h__
#define __Mu__Symbol__h__
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
#include <Mu/Name.h>
#include <iosfwd>
#include <vector>
#include <algorithm>
#include <stl_ext/stl_ext_algo.h>

namespace Mu {

class Node;
class Type;
class Thread;
class Module;
class SymbolTable;
class Context;

//
//  class Symbol
//
//  Symbol is the base class for all symbols in Mu.
//
//  Things to Note: You can never add symbols from a base class
//  constructor - the symbol table calls a virtual function in the
//  symbol (load()) when the symbol is added to the table
//

class Symbol
{
  public:
    MU_GC_STUBBORN_NEW_DELETE
    friend class SymbolTable;
    friend class Node;
    friend class Language;
    friend class Context;
    friend class Module;

    //
    //	These are really symbol properties. They have no global
    //	meaning per se. The implemented language determines what these
    //	mean.
    //

    enum Modifier
    {
	None,
	Static,
	Abstract,
	Final,
	Synchronized,
	Threadsafe,
	Const,
	Transient,
	Volatile,
	Native
    };

    enum Access
    {
	Public,
	Private,
	Protected
    };

    //
    //	If the symbol depends on other symbols it can be in one of
    //	three states: UntouchedState (resolution not yet attempted),
    //	UnresolvedState (tried but failed), or ResolvedState (tried
    //	and succeeded).
    //

    enum SymbolState
    {
	UntouchedState,
	UnresolvedState,
	ResolvedState
    };


    //
    //	This union is handy to store unresolved symbols. When the
    //	symbol does not yet exist, the SymbolRef can hold a
    //	name. Later when you resolve the names it holds the actual
    //	pointer. The sizeof(Name::Ref) == sizeof(Symbol*) so there is
    //	no wasted space here. Note that the name is stored as a
    //	Name::Ref which is just a name without constructors (so that
    //	it can be used in a union).
    //

    union SymbolRef
    {
	SymbolRef() : symbol(0) {}
	explicit SymbolRef(int) : symbol(0) {}
	SymbolRef(const Symbol* s) : symbol(s) {}
	SymbolRef(Name n) { name = n.nameRef(); }
	SymbolRef(Name::Ref n) { name = n; }
	void operator=(int) { symbol=0; }

	const Symbol*	symbol;
	Name::Ref	name;

        template <class T>
        const T* symbolOfType() const { return dynamic_cast<const T*>(symbol); }
    };

    typedef STLVector<SymbolRef>::Type      SymbolRefList;

    //
    //  Use this to end variadic function arguments
    //

    typedef void* VariadicKeyword;
    #define EndArguments NULL
    //static const VariadicKeyword EndArguments = 0;

    //
    //  Other typedefs
    //

    typedef STLVector<const Symbol*>::Type  ConstSymbolVector;
    typedef STLVector<Symbol*>::Type        SymbolVector;
    typedef STLVector<Name>::Type           NameVector;
    
    //
    //	Constructors
    //

    Symbol(Context*, const char *);
    virtual ~Symbol();

    //
    //
    //

    Context*                    context() { return _context; }
    const Context*              context() const { return _context; }

    //
    //	These functions deal with the human interpretable name of a
    //	symbol. There is a NamePool which is used by all symbols.
    //

    Name			name() const { return _name; }
    QualifiedName		fullyQualifiedName() const;
    virtual String              mangledName() const;
    virtual String              mangledId() const;

    //
    //	Returns the return Type of a nodes generated by this symbol.
    //

    virtual const Type*		nodeReturnType(const Node*) const;

    bool                        usesDataNode() const { return _datanode; }

    //
    //	Each symbol is potentially a scope in which any number of
    //  other symbols may exist. This is implemented as a symbol table
    //  for each scope. The symbol table is only constructed if
    //  something is added via addSymbol{s}().
    //

    void			addSymbols(Symbol*,...);
    virtual void		addSymbol(Symbol*);

    //
    //  This "adds" the symbol to this scope, but the symbol is not
    //  visible from here. This is useful when the symbol being added
    //  is a lambda object or some other "anonymous" things which has
    //  scope, but no name.
    //

    void                        addAnonymousSymbol(Symbol*);

    //
    //	The findSymbol() function is overriden by derived classes to
    //	cope with special scope rules which involve more than one
    //	symbol table -- for instance looking up a symbol in a parent
    //	class if its not found in a class. The findSymbol() function
    //	will not find qualified names, it only looks in the scope of
    //	this. findSymbolByQualifiedName() will find the first symbol
    //	that satisfies the qualified name relative to this.
    //

    Symbol*                     findSymbol(Name);
    virtual const Symbol*       findSymbol(Name) const;

    Symbol*			findSymbolByQualifiedName(QualifiedName,
                                                          bool restricted=true);
    const Symbol*		findSymbolByQualifiedName(QualifiedName,
                                                          bool restricted=true) const;

    //
    //  When find symbols by fully qualified name, there is a
    //  possibility that multiple symbols will satisfy the path name
    //  (because of overloading). These functions return all possible
    //  symbols that could match.
    //

    virtual void        	findSymbols(QualifiedName, SymbolVector&);
    virtual void                findSymbols(QualifiedName, ConstSymbolVector&) const;

    //
    //	findSymbolOfType() is a convenience function which given a
    //	pointer to the type desired will find the overloaded symbol
    //	which matches the type. For example:
    //
    //	    Type *t = sym->findSymbolOfType<Type>("foo");
    //
    //	will find the symbol named "foo" that is a Type.
    //

    template<class T>
    T*				findSymbolOfType(Name name);

    template<class T>
    const T*			findSymbolOfType(Name name) const;

    template<class T>
    T*				findSymbolOfTypeByQualifiedName(Name name,
                                                                bool restricted=true);

    template<class T>
    const T*			findSymbolOfTypeByQualifiedName(Name name,
                                                                bool restricted=true) const;

    template<class T>
    const T*			findSymbolOfTypeByMangledName(const String&,
                                                              QualifiedName) const;

    template<class T>
    SymbolVector		findSymbolsOfType(QualifiedName);

    template<class T>
    ConstSymbolVector           findSymbolsOfType(QualifiedName) const;


    //
    //	scope() returns the symbol which represents the scope in which
    //	this symbol lives. Only the globalScope() symbol should return
    //	0 from scope(). [So scope()->scope() is the grand scope() etc]
    //

    Symbol*			scope()			{ return _scope; }
    const Symbol*		scope() const		{ return _scope; }

    Symbol*			globalScope();
    const Symbol*		globalScope() const;

    Module*                     globalModule();
    const Module*               globalModule() const;

    bool                        isSearchable() const { return _searchable; }

    //
    //	If the symbol is an overloaded name (in the scope in which it
    //	lives) these functions will give access to the overloading
    //	symbols.
    //

    Symbol*			nextOverload()		{ return _overload; }
    const Symbol*		nextOverload() const	{ return _overload; }

    Symbol*			firstOverload();
    const Symbol*		firstOverload() const;

    virtual void		output(std::ostream&) const;
    virtual void		outputNode(std::ostream&,const Node*) const;

    SymbolTable*		symbolTable() const	{ return _symbolTable;}

    //
    //  Primary symbols are marked by the parser to indicate that they
    //  are *not* symbols loaded by require/use, etc. In other words,
    //  they need to be saved.
    //

    bool                        isPrimary() const { return _primary; }

    //
    //  Fills vector with symbols this symbol is dependant on (when
    //  resolved).
    //
    
    virtual void                symbolDependancies(ConstSymbolVector&) const;

  protected:
    void			appendOverload(Symbol*);
    void			append(Symbol*);

    int				symbolState() const	{ return _state; }
    bool			interned() const;

    //
    //	resolve() and resolveSymbols() are both const functions which
    //	are meant to work on mutable data memebers. Some symbols are
    //	dependent on other symbols -- like a variable and its return
    //	type. If the return type of a variable becomes available after
    //	the variable is declared it must be resolved at a later time.
    //

    void			resolve() const;

    //
    //	load() - is called when symbol is first added to a symbol
    //	table. If the symbol "contains" more symbols (like a package)
    //  then it can add them there.
    //

   virtual void                 load();

    //
    //	resolveSymbols() - any symbols that this is depedant on (like
    //	a functions return value symbol) should be resolved in this
    //	function. If the needed symbols are for some reason not
    //	available the function should return false indicating that it
    //	is still unresolved. Note: cached symbols must be declared
    //	mutable since resolveSymbols() is const.
    //

    bool			isResolved() const 
				{ return _state==ResolvedState; }

    virtual bool		resolveSymbols() const;

  protected:
    Symbol(Context* c) : _context(c) { init(Name()); }
    void init(Name);

  protected:
    Name			_name;
    Context*                    _context;
    Symbol*			_scope;
    Symbol*			_overload;
    SymbolTable*		_symbolTable;
    mutable unsigned int	_state	    : 2;
    unsigned int		_access	    : 2;
    unsigned int		_modifier   : 4;
    bool			_searchable : 1;
    bool                        _datanode   : 1;
    mutable bool                _primary    : 1;
    mutable bool		_resolving;//  : 1;
};


//----------------------------------------------------------------------

template<class T>
T* Symbol::findSymbolOfType(Name name)
{
    if (Symbol *s = findSymbol(name))
    {
	for (s = s->firstOverload(); s; s = s->nextOverload())
	{
            if ( T* typePointer = dynamic_cast<T*>(s) )
            {
                return typePointer;
            }
	}
    }

    return 0;
}


template<class T>
const T* Symbol::findSymbolOfType(Name name) const
{
    if (const Symbol *symbol = findSymbol(name))
    {
	while (symbol)
	{
            if (const T* typePointer = dynamic_cast<const T*>(symbol) )
            {
                return typePointer;
            }

	    symbol = symbol->nextOverload();
	}
    }

    return 0;
}

template<class T>
T* Symbol::findSymbolOfTypeByQualifiedName(QualifiedName name, bool restricted)
{
    if (Symbol *s = findSymbolByQualifiedName(name, restricted))
    {
	for (s = s->firstOverload(); s; s = s->nextOverload())
	{
            if ( T* typePointer = dynamic_cast<T*>(s) )
            {
                return typePointer;
            }
	}
    }

    return 0;
}


template<class T>
const T* Symbol::findSymbolOfTypeByQualifiedName(QualifiedName name, 
                                                 bool restricted) const
{
    if (const Symbol *symbol = findSymbolByQualifiedName(name, restricted))
    {
	while (symbol)
	{
            if (const T* typePointer = dynamic_cast<const T*>(symbol) )
            {
                return typePointer;
            }

	    symbol = symbol->nextOverload();
	}
    }

    return 0;
}

template<class T>
Symbol::SymbolVector
Symbol::findSymbolsOfType(QualifiedName name)
{
    SymbolVector s;
    findSymbols(name, s);
    s.erase( std::remove_if(s.begin(), 
                            s.end(), 
                            stl_ext::IsNotA_p<Symbol, T>()),
             s.end());
    return s;
}

template<class T>
Symbol::ConstSymbolVector
Symbol::findSymbolsOfType(QualifiedName name) const
{
    ConstSymbolVector s;
    findSymbols(name, s);
    s.erase( std::remove_if(s.begin(), 
                            s.end(), 
                            stl_ext::IsNotA_p<const Symbol, const T>()),
                   s.end());
    return s;
}

template<class T>
const T*
Symbol::findSymbolOfTypeByMangledName(const Mu::String& mangledName,
                                      QualifiedName name) const
{
    ConstSymbolVector s = findSymbolsOfType<T>(name);

    for (int i=0; i < s.size(); i++)
    {
        if (s[i]->mangledName() == mangledName) 
            return static_cast<const T*>(s[i]);
    }

    return 0;
}

std::ostream& operator << (std::ostream &, const Symbol &);

} // namespace Mu

#endif // __Mu__Symbol__h__
