#ifndef __Mu__SymbolicConstant__h__
#define __Mu__SymbolicConstant__h__
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
#include <Mu/Value.h>

namespace Mu {
class Type;

namespace Archive {
class Reader;
class Writer;
}

class SymbolicConstant : public Symbol
{
  public:
    SymbolicConstant(Context* context, const char *name, const Type *, const Value &);
    SymbolicConstant(Context* context, const char *name, const char *type, const Value &);
   ~SymbolicConstant();

    //
    //	Symbol API
    //
    
    virtual const Type* nodeReturnType(const Node*) const;
    virtual void outputNode(std::ostream&,const Node*) const;

    //
    //	Output the symbol
    //

    virtual void output(std::ostream&) const;

    //
    //	SymbolicConstant API
    //

    const Type*	type() const;

    //
    //	Value
    //

    Value value() const { return _value; }
    void setValue(Value v) { _value = v; }

  protected:
    virtual bool resolveSymbols() const;

  private:
    mutable SymbolRef	_type;
    Value		_value;

    friend class Archive::Reader;
    friend class Archive::Writer;
};


} // namespace Mu

#endif // __Mu__SymbolicConstant__h__
