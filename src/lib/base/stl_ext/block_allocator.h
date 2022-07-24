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
#ifndef __stl_ext__block_alloc__h__
#define __stl_ext__block_alloc__h__
#include <stl_ext/block_alloc_arena.h>

#error "Dont use this yet! GCC seems to have trouble with it"

namespace stl_ext {

//
//  class block_allocator<>
//
//  This is a standards compliant allocator class. You can pass this
//  as a template argument to STL classes which take an allocator. In
//  doing so, you create an STL class which uses block_alloc_arena's
//  static arena object for its allocation. Note that the memory used
//  by block_alloc_arena::static_arena() is never freed.
//
//  Alternately, you can pass in your own ArenaSelector struct which
//  can choose some other arena.
//

struct arena_selector
{
    static block_alloc_arena& arena() 
    { 
	return block_alloc_arena::static_arena(); 
    }
};

template <class T, class ArenaSelector>
class block_allocator
{
public:
    typedef size_t 		size_type;
    typedef ptrdiff_t 		difference_type;
    typedef T* 			pointer;
    typedef const T* 		const_pointer;
    typedef T& 			reference;
    typedef const T& 		const_reference;
    typedef T 			value_type;

    template <class U> struct rebind 
    { 
        typedef block_allocator<U, ArenaSelector> other; 
    };

    block_allocator() throw() {}
    block_allocator(const block_allocator&) throw() {}
    template <class U> 
    block_allocator(const block_allocator<U, ArenaSelector>&) throw() {}
    ~block_allocator() throw() {}

    pointer		address(reference x) const	    { return &x; }
    const_pointer	address(const_reference x) const    { return &x; }
    pointer		allocate(size_type, const void* hint = 0);
    void		deallocate(pointer p, size_type n);
    void		construct(pointer p, const T& val) { new(p) T(val); }
    void		destroy(pointer p) { ((T*)p)->~T(); }

    size_type           max_size() const throw()
                        { return size_t(-1) / sizeof(T); }
};

template<>
class block_allocator<void> 
{
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;
    typedef void*       pointer;
    typedef const void* const_pointer;
    typedef void        value_type;

    template <class GC_Tp1> struct rebind 
    {
        typedef block_allocator<GC_Tp1> other;
    };
};

template<class T, class ArenaSelector>
inline typename block_allocator<T, ArenaSelector>::pointer
block_allocator<T, ArenaSelector>::allocate(size_type size, const void *)
{
    return reinterpret_cast<T*>
	(ArenaSelector::arena().allocate(size*sizeof(T)));
};

template<class T, class ArenaSelector>
inline void
block_allocator<T, ArenaSelector>::deallocate(typename block_allocator<T, ArenaSelector>::pointer p, size_type size)
{
    ArenaSelector::arena().deallocate(p,size*sizeof(T));
};


} // stl_ext

#endif // __stl_ext__block_alloc__h__
