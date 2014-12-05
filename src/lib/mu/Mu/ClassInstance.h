#ifndef __Mu__ClassInstance__h__
#define __Mu__ClassInstance__h__
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
#include <Mu/config.h>
#include <Mu/Object.h>
#include <Mu/Value.h>
#include <Mu/Class.h>

namespace Mu {
class Thread;

class ClassInstance : public Object
{
  public:
    //
    //  A ClassInstance requires use of placement new to be created,
    //  when the type is something dynamic (like a user defined class
    //  or a tuple type, etc).
    //
    //  Use the allocate function
    //

    static ClassInstance* allocate(const Class* c);
    static ClassInstance* allocate(Thread& thread, const char* c);
    static void deallocate(ClassInstance* p);

    Structure	    structure() { return (unsigned char*)this + sizeof(this); }
    const Structure structure() const { return (unsigned char*)this + sizeof(this); }
    const Class*    classType() const 
		    { return static_cast<const Class*>(type()); }

    template <class T>
    T* data() { return reinterpret_cast<T*>(structure()); }

    template <class T>
    const T* data() const { return reinterpret_cast<const T*>(structure()); }

    //
    // This function uses the contents of the Structure plus the type
    // to produce the hash code. This may not always be what you want,
    // but it is a good default.
    //

    unsigned long hash() const;

    //
    //  Field access
    //

    const Type* fieldType(size_t i) const { return type()->fieldType(i); }

    ValuePointer field(size_t);
    const ValuePointer field(size_t) const;

  protected:
    ClassInstance(const Class*);
    ClassInstance(Thread&, const char*);
    ClassInstance();
    ~ClassInstance();

  private:
    //Structure	 _structure;
    friend class Class;
    friend class VariantInstance;
};

} // namespace Mu

#endif // __Mu__ClassInstance__h__
