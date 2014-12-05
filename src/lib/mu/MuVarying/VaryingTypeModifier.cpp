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

#include "VaryingTypeModifier.h"
#include "VaryingType.h"
#include "VaryingVecfType.h"
#include "VaryingBoolType.h"
#include "VaryingFloatType.h"
#include "VaryingComponentType.h"
#include <MuLang/MuLangContext.h>

namespace Mu {
using namespace std;

VaryingTypeModifier::VaryingTypeModifier(Context* c) 
    : TypeModifier(c, "varying"),
      _vBoolType(0),
      _vFloatType(0),
      _vIntType(0),
      _vV4fType(0),
      _vV3fType(0),
      _vV2fType(0),
      _componentType(0)
{
}

VaryingTypeModifier::~VaryingTypeModifier() {}

const Type*
VaryingTypeModifier::transform(const Type* type, Context *mc) const
{
    MuLangContext *c = static_cast<MuLangContext*>(mc);

    if (type == c->floatType())
    {
	if (!_vFloatType)
	{
	    _vFloatType = 
                new VaryingFloatType(mc, static_cast<const FloatType*>(c->floatType()));
	    
	    c->globalScope()->addSymbol(_vFloatType);

	    _componentType = 
		new VaryingComponentType(mc, "varying vector component",
					 (VaryingFloatType*)
					 _vFloatType);

	    c->globalScope()->addSymbol(_componentType);
	}

	return _vFloatType;
    }
    else if (type == c->boolType())
    {
	if (!_vBoolType)
	{
	    _vBoolType = 
                new VaryingBoolType(mc, static_cast<const BoolType*>(c->boolType()));
	    
	    c->globalScope()->addSymbol(_vBoolType);
	}

	return _vBoolType;
    }
    else if (type == c->intType())
    {
    }
    else if (type == c->vec2fType())
    {
	if (!_vV2fType)
	{
	    _vV2fType = new VaryingVecfType(mc, "varying vector float[2]", 
					    c->vec2fType(),
					    (VaryingComponentType*)
					    _componentType);
	    
	    c->globalScope()->addSymbol(_vV2fType);
	}

	return _vV2fType;
    }
    else if (type == c->vec3fType())
    {
	if (!_vV3fType)
	{
	    _vV3fType = new VaryingVecfType(mc, "varying vector float[3]", 
					    c->vec3fType(),
					    (VaryingComponentType*)
					    _componentType);
	    
	    c->globalScope()->addSymbol(_vV3fType);
	}

	return _vV3fType;
    }
    else if (type == c->vec4fType())
    {
	if (!_vV4fType)
	{
	    _vV4fType = new VaryingVecfType(mc, "varying vector float[4]", 
					    c->vec4fType(),
					    (VaryingComponentType*)
					    _componentType);
	    
	    c->globalScope()->addSymbol(_vV4fType);
	}

	return _vV4fType;
    }

    return 0;
}

} // namespace Mu
