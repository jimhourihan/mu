#ifndef __Mu__Variable__h__
#define __Mu__Variable__h__
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

namespace Mu {

class Type;
class Function;

//
//  class Variable
//
//  Base class for local, global, and data member variables.
//

class Variable : public Symbol
{
  public:
    //
    //	Types
    //	

    typedef unsigned int AccessPermissions;

    //
    //  Variable Attributes
    //  Some of these are set after the fact.
    //

    enum Attribute	
    { 
        NoVariableAttr  = 0,
	Readable        = 1 << 0,
	Writable        = 1 << 1,
        ReadWrite       = Readable | Writable,
        SingleAssign    = 1 << 2,
        ImplicitType    = 1 << 3,
        SingleUse       = 1 << 4,
    };

    typedef unsigned int Attributes;

    //
    //	The storageClass is the type of value stored in the
    //	variable. The address parameter indicates the Variable's
    //	position in the heap or stack (this may change). The
    //	permission is mostly for parsers since these permission are
    //	not enforced at run-time.
    //

    Variable(Context* context,
             const char *name, 
	     const Type *storageClass, 
	     int address=0,
	     Attributes a=ReadWrite);
    
    Variable(Context* context,
             const char *name, 
	     const char *storageClass, 
	     int address=0,
	     Attributes a=ReadWrite);

    virtual ~Variable();

    void init(Attributes);

    //
    //	Returns the storage class that was passed in when
    //	constructed. Why is this virtual?
    //
    //  NOTE: storageClass() will return 0 if the symbol
    //  cannot be resolved (yet).
    //

    virtual const Type*	    storageClass() const;
    virtual Name	    storageClassName() const;

    //
    //  If the variable is "unresolved" it may become resolved
    //  later. At that point it will gain a type
    //

    virtual void            setStorageClass(const Type*);

    //
    //	If the variable object is initialized. This flag is set
    //	externally.
    //

    bool		    isInitialized() const   { return _initialized;}
    void		    setInitialized()	    { _initialized=1;}

    bool                    isImplicitlyTyped() const { return _implicitType;}

    //
    //	From Symbol API: normally returns the reference type of the
    //	storageClass(). Variable nodes are either lvalues or rvalues,
    //	either way they return a reference. In the rvalue case, the
    //	reference needs to be de-referenced.
    //

    virtual const Type*	    nodeReturnType(const Node*) const;

    //
    //	From Symbol: human readable output
    //
    
    virtual void	    output(std::ostream &o) const;

    virtual void            symbolDependancies(ConstSymbolVector&) const;

    //
    //	Address passed in to constructor. Usually a parser will set
    //	the address of a Variable after it knows how it wants to
    //	layout the stack or heap for a block.
    //

    int			    address() const	    { return _address; }
    void		    setAddress(int a)	    { _address=a; }

    //
    //	Special access. You can pass these functions to return
    //	specialized functions for dereferencing, referencing, and
    //	setting the variable value. By default, these all return 0.
    //

    virtual const Function* referenceFunction() const;
    virtual const Function* extractFunction() const;

    //
    //  The node assembler may redefine the attributes for a variable
    //  if it discovers that it is single assignment or single use
    //

    Attributes              attributes() const;
    void                    setAttributes(Attributes a) { init(a); }

  protected:

    //
    //	Variable needs to resolve the storage type pointer.
    //

    virtual bool	    resolveSymbols() const;

  protected:
    mutable SymbolRef	    _type;
    int			    _address;
    bool                    _singleAssignment : 1;
    bool                    _singleUse        : 1;
    bool		    _initialized      : 1;
    bool                    _readable         : 1;
    bool                    _writable         : 1;
    bool                    _singleAssign     : 1;
    bool                    _implicitType     : 1;
};


} // namespace Mu

#endif // __Mu__Variable__h__

