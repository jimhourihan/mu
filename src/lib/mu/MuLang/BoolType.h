#ifndef __MuLang__BoolType__h__
#define __MuLang__BoolType__h__
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
#include <Mu/Node.h>
#include <Mu/PrimitiveObject.h>
#include <Mu/PrimitiveType.h>
#include <iosfwd>

namespace Mu {

//
//  class BoolType
//
//  Boolean type. Includes most of the flow control constructs as
//  well. 
//

class BoolType : public Mu::PrimitiveType
{
  public:
    BoolType(Context*);
    ~BoolType();

    //
    //	Type API
    //

    virtual Mu::PrimitiveObject* newObject() const;
    virtual Mu::Value nodeEval(const Mu::Node*, Mu::Thread&) const;
    virtual void nodeEval(void*, const Mu::Node*, Mu::Thread&) const;

    //
    //	Output the symbol name
    //	Output the appropriate Value in human readable form
    //

    virtual void outputValue(std::ostream&, const Mu::Value&, bool full=false) const;
    virtual void outputValueRecursive(std::ostream&, 
                                      const Mu::ValuePointer,
                                      ValueOutputState&) const;

    //
    //	Load function is called when the symbol is added to the
    //	context.
    //

    virtual void load();

    //
    //	Casts
    //

    static NODE_DECLARATION(defaultBool,bool);
    static NODE_DECLARATION(dereference,bool);

    //
    //	Operators
    //

    static NODE_DECLARATION(assign,Mu::Pointer);
    static NODE_DECLARATION(logicalNot,bool);
    static NODE_DECLARATION(logicalAnd,bool);
    static NODE_DECLARATION(logicalOr,bool);
    static NODE_DECLARATION(conditionalExpr,bool);

    static NODE_DECLARATION(eq, bool);
    static NODE_DECLARATION(neq, bool);

    //
    //	Language Constructs
    //

    static NODE_DECLARATION(__if,void);
    static NODE_DECLARATION(__if_else,void);
    static NODE_DECLARATION(__for,void);
    static NODE_DECLARATION(__repeat,void);
    static NODE_DECLARATION(__for_each_fixed_array,void);
    static NODE_DECLARATION(__for_each_dynamic_array,void);
    static NODE_DECLARATION(__for_each_list,void);
    static NODE_DECLARATION(__for_index_dynamic_array,void);
    static NODE_DECLARATION(__for_index_fixed1_array,void);
    static NODE_DECLARATION(__for_index_fixed2_array,void);
    static NODE_DECLARATION(__for_index_fixed3_array,void);
    static NODE_DECLARATION(__while,void);
    static NODE_DECLARATION(__do_while,void);

    static NODE_DECLARATION(__break,void);
    static NODE_DECLARATION(__continue,void);

    //
    //	Functions
    //

    static NODE_DECLARATION(assertion,void);

};

} // namespace Mu

#endif // __MuLang__BoolType__h__
