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

#include "VectorTypeModifier.h"
#include "MuLangContext.h"
#include "FixedArrayType.h"
#include "VectorType.h"
#include <Mu/Type.h>

namespace Mu {
using namespace std;

VectorTypeModifier::VectorTypeModifier(Context* c)
    : TypeModifier(c, "vector"),
      _v4fType(0),
      _v3fType(0),
      _v2fType(0)
{
}

VectorTypeModifier::~VectorTypeModifier()
{
}

const Type*
VectorTypeModifier::transform(const Type* type, Context *context) const
{
    MuLangContext *c = static_cast<MuLangContext*>(context);
    Type* float4 = c->arrayType(c->floatType(), 1, 4);

    Context::PrimaryBit fence(context, false);

    if (type == float4)
    {
	if (!_v4fType)
	{
	    _v4fType = new Vector4fType(c, "vector float[4]",
					c->floatType(),
					Vector4FloatRep::rep());

	    c->globalScope()->addSymbol(_v4fType);
	}

	return _v4fType;
    }

    Type* float3 = c->arrayType(c->floatType(), 1, 3);

    if (type == float3)
    {
	if (!_v3fType)
	{
	    _v3fType = new Vector3fType(c, "vector float[3]",
					c->floatType(),
					Vector3FloatRep::rep());

	    c->globalScope()->addSymbol(_v3fType);
	}

	return _v3fType;
    }

    Type* float2 = c->arrayType(c->floatType(), 1, 2);

    if (type == float2)
    {
	if (!_v2fType)
	{
	    _v2fType = new Vector2fType(c, "vector float[2]",
					c->floatType(),
					Vector2FloatRep::rep());

	    c->globalScope()->addSymbol(_v2fType);
	}

	return _v2fType;
    }

    return 0;
}


} // namespace Mu
