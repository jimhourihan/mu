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


#ifndef __MU_H__
#define __MU_H__

#include <Mu/Alias.h>
#include <Mu/Archive.h>
#include <Mu/BaseFunctions.h>
#include <Mu/Class.h>
#include <Mu/ClassInstance.h>
#include <Mu/config.h>
#include <Mu/Construct.h>
#include <Mu/Context.h>
#include <Mu/Environment.h>
#include <Mu/Exception.h>
#include <Mu/FreeVariable.h>
#include <Mu/Function.h>
#include <Mu/FunctionObject.h>
#include <Mu/FunctionSpecializer.h>
#include <Mu/FunctionType.h>
#include <Mu/GarbageCollector.h>
#include <Mu/GlobalVariable.h>
#include <Mu/HashTable.h>
#include <Mu/Interface.h>
#include <Mu/InterfaceImp.h>
#include <Mu/MachineRep.h>
#include <Mu/MemberFunction.h>
#include <Mu/MemberVariable.h>
#include <Mu/Module.h>
#include <Mu/Name.h>
#include <Mu/Namespace.h>
#include <Mu/NilType.h>
#include <Mu/NodeAssembler.h>
#include <Mu/NodeFunc.h>
#include <Mu/Node.h>
#include <Mu/NodePatch.h>
#include <Mu/NodePrinter.h>
#include <Mu/NodeSimplifier.h>
#include <Mu/NodeVisitor.h>
#include <Mu/Object.h>
#include <Mu/ParameterModifier.h>
#include <Mu/ParameterVariable.h>
#include <Mu/PartialApplicator.h>
#include <Mu/PrimitiveObject.h>
#include <Mu/PrimitiveType.h>
#include <Mu/Process.h>
#include <Mu/ReferenceType.h>
#include <Mu/Signature.h>
#include <Mu/StackVariable.h>
#include <Mu/StringHashTable.h>
#include <Mu/Symbol.h>
#include <Mu/SymbolicConstant.h>
#include <Mu/SymbolTable.h>
#include <Mu/Thread.h>
#include <Mu/Type.h>
#include <Mu/TypeModifier.h>
#include <Mu/TypePattern.h>
#include <Mu/Unresolved.h>
#include <Mu/Value.h>
#include <Mu/Variable.h>
#include <Mu/Vector.h>


#endif    // End #ifdef __MU_H__
