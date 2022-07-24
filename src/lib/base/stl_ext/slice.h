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
#ifndef __stl_ext__slice_h__
#define __stl_ext__slice_h__

namespace stl_ext {

//
//  slice provides a way to index into an existing vector or
//  deque. The access methods do not yet allow iterators.
//
//  push_back() will add elements to the master container until the element
//  would appear in the slice. 
//
//  There are two versions of slice: the normal template class version
//  with constructors and a slice_struct version which does not have
//  constructors. If you need to use the slice in a union (like the
//  yacc union for instance) you should use the struct version. Note
//  that if you make the slice start at 0 with a stride of 1 you
//  basically have a proxy to the underlying container. 
//

template<class Container> struct stride_struct;

template<class Container>
class slice
{
  public:
    typedef typename Container::value_type  value_type;
    typedef value_type*	    	    	    pointer;
    typedef const pointer   	    	    const_pointer;
    typedef value_type&	    	    	    reference;
    typedef reference                       const_reference;
    typedef size_t	    	    	    size_type;
    typedef int		    	    	    difference_type;
    typedef slice<Container>	    	    this_type;

    typedef typename Container::iterator	    	iterator;
    typedef typename Container::const_iterator 		const_iterator;
    typedef typename Container::reverse_iterator 	reverse_iterator;
    typedef typename Container::const_reverse_iterator 	const_reverse_iterator;


    slice(Container &c, iterator i, int stride=1) 
	: _c(&c), _start(i-c.begin()), _stride(stride) {}
    slice(Container &c, size_t i, int stride=1)   
	: _c(&c), _start(i), _stride(stride) {}
    slice(Container &c, int stride=1)		
	: _c(&c), _start(0), _stride(stride) {}
    slice()
	: _c(0), _start(0), _stride(0) {}

    size_t	    start() const { return _start; }
    size_t	    stride() const { return _stride; }
    Container&	    container() { return *_c; }
    const Container&  container() const { return *_c; }

    const_reference operator [] (size_type i) const 
		    { return const_reference(container()[i*_stride+_start]); }
    reference	    operator [] (size_type i) 
		    { return reference(container()[i*_stride+_start]); }

    iterator        begin() { return _c->begin(); }
    const_iterator  begin() const { return ((const Container*)_c)->begin(); }

    iterator        end() { return _c->end(); }
    const_iterator  end() const { return ((const Container*)_c)->end(); }

    void	    push_back(const value_type &t)
		    { 
			do { container().push_back(t); }
			while((container().size()-_start)%_stride); 
		    }

    reference	    front() { return (*_c)[start()]; }
    const_reference front() const { return (*_c)[start()]; }

    bool	    empty() const { return _c ? container().empty() : true; }
    size_t	    size() const 
		    { return empty()?0:(container().size()-_start)/_stride; }

    const_reference back() const { return (*this)[size()-1]; }
    reference	    back() { return (*this)[size()-1]; }

  private:
    Container*	_c;
    size_t	_start;
    int		_stride;
};

//
//  This is a no-constructor version that you can use in a union.
//

template<class Container>
struct slice_struct
{
    typedef typename Container::value_type  value_type;
    typedef value_type*	    	    	    pointer;
    typedef const pointer   	    	    const_pointer;
    typedef value_type&	    	    	    reference;
    typedef reference                       const_reference;
    typedef size_t	    	    	    size_type;
    typedef int		    	    	    difference_type;
    typedef slice_struct<Container>    	    this_type;

    typedef typename Container::iterator	    	iterator;
    typedef typename Container::const_iterator 		const_iterator;
    typedef typename Container::reverse_iterator 	reverse_iterator;
    typedef typename Container::const_reverse_iterator 	const_reverse_iterator;

    Container*	_c;
    size_t	_start;
    int		_stride;

    size_t	    start() const { return _start; }
    size_t	    stride() const { return _stride; }
    Container&	    container() { return *_c; }
    const Container& container() const { return *_c; }

    const_reference operator [] (size_type i) const 
		    { return const_reference(container()[i*_stride+_start]); }
    reference	    operator [] (size_type i) 
		    { return reference(container()[i*_stride+_start]); }

    void	    push_back(const value_type &t)
		    { 
			do { container().push_back(t); }
			while((container().size()-_start)%_stride); 
		    }

    iterator        begin() { return _c->begin(); }
    const_iterator  begin() const { return ((const Container*)_c)->begin(); }

    iterator        end() { return _c->end(); }
    const_iterator  end() const { return ((const Container*)_c)->end(); }


    reference	    front() { return (*_c)[start()]; }
    const_reference front() const { return (*_c)[start()]; }

    bool	    empty() const { return _c ? container().empty() : true; }
    size_t	    size() const 
		    { return empty()?0:(container().size()-_start)/_stride; }

    const_reference back() const { return (*this)[size()-1]; }
    reference	    back() { return (*this)[size()-1]; }
};

} // namespace stl_ext

#endif // __stl_ext__slice_h__
