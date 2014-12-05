#ifndef __MuLang__DynamicArrayType__h__
#define __MuLang__DynamicArrayType__h__
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

#include <vector>
#include <Mu/Type.h>
#include <Mu/Class.h>
#include <Mu/ClassInstance.h>
#include <Mu/MachineRep.h>

namespace Mu {

//
//  class DynamicArrayType
//
//  An array class parameterized by type. The array object handles
//  memory using the std::vector<> template. The memory is guaranteed
//  to be contiguous (this is in an upcoming ANSI C++
//  specification). The object type is DynamicArray
//

class DynamicArrayType : public Class
{
public:
    typedef STLVector<size_t>::Type SizeVector;

    DynamicArrayType(Context* c,
                     const char *name, 
                     Class *superClass, 
                     const Type *elementType,
                     int dimensions);

    ~DynamicArrayType();

    virtual MatchResult match(const Type*, Bindings&) const;

    const Type* elementType() const { return _elementType; }
    const MachineRep* elementRep() const { return elementType()->machineRep(); }

    const size_t dimensions() const { return _dimensions; }

    //
    //	Symbol API
    //

    virtual Object* newObject() const;
    virtual size_t objectSize() const;
    virtual void deleteObject(Object*) const;
    virtual Value nodeEval(const Node*, Thread&) const;
    virtual void outputValueRecursive(std::ostream&,
                                      const ValuePointer,
                                      ValueOutputState&) const;
    virtual void load();
    virtual void constructInstance(Pointer) const;
    virtual void copyInstance(Pointer, Pointer) const;
    virtual void freeze();

    //
    //	Type API
    //

    virtual const Type*         fieldType(size_t) const;
    virtual ValuePointer        fieldPointer(Object*, size_t) const;
    virtual const ValuePointer  fieldPointer(const Object*, size_t) const;

    //
    //  Archiving
    //

    virtual void serialize(std::ostream&, Archive::Writer&, const ValuePointer) const;
    virtual void deserialize(std::istream&, Archive::Reader&, ValuePointer) const;

    //
    //	Dynamic array functions
    //

    static NODE_DECLARATION(dyn_construct,Pointer);
    static NODE_DECLARATION(dyn_construct_aggregate,Pointer);
    static NODE_DECLARATION(dyn_copyconstruct,Pointer);
    static NODE_DECLARATION(dyn_print,void);
    static NODE_DECLARATION(dyn_size,int);
    static NODE_DECLARATION(dyn_empty,bool);
    static NODE_DECLARATION(dyn_rest,Pointer);
    static NODE_DECLARATION(dyn_index1,Pointer);
    static NODE_DECLARATION(dyn_indexN,Pointer);
    static NODE_DECLARATION(dyn_equals,bool);
    static NODE_DECLARATION(front,Pointer);
    static NODE_DECLARATION(back,Pointer);
    static NODE_DECLARATION(clear,void);
    static NODE_DECLARATION(dyn_resize1,void);
    static NODE_DECLARATION(dyn_resizeN,void);
    static NODE_DECLARATION(push_back_float,float);
    static NODE_DECLARATION(push_back_double,double);
    static NODE_DECLARATION(push_back_int,int);
    static NODE_DECLARATION(push_back_int64,int64);
    static NODE_DECLARATION(push_back_bool,bool);
    static NODE_DECLARATION(push_back_Vector4f,Vector4f);
    static NODE_DECLARATION(push_back_Vector3f,Vector3f);
    static NODE_DECLARATION(push_back_Vector2f,Vector2f);
    static NODE_DECLARATION(push_back_Pointer,Pointer);
    static NODE_DECLARATION(push_back_char,char);
    static NODE_DECLARATION(push_back_short,short);
    static NODE_DECLARATION(pop_back_float,float);
    static NODE_DECLARATION(pop_back_double,double);
    static NODE_DECLARATION(pop_back_int,int);
    static NODE_DECLARATION(pop_back_int64,int64);
    static NODE_DECLARATION(pop_back_bool,bool);
    static NODE_DECLARATION(pop_back_Vector4f,Vector4f);
    static NODE_DECLARATION(pop_back_Vector3f,Vector3f);
    static NODE_DECLARATION(pop_back_Vector2f,Vector2f);
    static NODE_DECLARATION(pop_back_Pointer,Pointer);
    static NODE_DECLARATION(pop_back_char,char);
    static NODE_DECLARATION(pop_back_short,short);
    static NODE_DECLARATION(erase_float,void);
    static NODE_DECLARATION(erase_double,void);
    static NODE_DECLARATION(erase_int,void);
    static NODE_DECLARATION(erase_int64,void);
    static NODE_DECLARATION(erase_bool,void);
    static NODE_DECLARATION(erase_Vector4f,void);
    static NODE_DECLARATION(erase_Vector3f,void);
    static NODE_DECLARATION(erase_Vector2f,void);
    static NODE_DECLARATION(erase_Pointer,void);
    static NODE_DECLARATION(erase_char,void);
    static NODE_DECLARATION(erase_short,void);

private:
    const Type* _elementType;
    size_t _dimensions;
};




} // namespace Mu

#endif // __MuLang__DynamicArrayType__h__

