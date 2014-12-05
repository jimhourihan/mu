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

#include "VaryingObject.h"

namespace Mu {
using namespace std;

VaryingObject::VaryingObject(const VaryingType* c, 
			     size_t s0,
			     size_t s1,
			     size_t s2)
    : Object(c),
      _assigned(false),
      _myData(true),
      _component(0),
      _other(0)
{
    _size[0] = s0;
    _size[1] = s1;
    _size[2] = s2;
    size_t s = c->elementRep()->size() * size();
    _data = (byte*)arena().allocate(s);
    memset(_data, 0, s);
}

VaryingObject::VaryingObject(const VaryingType* c, 
			     VaryingObject::byte* data,
			     size_t s0,
			     size_t s1,
			     size_t s2)
    : Object(c),
      _assigned(true),
      _myData(false),
      _component(0),
      _other(0)
{
    _size[0] = s0;
    _size[1] = s1;
    _size[2] = s2;
    size_t s = c->elementRep()->size() * size();
    _data = data;
}

VaryingObject::VaryingObject(const VaryingObject* o)
    : Object(o->varyingType()),
      _assigned(false),
      _myData(true),
      _component(0),
      _other(0)
{
    _size[0] = o->size(0);
    _size[1] = o->size(1);
    _size[2] = o->size(2);
    size_t s = varyingType()->elementRep()->size() * size();
    _data = (byte*)arena().allocate(s);
    memcpy(_data, o->_data, s);
}

VaryingObject::VaryingObject(VaryingObject *o, size_t component)
    : Object(o->varyingType()),
      _assigned(false),
      _myData(false),
      _component(component),
      _other(o)
{
    _size[0] = o->size(0);
    _size[1] = o->size(1);
    _size[2] = o->size(2);
    o->setAssigned(true);
    _data = o->_data;
}

VaryingObject::~VaryingObject()
{ 
    if (_myData) 
    {
	size_t s = varyingType()->elementRep()->size() * size();
	arena().deallocate(_data, s);
    }
}

} // namespace Mu
