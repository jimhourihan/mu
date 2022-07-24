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
#include <assert.h>
#include <stl_ext/block_alloc_arena.h>
#include <stl_ext/pvector.h>
#include <stl_ext/stl_ext_algo.h>
#include <iostream>

namespace stl_ext {
using namespace std;

block_alloc_arena block_alloc_arena::_static_arena;

block_alloc_arena::block_alloc_arena(size_t gl, size_t lbs) 
    : _running_allocation(0), 
      _garbage_limit(gl),
      _large_block_size(lbs),
      _garbage_function(0),
      _disable(false)
{
    pthread_mutex_init(&_lock, 0);
}

block_alloc_arena::~block_alloc_arena()
{
    pthread_mutex_destroy(&_lock);
    delete_contents(_blocks);
}

inline size_t
adjust_size(size_t n)
{
    //
    //	Should user of the class be able to tune these?
    //

    if (n < 8) n = 8;
    else while (n & 0x7) n++;
    return n >> 3;
    //return n;
}

void
block_alloc_arena::set_garbage_function(garbage_function func)
{
    pthread_mutex_lock(&_lock);
    _garbage_function = func;
    pthread_mutex_unlock(&_lock);
}

void
block_alloc_arena::reset_running_allocation()
{
    pthread_mutex_lock(&_lock);
    _running_allocation = 0;
    pthread_mutex_unlock(&_lock);
}

void
block_alloc_arena::set_garbage_limit(size_t limit)
{
    pthread_mutex_lock(&_lock);
    _garbage_limit = limit;
    pthread_mutex_unlock(&_lock);
}

void
block_alloc_arena::set_large_block_size(size_t t)
{
    pthread_mutex_lock(&_lock);
    _large_block_size = t;
    pthread_mutex_unlock(&_lock);
}

void*
block_alloc_arena::allocate(size_t n)
{
    if (_disable)
    {
        return (void*)(new char[n]);
    }
    else
    {
        _running_allocation += n;
        if (_running_allocation >= _garbage_limit)
        {
            if (_garbage_function) (*_garbage_function)(this);
            _running_allocation = 0;
        }

        pthread_mutex_lock(&_lock);

        if (n >= _large_block_size)
        {
            void *data = (void*)(new byte[n]);
            pthread_mutex_unlock(&_lock);
            return data;
        }
        else
        {
            size_t on = n;
            n = adjust_size(n);
            while ( _blocks.size() <= n ) _blocks.push_back(0);

            if ( !_blocks[n] )
            {
                _blocks[n] = new allocator(n << 3);
            }

            pthread_mutex_unlock(&_lock);

            void* obj;

            try
            {
                obj = _blocks[n]->allocate();
            }
            catch (std::bad_alloc& e)
            {
                cerr << "ERROR: block_alloc_arena: failed to allocate " << on
                     << " bytes from arena size " << (n << 3)
                     << endl;

                throw;
            }
            catch (std::exception& e)
            {
                cerr << "ERROR: caught std::exception during allocation"
                     << endl;

                throw;
            }

            return obj;
        }
    }
}

void
block_alloc_arena::deallocate(void *p, size_t n)
{
    if (_disable)
    {
        delete [] ((char*)p);
    }
    else
    {
        if (p)
        {
            pthread_mutex_lock(&_lock);
            if (n <= _running_allocation) _running_allocation -= n;

            if (n >= _large_block_size)
            {
                delete [] (byte*)p;
                pthread_mutex_unlock(&_lock);
            }
            else
            {
                n = adjust_size(n);
                pthread_mutex_unlock(&_lock);
                if ( _blocks.size() > n && _blocks[n] ) _blocks[n]->deallocate(p);
            }
        }
    }
}

bool
block_alloc_arena::is_allocated(const void *p, size_t n) const
{
    //
    //	If any of the last three bits are non-zero the alignment would be
    //	wacky, so it can't possibly be pointing to a struct in here.
    //

    if ((size_t(p) & 0x7) != 0) return false;

    n = adjust_size(n);
    return _blocks.size() > n && _blocks[n]
	? _blocks[n]->is_allocated(p) : false;
}

bool
block_alloc_arena::is_allocated(const void *p) const
{
    for (int i=0; i<_blocks.size(); i++)
	if (_blocks[i] && _blocks[i]->is_allocated(p)) return true;
    return false;
}

bool
block_alloc_arena::is_live(const void *p, size_t n)
{
    n = adjust_size(n);
    return _blocks.size() > n && _blocks[n]
	? _blocks[n]->is_live(p) : false;
}

bool
block_alloc_arena::is_live(const void *p)
{
    for (int i=0; i<_blocks.size(); i++)
	if (_blocks[i] && _blocks[i]->is_live(p)) return true;
    return false;
}

void
block_alloc_arena::mark_free(bool b)
{
    pthread_mutex_lock(&_lock);
    for (int i=0; i<_blocks.size(); i++)
	if (_blocks[i]) _blocks[i]->mark_free(b);
    pthread_mutex_unlock(&_lock);
}

void
block_alloc_arena::iterator::init()
{
    if (_arena)
    {
	if (_arena->_blocks.size() && _arena->_blocks[_index])
	{
	    _i = _arena->_blocks[_index]->begin();
	}
	else
	{
	    _i = allocator::iterator();
	    next();
	}
    }
}

void
block_alloc_arena::iterator::next()
{
    if (!_arena) return;
    allocator::iterator end;

    _i++;

    if (_i == end)
    {
	_index++;
	for (;_index < _arena->_blocks.size() && !_arena->_blocks[_index]; 
	     _index++);
	if (_index >= _arena->_blocks.size()) { _index--; return; }
	_i = _arena->_blocks[_index]->begin();
    }
}


size_t
block_alloc_arena::capacity()
{
    size_t bytes = 0;

    for (int i=0; i<_blocks.size(); i++)
    {
	if (_blocks[i]) bytes += _blocks[i]->capacity();
    }

    return bytes;
}

} // namespace stl_ext
