#ifndef __Mu__PartialEval__h__
#define __Mu__PartialEval__h__
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
#include <Mu/Function.h>
#include <Mu/NodeAssembler.h>
#include <Mu/SymbolTable.h>
#include <Mu/ParameterVariable.h>
#include <Mu/TypeVariable.h>
#include <map>
#include <vector>

namespace Mu {
class Variable;

//
//  Takes a function and an argument list and returns a new function with
//  some of the parameter replaced by constants.
//

class FunctionSpecializer
{
  public:
    typedef Function::ArgumentVector                 ArgumentVector;
    typedef std::vector<bool>                        ArgumentMask;
    typedef NodeAssembler::NodeList                  NodeList;
    typedef NodeAssembler::SymbolList                SymbolList;
    typedef ParameterVariable*                       Param;
    typedef STLMap<const Param, int>::Type           IndexMap;
    typedef STLMap<const Param, Param>::Type         ParameterMap;
    typedef STLMap<const Variable*, Variable*>::Type VariableMap;
    typedef STLVector<const Variable*>::Type         Variables;
    typedef SymbolTable::SymbolHashTable             SymbolHashTable;
    typedef SymbolTable::Item                        Item;
    typedef TypeVariable::Bindings                   TypeBindings;

    FunctionSpecializer(const Function*, Process*, Thread*);
    ~FunctionSpecializer();

    Function* partiallyEvaluate(const ArgumentVector&,
                                const ArgumentMask&);

    Function* specialize(const TypeBindings&);

    Function* result() const { return _lambda; }

  private:
    void                accumulateVariables(const Symbol*);
    Node*               translate(const Node*);
    const Type*         translate(const Type*);
    void                declareVariables();
    void                doit(const char*, SymbolList, bool);
    Node*               callDirectly();

  private:
    Node*               _root;
    NodeAssembler       _as;
    const Function*     _f;
    Function*           _lambda;
    ArgumentVector      _args;
    ArgumentMask        _mask;
    IndexMap            _originalIndex;
    ParameterMap        _map;
    Variables           _variables;
    VariableMap         _variableMap;
    TypeBindings        _typeBindings;
};


} // namespace Mu

#endif // __Mu__PartialEval__h__
