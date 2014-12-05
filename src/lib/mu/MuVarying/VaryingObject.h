#ifndef __MuLang__VaryingObject__h__
#define __MuLang__VaryingObject__h__
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
#include <vector>
#include <Mu/Object.h>
#include "VaryingType.h"

namespace Mu {

//
//  class VaryingObject
//
//  VaryingObject is similar to FixedArray, but the number of dimensions
//  and their sizes is stored with the object. Operations on VaryingObjects
//  generally appear as scalar operations (except for derivatives).
//
//  VaryingObject is currently limited to a three dimensions.
//
//  Two of the constructors allow you to pass in a region of memory
//  with the given dimensions. If you pass memory into the object it
//  will not free it. The memory is read/write and assumed to be
//  pre-assigned.
//

class VaryingObject : public Object
{
  public:
    typedef unsigned char byte;

    //
    //	Manages its own memory
    //

    VaryingObject(const VaryingType*, 
		  size_t size0, 
		  size_t size1=0, 
		  size_t size2=0);

    //
    //	Mostly for external data, the VaryingObject will not attempt
    //	to free the passed in data.
    //

    VaryingObject(const VaryingType*,
		  byte* data,
		  size_t size0, 
		  size_t size1=0, 
		  size_t size2=0);

    //
    //	Copies of the VaryingObject
    //

    VaryingObject(const VaryingObject*);

    //
    //	Used to create a component reference object
    //

    VaryingObject(VaryingObject*, size_t component);

    ~VaryingObject();

    const VaryingType* varyingType() const 
	{ return static_cast<const VaryingType*>(type()); }

    //
    //	Raw data
    //

    template <typename T> T* data() { return reinterpret_cast<T*>(_data); }

    //
    //	Sizes are returned in number of elements not bytes
    //

    size_t size() const;
    size_t size(size_t i) const { return _size[i]; }

    //
    //	The varying component class uses this to determine which
    //	component is being referred to.
    //

    size_t component() const { return _component; }

    //
    //	Element
    //

    template <typename T> T& element(size_t i) 
	{ return data<T>()[i]; }

    template <typename T> T& element(size_t i, size_t j) 
	{ return data<T>()[i * size(0) + j]; }

    template <typename T> T& element(size_t i, size_t j, size_t k)
	{ return data<T>()[i * size(0) * size(1) + j * size(1) + k]; }

    byte* elementPointer(int i)
	{return &data<byte>()[i * varyingType()->elementRep()->size()]; }

    byte* elementPointer(int i, int j)
    {
	size_t s = varyingType()->elementRep()->size();
	return &data<byte>()[s * (i * size(0) + j)];
    }

    byte* elementPointer(int i, int j, int k)
    {
	size_t s = varyingType()->elementRep()->size();
	return &data<byte>()[s * (i * size(0) * size(1) + j * size(1) + k)];
    }

    //
    //	"One bit reference counting". Perhaps this should be converted
    //	into full-on reference counting?
    //

    bool    assigned() const { return _assigned; }
    void    setAssigned(bool b) { _assigned = b; }

protected:
    VaryingObject();
    friend class VaryingType;

private:
    byte*	    _data;
    VaryingObject*  _other;
    size_t	    _size[3];
    unsigned int    _component: 5;
    bool	    _assigned : 1;
    bool	    _myData   : 1;
};

inline size_t 
VaryingObject::size() const
{
    if (_size[2]) return _size[0] * _size[1] * _size[2];
    else if (_size[1]) return _size[0] * _size[1];
    else return _size[0];
}

} // namespace Mu

#endif // __MuLang__VaryingObject__h__
