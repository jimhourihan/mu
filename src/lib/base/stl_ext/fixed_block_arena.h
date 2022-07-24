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
#ifndef __stl_ext__fixed_block_arena_h__
#define __stl_ext__fixed_block_arena_h__
#include <vector>
#include <stl_ext/markable_pointer.h>
#include <stl_ext/stl_ext_config.h>
#include <stl_ext/fixed_block_allocator.h>
#include <pthread.h>
#include <assert.h>

namespace stl_ext {

//
//  class fixed_block_arena
//     
//  A collection of fixed_block_allocators. As each successive
//  fixed_block_allocator runs out of available memory, a new one is
//  created by the arena and the process starts all over again.
//

class fixed_block_arena
{
  public:
    typedef fixed_block_allocator       allocator;
    typedef allocator::iterator         allocator_iterator;
    typedef allocator*                  allocator_pointer;
    typedef allocator::pointer          pointer;
    typedef allocator::const_pointer    const_pointer;
    typedef allocator::value_type       value_type;
    typedef std::vector<allocator*>     allocator_vector;
    typedef markable_pointer		object;
    typedef object*			object_pointer;
    typedef object&			object_reference;

    fixed_block_arena(size_t value_size);
    ~fixed_block_arena();

    pointer				allocate();
    void				deallocate(pointer);

    bool				is_allocated(const_pointer) const;
    bool				is_live(const_pointer);

    size_t				capacity();

    class iterator
    {
      public:
	iterator() : _index(0), _it(), _arena(0) {}
	iterator(fixed_block_arena* a) : _arena(a), _index(0) {init();}

	object_reference	operator*() { return *_it; }
	object_pointer		operator->() { return &(operator*()); }
	void			operator++() { next(); }
	void			operator++(int) { next(); }
	bool			operator==(const iterator &i) const
				{ return _it == i._it; }
	bool			operator!=(const iterator &i) const
				{ return _it != i._it; }

      private:
	void			next();
	void			init();

      private:
        fixed_block_arena*      _arena;
        size_t                  _index;
        allocator_iterator      _it;
    };

    void				mark_free(bool);
    iterator				begin() { return iterator(this); }
    iterator				end()	{ return iterator(); }

  private:
    fixed_block_arena() {}
    fixed_block_arena(const fixed_block_arena&) {}
    void operator=(const fixed_block_arena&) {}

  private:
    allocator_vector			_allocators;
    pthread_mutex_t			_lock;
    friend class iterator;
};

} // namespace stl_ext

#endif // __stl_ext__fixed_block_arena_h__
