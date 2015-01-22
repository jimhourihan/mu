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

#include "List.h"
#include <Mu/Thread.h>

namespace Mu {
using namespace std;

List::List(Process* p, ClassInstance* o) 
  : _process(p),
    _current(o),
    _head(o)
{
    if (o)
    {
        _type = static_cast<const ListType*>(_current->classType());
        _voff = _type->valueOffset();
        _noff = _type->nextOffset();
    }
    else
    {
        _type = 0;
        _voff = 0;
        _noff = 0;
    }
}

List::List(Process* p, const ListType* l) :
    _process(p),
    _type(l),
    _voff(l->valueOffset()),
    _noff(l->nextOffset())
{
    _head = 0;
    _current = _head;
}

void
List::appendDefaultValue()
{
    while (_current && next()) _current = next();
    ClassInstance* o = ClassInstance::allocate(_type);
    if (_current) next() = o;
    if (!_head) _head = o;
    _current = o;
}

void
List::append(Thread& thread, const Node* n)
{
    while (_current && next()) _current = next();
    ClassInstance* o = ClassInstance::allocate(_type);
    if (_current) next() = o;
    if (!_head) _head = o;
    _current = o;
    n->eval(thread, valuePointer());
}


ClassInstance*
List::splice(Thread& thread, const Node* n)
{
    ClassInstance* o = ClassInstance::allocate(_type);
    ClassInstance* c = _current;
    if (!_head) _head = o;
    _current = o;
    _head = o;
    n->eval(thread, valuePointer());
    return o;
}


} // namespace Mu
