#ifndef __MuLang__SymbolType__h__
#define __MuLang__SymbolType__h__
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
//     * Neither the name of Jim Hourihan nor the names of its
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
#include <Mu/OpaqueType.h>
#include <iosfwd>

namespace Mu {

//
//  class SymbolType
//
//  Base type for internal symbols used by runtime
//

class SymbolType : public OpaqueType
{
  public:
    SymbolType(Context*, const char*);
    ~SymbolType();

    virtual void outputValue(std::ostream&, const Value&, bool full=false) const;
    virtual void outputValueRecursive(std::ostream&,
                                      const ValuePointer,
                                      ValueOutputState&) const;
    virtual void load();
};


class TypeSymbolType : public SymbolType
{
  public:
    TypeSymbolType(Context*, const char*);
    ~TypeSymbolType();
};

class ModuleSymbolType : public SymbolType
{
  public:
    ModuleSymbolType(Context*, const char*);
    ~ModuleSymbolType();
};

class TypeModifierSymbolType : public SymbolType
{
  public:
    TypeModifierSymbolType(Context*, const char*);
    ~TypeModifierSymbolType();
};

class FunctionSymbolType : public SymbolType
{
  public:
    FunctionSymbolType(Context*, const char*);
    ~FunctionSymbolType();
};

class VariableSymbolType : public SymbolType
{
  public:
    VariableSymbolType(Context*, const char*);
    ~VariableSymbolType();
};

class ParameterSymbolType : public SymbolType
{
  public:
    ParameterSymbolType(Context*, const char*);
    ~ParameterSymbolType();
};

} // namespace Mu

#endif // __MuLang__SymbolType__h__
