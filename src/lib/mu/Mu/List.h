#ifndef __MuLang__List__h__
#define __MuLang__List__h__
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
#include <Mu/ListType.h>
#include <Mu/Exception.h>

namespace Mu {

//
//  class List
//
//  Unlike DynamicArray and FixedArray, the List class is a wrapper
//  around the underlying ClassInstance representation of a Mu list.
//  This class makes it easy to create and edit lists.
//

class List
{
public:
    //
    //  Make a new list
    //

    List(Process*, const ListType*);

    //
    //  Use an existing list
    //

    List(Process*, ClassInstance*);

    //
    //  New list from result of eval
    //

    List(const ListType*, Thread& thread, const Node*);

    //
    //  isNil means there is no longer a list
    //

    bool isNil() const { return _current ? false : true; }
    bool isNotNil() const { return _current ? true : false; }

    //
    //  Type of the List
    //

    const ListType* type() const { return _type; }

    //
    //  The head cons cell
    //

    ClassInstance* head() const { return _head; }

    //
    //  The current cons cell
    //

    ClassInstance* operator*() const { return _current; }

    //
    //  Value of the current cons cell
    //

    template <class T>
    const T value() const
    { 
        if (!_current) throw BadInternalListCallException();
        return *reinterpret_cast<const T*>(_current->structure() + _voff); 
    }

    template <class T>
    T& value()
    { 
        if (!_current) throw BadInternalListCallException();
        return *reinterpret_cast<T*>(_current->structure() + _voff); 
    }

    ValuePointer valuePointer() const
    { 
        if (!_current) throw BadInternalListCallException();
        return reinterpret_cast<ValuePointer>(_current->structure() + _voff); 
    }

    //
    //  Reference to next cons cell
    //

    ClassInstance*& next() const
    { 
        if (!_current) throw BadInternalListCallException();
        return *reinterpret_cast<ClassInstance**>(_current->structure() + _noff); 
    }

    //
    //  Increment current cons cell (to next cons cell)
    //

    void operator++() { if (_current) _current = next(); }
    void operator++(int) { if (_current) _current = next(); }

    //
    //  Append value to the end of the current list, (or the result of
    //  evaluating the given node). This will make the appended
    //  element the current cons cell.
    //

    template <class T>
    void append(const T& v);

    //
    //  Like above, but appends a default value
    //

    void appendDefaultValue();

    //
    //  Append result of evaluating node. The appended cons cell
    //  becomes the current cons cell.
    //

    void append(Thread& thread, const Node* n);

    //
    //  Splice creates a new head at the current cons cell and becomes
    //  the head and current cons cell of the list.
    //

    template <class T>
    ClassInstance* splice(const T& v);

    //
    //  Same as above, but value comes from node eval
    //

    ClassInstance* splice(Thread& thread, const Node* n);

private:
    Process*        _process;
    const ListType* _type;
    ClassInstance*  _head;
    ClassInstance*  _current;
    size_t          _voff;
    size_t          _noff;

private:
    List() {}
};
        

template <class T>
void
List::append(const T& v)
{
    while (_current && next()) _current = next();
    ClassInstance* o = ClassInstance::allocate(_type);
    if (_current) next() = o;
    if (!_head) _head = o;
    _current = o;
    value<T>() = v;
}

template <class T>
ClassInstance*
List::splice(const T& v)
{
    ClassInstance* o = ClassInstance::allocate(_type);
    ClassInstance* c = _current;
    _current = o;
    _head = o;
    value<T>() = v;
    next() = c;
    return o;
}


} // namespace Mu

#endif // __MuLang__List__h__
