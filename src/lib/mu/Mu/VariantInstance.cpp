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

#include <Mu/VariantInstance.h>
#include <Mu/VariantType.h>
#include <Mu/VariantTagType.h>
#include <Mu/Thread.h>
#include <Mu/Context.h>
#include <Mu/MemberVariable.h>
#include <Mu/GarbageCollector.h>
#include <stl_ext/block_alloc_arena.h>

namespace Mu {
using namespace std;
using namespace stl_ext;

VariantInstance::VariantInstance() : Object() {}

VariantInstance::VariantInstance(const VariantTagType* type) : Object(type)
{
    type->representationType()->constructInstance(structure());
}

VariantInstance::VariantInstance(Thread& thread, const char* cname)
    : Object()
{
    //
    //  This is a performance critical section. It needs to be
    //  optimized with thread specific cache or something.
    //

    Context* context = thread.context();

    Name n = context->internName(cname);
    VariantTagType* t = context->findSymbolOfTypeByQualifiedName<VariantTagType>(n);
    assert(t);
    t->representationType()->constructInstance(structure());
}

VariantInstance* 
VariantInstance::allocate(const VariantTagType* c)
{
    size_t s = c->objectSize();
    unsigned char* obj = (unsigned char*)(c->isGCAtomic() ? MU_GC_ALLOC_ATOMIC(s) : MU_GC_ALLOC(s));
    return new (obj) VariantInstance(c);
}

VariantInstance* 
VariantInstance::allocate(Thread& thread, const char* c)
{
    Context* context = thread.context();
    Name n = context->internName(c);
    const Class* t = context->findSymbolOfTypeByQualifiedName<Class>(n);
    assert(t);
    size_t s = t->objectSize();
    unsigned char* obj = (unsigned char*)(t->isGCAtomic() ? MU_GC_ALLOC_ATOMIC(s) : MU_GC_ALLOC(s));
    return new (obj) VariantInstance(thread, c);
}


VariantInstance::~VariantInstance() {}

void
VariantInstance::deallocate(VariantInstance* p)
{
    MU_GC_FREE(p);
}

unsigned long
VariantInstance::hash() const
{
    const VariantTagType *t = tagType();
    size_t s = t->objectSize();

    unsigned long h=0,g;
    
    for (int i=0; i < s; i++)
    {
	h = (h << 4) + structure()[i];
	if ( g = h & 0xf0000000 ) h ^= g >> 24;
	h &= ~g;
    }
    
    return h ^ (unsigned long)t;
}

ValuePointer
VariantInstance::field(size_t i)
{
    assert(i==0);
    return structure();
}

const ValuePointer
VariantInstance::field(size_t i) const
{
    assert(i==0);
    return structure();
}

} // namespace Mu
