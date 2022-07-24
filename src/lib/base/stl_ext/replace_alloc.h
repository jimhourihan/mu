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
#ifndef __stl_ext__replace_alloc__h__
#define __stl_ext__replace_alloc__h__

#ifdef PLATFORM_LINUX
#include <malloc.h>
#endif

#ifdef PLATFORM_WINDOWS
#define TWK_USE_NEDMALLOC
#endif

#ifdef PLATFORM_DARWIN
#define TWK_USE_SYSTEM_ALLOC
#endif

#ifdef PLATFORM_LINUX
//#define TWK_USE_SYSTEM_ALLOC
#define TWK_USE_NEDMALLOC
#endif

#ifdef TWK_USE_NEDMALLOC
#include <nedmalloc.h>
#define TWK_ALLOCATE(T) ((T*)nedmalloc(sizeof(T)))
#define TWK_ALLOCATE_ARRAY(T,n) ((T*)nedmalloc(n * sizeof(T)))
#define TWK_ALLOCATE_PAGE_ALIGNED(T) ((T*)nedmemalign(4096, sizeof(T)))
#define TWK_ALLOCATE_ARRAY(T,n) ((T*)nedmalloc(n * sizeof(T)))
#define TWK_ALLOCATE_ARRAY_PAGE_ALIGNED(T,n) ((T*)nedmemalign(4096, n * sizeof(T)))
#define TWK_DEALLOCATE(p) { if (p) nedfree((void*)p); }
#define TWK_DEALLOCATE_ARRAY(p) { if (p) nedfree((void*)p); }
#endif


#ifdef TWK_USE_SYSTEM_ALLOC
#define TWK_ALLOCATE(T) ((T*)malloc(sizeof(T)))
#define TWK_ALLOCATE_ARRAY(T,n) ((T*)malloc(n * sizeof(T)))
#define TWK_DEALLOCATE(p) { if (p) free((void*)p); }
#define TWK_DEALLOCATE_ARRAY(p) { if (p) free((void*)p); }
    #ifdef PLATFORM_LINUX
        #define TWK_ALLOCATE_PAGE_ALIGNED(T) ((T*)memalign(4096, sizeof(T)))
        #define TWK_ALLOCATE_ARRAY_PAGE_ALIGNED(T,n) ((T*)memalign(4096, sizeof(T)*n))
    #endif
    #ifdef PLATFORM_DARWIN
        #define TWK_ALLOCATE_PAGE_ALIGNED(T) ((T*)valloc(sizeof(T)))
        #define TWK_ALLOCATE_ARRAY_PAGE_ALIGNED(T,n) ((T*)valloc(sizeof(T)*n))
    #endif
#endif

#define TWK_CLASS_NEW_DELETE(T) \
void* T::operator new (size_t s) { return TWK_ALLOCATE_ARRAY(unsigned char,s); } \
void T::operator delete (void* p, size_t s) { TWK_DEALLOCATE_ARRAY(p); }

#define TWK_CLASS_NEW_DELETE_PAGE_ALIGNED(T) \
void* T::operator new (size_t s) { return TWK_ALLOCATE_ARRAY_PAGE_ALIGNED(unsigned char,s); } \
void T::operator delete (void* p, size_t s) { TWK_DEALLOCATE_ARRAY(p); }

namespace stl_ext {

template <typename T>
class replacement_allocator 
{
public:
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;
    typedef T*        pointer;
    typedef const T*  const_pointer;
    typedef T&        reference;
    typedef const T&  const_reference;
    typedef T         value_type;

    template <class T1> struct rebind {
        typedef replacement_allocator<T1> other;
    };

    replacement_allocator() throw() {}
    replacement_allocator(const replacement_allocator&) throw() {}
    template <class T1> replacement_allocator(const replacement_allocator<T1>&) throw() {}
    ~replacement_allocator() throw() {}

    pointer address(reference x) const { return &x; }
#ifndef WIN32
    const_pointer address(const_reference x) const { return &x; }
#endif

    T* allocate(size_type n, const void* = 0) 
    {
        if (n == 0) return 0;
        return TWK_ALLOCATE_ARRAY(T, n);
    }

    // __p is not permitted to be a null pointer.
    void deallocate(pointer p, size_type n) { TWK_DEALLOCATE_ARRAY(p); }

    size_type max_size() const throw()
        { return size_t(-1) / sizeof(T); }

    void construct(pointer p, const T& val) 
        { new(p) T(val); }

    void destroy(pointer p) { p->~T(); }
};

template <class T1, class T2>
inline bool operator==(const replacement_allocator<T1>&, const replacement_allocator<T2>&)
{
  return true;
}

template <class T1, class T2>
inline bool operator!=(const replacement_allocator<T1>&, const replacement_allocator<T2>&)
{
  return false;
}

#if 0
template<>
class replacement_allocator<void> 
{
    typedef size_t      size_type;
    typedef ptrdiff_t   difference_type;
    typedef void*       pointer;
    typedef const void* const_pointer;
    typedef void        value_type;

    template <class T1> struct rebind {
        typedef replacement_allocator<T1> other;
    };
};
#endif

}

#endif
