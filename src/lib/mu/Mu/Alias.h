#ifndef __Mu__Alias__h__
#define __Mu__Alias__h__
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

//
//  class Alias
//
//  An alias is a symbol that points to another symbol. An alias has no
//  particular type and no node should be created by it. The alias is
//  primarily used by a parser to keep track of typedef and similar. Note
//  that an alias necessarily represents a whole family of similarily named
//  symbols. If the alias points to a type, it may also be pointing to
//  constructors for that type.
//

class Alias : public Symbol
{
  public:
    Alias(Context* context, const char *name, Symbol *symbol);
    Alias(Context* context, const char *name, const char *symbol);
    virtual ~Alias();

    //
    //	Symbol API
    //
    
    virtual const Type* nodeReturnType(const Node*) const;
    virtual void outputNode(std::ostream&,const Node*) const;
    virtual void symbolDependancies(ConstSymbolVector&);

    //
    //	Output the symbol
    //

    virtual void output(std::ostream&) const;

    //
    //	Alias API
    //

    void set(const Symbol *s);
    const Symbol* alias() const;
    Symbol* alias();

  protected:
    virtual bool resolveSymbols() const;

  private:
    mutable SymbolRef _symbol;
};

} // namespace Mu

#endif // __Mu__Alias__h__
