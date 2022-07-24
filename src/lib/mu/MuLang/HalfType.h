#ifndef __MuLang__HalfType__h__
#define __MuLang__HalfType__h__
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
#include <Imath/half.h>
#include <Imath/halfLimits.h>

namespace Mu {

//
//  class HalfType
//
//  Basic integer type: uses the normal machine 32 bit integer type.
//

class HalfType : public PrimitiveType
{
  public:
    HalfType(Context*);
    ~HalfType();

    //
    //	Type API
    //

    virtual PrimitiveObject* newObject() const;
    virtual Value nodeEval(const Node*, Thread&) const;
    virtual void nodeEval(void*, const Node*, Thread&) const;

    //
    //	Output the symbol name
    //	Output the appropriate Value in human readable form
    //

    virtual void outputValue(std::ostream&, const Value&, bool full=false) const;
    virtual void outputValueRecursive(std::ostream&, 
                                      const ValuePointer,
                                      ValueOutputState&) const;
    
    //
    //	Load function is called when the symbol is added to the
    //	context.
    //

    virtual void load();

    //
    //	Casts
    //

    static NODE_DECLARATION(defaultHalf,short);
    static NODE_DECLARATION(toFloat,float);
    static NODE_DECLARATION(dereference,short);
    static NODE_DECLARATION(int2half,short);
    static NODE_DECLARATION(int642half,short);
    static NODE_DECLARATION(float2half,short);
    static NODE_DECLARATION(double2half,short);

    //
    //	Operators
    //

    static NODE_DECLARATION(add,short);
    static NODE_DECLARATION(sub,short);
    static NODE_DECLARATION(mult,short);
    static NODE_DECLARATION(div,short);
    static NODE_DECLARATION(mod,short);
    static NODE_DECLARATION(negate,short);
    static NODE_DECLARATION(conditionalExpr,short);

    static NODE_DECLARATION(assign,Pointer);
    static NODE_DECLARATION(assignPlus,Pointer);
    static NODE_DECLARATION(assignSub,Pointer);
    static NODE_DECLARATION(assignMult,Pointer);
    static NODE_DECLARATION(assignDiv,Pointer);
    static NODE_DECLARATION(assignMod,Pointer);

    static NODE_DECLARATION(preInc,short);
    static NODE_DECLARATION(postInc,short);
    static NODE_DECLARATION(preDec,short);
    static NODE_DECLARATION(postDec,short);

    static NODE_DECLARATION(equals,bool);
    static NODE_DECLARATION(notEquals,bool);
    static NODE_DECLARATION(greaterThan,bool);
    static NODE_DECLARATION(lessThan,bool);
    static NODE_DECLARATION(greaterThanEq,bool);
    static NODE_DECLARATION(lessThanEq,bool);

    static NODE_DECLARATION(print,void);
    static NODE_DECLARATION(round,short);
    static NODE_DECLARATION(bits,short);
    static NODE_DECLARATION(convert,short);
};

inline half shortToHalf(short s) { half h; h.setBits((unsigned short)s); return h; }
inline short halfToShort(half h) { return short(h.bits()); }
#define NODE_ARG_HALF(I) shortToHalf(NODE_ARG(I, short))
#define NODE_RETURN_HALF(H) NODE_RETURN(halfToShort(H))


} // namespace Mu

#endif // __MuLang__HalfType__h__
