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
#ifndef __stl_ext__block_alloc_arena_h__
#define __stl_ext__block_alloc_arena_h__
#include <stl_ext/fixed_block_arena.h>
#include <pthread.h>
#include <vector>
#include <stl_ext/stl_ext_config.h>

namespace stl_ext {

//
//  class block_alloc_arena
//
//  block_alloc_arena can be used to manage block allocated memory for
//  a variety of object sizes. The class keeps an internal pvector of
//  fixed_block_allocator instances for various sizes. block_alloc_arena
//  will always allocate from one of these fixed_block_allocators. This
//  ensures that pointers can be tracked for garbage collection. Given
//  an arbitrary pointer, block_alloc_arena can tell you if it was
//  allocated by it and whether or not the pointer is live.
//
//  Note: its very dangerous to destroy one of these if you are using
//  it for memory management. You should have destroyed all of the
//  objects that where previously allocated using the
//  block_alloc_arena first.
//

class STL_EXT_EXPORT block_alloc_arena
{
  public:
    typedef fixed_block_arena           allocator;
    typedef allocator::object_reference object_reference;
    typedef allocator::object_pointer   object_pointer;
    typedef unsigned char		byte;
    typedef void (*garbage_function)(block_alloc_arena*);

    block_alloc_arena(size_t garbage_limit=1024*16,
		      size_t large_block_size=1 << 13);
    ~block_alloc_arena();

    void* allocate(size_t);
    void  deallocate(void*,size_t);

    void disable() { _disable = true; }
    void enable() { _disable = false; }

    bool  is_allocated(const void*) const;
    bool  is_allocated(const void*,size_t) const;
    bool  is_live(const void*);
    bool  is_live(const void*,size_t);

    //
    //	Marks all freed objects -- assumes that all objects start with
    //	a markable_pointer.
    //

    void  mark_free(bool);

    //
    //	Garbage collection function is called if this number is
    //	exceeded.
    //

    void  set_garbage_function(garbage_function);
    void  set_garbage_limit(size_t);
    size_t garbage_limit() { return _garbage_limit; }
    void reset_running_allocation();

    //
    //	Threshold where regular new/delete is used
    //

    void   set_large_block_size(size_t t);
    size_t get_large_block_size() { return _large_block_size; }

    //
    //	Total amount of memory in caches
    //

    size_t capacity();

    class iterator
    {
      public:
	iterator() : _index(-1), _i(), _arena(0) { init(); }
	iterator(block_alloc_arena* a) : _index(0), _arena(a) { init(); }

	object_reference    operator*()  { return _i.operator*(); }
	object_pointer      operator->() { return _i.operator->(); }
	void		    operator++() { next(); }
	void		    operator++(int) { next(); }
	bool		    operator==(const iterator &i) const
			    { return _i == i._i; }
	bool		    operator!=(const iterator &i) const
			    { return _i != i._i; }
      private:
	void		    init();
	void		    next();

      private:
	int			    _index;
	allocator::iterator	    _i;
	block_alloc_arena*	    _arena;
    };

    iterator begin() { return iterator(this); }
    iterator end() { return iterator(); }

    static block_alloc_arena&	    static_arena()  { return _static_arena; }

  private:
    std::vector<allocator*>	    _blocks;
    pthread_mutex_t		    _lock;
    garbage_function		    _garbage_function;
    size_t			    _running_allocation;
    size_t			    _garbage_limit;
    size_t			    _large_block_size;
    bool                            _disable;
    static block_alloc_arena	    _static_arena;
    friend class iterator;
};

#define BLOCK_ALLOC_NEW_AND_DELETE					\
static void* operator new (size_t s)					\
{									\
    return stl_ext::block_alloc_arena::static_arena().allocate(s);	\
};									\
									\
static void operator delete (void* p, size_t s)				\
{									\
    stl_ext::block_alloc_arena::static_arena().deallocate(p,s);	    	\
}

} // namespace stl_ext

#endif // __stl_ext__block_alloc_arena_h__
