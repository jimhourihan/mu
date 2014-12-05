#ifndef __MuLang__FixedArray__h__
#define __MuLang__FixedArray__h__
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
#include <Mu/ClassInstance.h>
#include <MuLang/FixedArrayType.h>

namespace Mu {

//
//  class FixedArray
//
//  FixedArray is a ClassInstance which manages a fixed (at creation time)
//  amount of memory. The memory can be used to hold any primitive value
//  type. If the element type (gleaned from the ArrayType) is a Pointer
//  type, it is assumed to be a reference type and the array elemenets will
//  be marked by the garbage sweep algorithm.
//

class FixedArray : public ClassInstance
{
  public:
    typedef unsigned char byte;

    const FixedArrayType* arrayType() const 
	{ return static_cast<const FixedArrayType*>(type()); }

    size_t size() const;
    size_t size(size_t i) const { return arrayType()->dimensions()[i]; }

    static Pointer construct(Thread&, const char* type, Pointer value);


    template <typename T> T& element(size_t i) 
	{ return data<T>()[i]; }

    template <typename T> T& element(size_t i, size_t j) 
	{ return data<T>()[i * size(0) + j]; }

    template <typename T> T& element(size_t i, size_t j, size_t k)
	{ return data<T>()[i * size(0) * size(1) + j * size(1) + k]; }

    template <typename T> const T& element(size_t i) const
	{ return data<T>()[i]; }

    template <typename T> const T& element(size_t i, size_t j) const
	{ return data<T>()[i * size(0) + j]; }

    template <typename T> const T& element(size_t i, size_t j, size_t k) const
	{ return data<T>()[i * size(0) * size(1) + j * size(1) + k]; }

    byte* elementPointer(int i)
	{return &data<byte>()[i * arrayType()->elementRep()->size()]; }

    byte* elementPointer(int i, int j)
    {
	size_t s = arrayType()->elementRep()->size();
	return &data<byte>()[s * (i * size(0) + j)];
    }

    byte* elementPointer(int i, int j, int k)
    {
	size_t s = arrayType()->elementRep()->size();
	return &data<byte>()[s * (i * size(0) * size(1) + j * size(1) + k)];
    }

    const byte* elementPointer(int i) const
	{return &data<const byte>()[i * arrayType()->elementRep()->size()]; }

    const byte* elementPointer(int i, int j) const
    {
	size_t s = arrayType()->elementRep()->size();
	return &data<const byte>()[s * (i * size(0) + j)];
    }

    const byte* elementPointer(int i, int j, int k) const
    {
	size_t s = arrayType()->elementRep()->size();
	return &data<const byte>()[s*(i * size(0) * size(1) + j * size(1) +k)];
    }

protected:
    FixedArray(const FixedArrayType*, size_t size);
    FixedArray(Thread&, const char*);
    ~FixedArray();
};

} // namespace Mu

#endif // __MuLang__FixedArray__h__
