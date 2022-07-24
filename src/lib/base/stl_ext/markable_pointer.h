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
//     * Neither the name of stl_ext nor the names of its
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
#ifndef __stl_ext__markable_pointer__h__
#define __stl_ext__markable_pointer__h__
#include <stl_ext/stl_ext_config.h>
#include <vector>
#include <stdlib.h>

namespace stl_ext {

//
//  class markable_pointer
//
//  This class allows you to add a single bit of data to any pointer
//  (for when you're really squeezed for bits). The assumption is that
//  the object being pointed to has alignment which always leaves the
//  least significant bit 0. With RISC machines, its generally the
//  case that the two least significant bits are 0 so usually you have
//  some room to spare. If the machine does not have this behavior
//  normallly, you need to make sure the object allocator aligns the
//  memory thusly.
//
//  Use the supplied markable_cast<> function to cast from a markable
//  pointer to a pointer to your object type. For example:
//
//	Foo *foo_ptr = get_foo_pointer();
//	markable_pointer p = foo_ptr;
//	p.mark(true);
//	if (p.mark()) do_something();
//	Foo *the_ptr = markable_cast<Foo>(p);
//

class STL_EXT_EXPORT markable_pointer
{
  public:
    typedef size_t ptr;
    typedef markable_pointer& reference;

    markable_pointer() : _p(0) {}
    markable_pointer(void* p) : _p((ptr)p) {}

    void	    mark(bool b)	{ if (b) _p |= 1; else _p &= ~1; }
    bool	    mark() const	{ return _p & 1; }

		    operator void* ()	{ return pointer(); }
    reference	    operator =(void *p) { pointer(p); return *this; }

    template<class T>
    reference	    operator =(T *p)	
		    { pointer(reinterpret_cast<void*>(p)); return *this; }
    
    void	    pointer(void* p)	{ _p = mark()?((ptr)p|1):((ptr)p&~1); }
    void*	    pointer() const	{ return (void*)(_p & ~1); }

  private:
    ptr	    	    _p;
};

template <class T>
inline 
T* markable_cast(markable_pointer p)
{
    return reinterpret_cast<T*>(p.pointer());
}


} // namespace stl_ext

#endif // __stl_ext__markable_pointer__h__
