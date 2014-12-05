#ifndef __Mu__PyModule__
#define __Mu__PyModule__
//
//  Copyright (c) 2011, Jim Hourihan
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
//     * Neither the name of MuPy nor the names of its
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
#include <Mu/Module.h>
#include <Mu/Node.h>
#include <Mu/Value.h>

struct _object;
typedef struct _object PyObject;

class PyLockObject
{
  public:
    //
    //  Initialize locking and release GIL.
    //  
    static void initialize();

    //
    //  Find PyThreadState of current thread.  If this thread does
    //  not have the GIL, acquire it and swap in this state.
    //  
    PyLockObject();

    //
    //  If we acquired the GIL in the constructor, release it here.
    //  If we already had the GIL when the constructor ran, we leave
    //  that state unchanged.
    //
    ~PyLockObject();

  private:
    //
    //  True IFF we acquired the GIL in the constructor and must
    //  release it in the destructor.
    //  
    bool _mustReleaseGIL;
};

namespace Mu {

class MuLangContext;
class Type;
class ClassInstance;


class PyModule : public Module
{
  public:
    PyModule(Context* c, const char *name);
    virtual ~PyModule();

    virtual void load();

    typedef void* (*MuToPyObjectConverter)(const Type*, Mu::ClassInstance*);
    typedef ClassInstance* (*PyObjectToMuConverter)(const Type*, void*);
    typedef void* (*MuOpaqueToPyObjectConverter)(const Type*, void*);
    typedef Pointer (*PyObjectToMuOpaqueConverter)(const Type*, void*);

    //
    //  NOTE: any of these can be 0 if no function is needed
    //

    static void addConverterFunctions(MuToPyObjectConverter, 
                                      PyObjectToMuConverter,
                                      MuOpaqueToPyObjectConverter,
                                      PyObjectToMuOpaqueConverter);

    static Value     py2mu(MuLangContext*, Process*, const Type*, PyObject*);
    static PyObject* mu2py(MuLangContext*, Process*, const Type*, const Value&);

    static NODE_DECLARATION(nPy_DECREF, void);
    static NODE_DECLARATION(nPy_INCREF, void);
    static NODE_DECLARATION(nPyErr_Print, void);
    static NODE_DECLARATION(nPyObject_GetAttr, Pointer);
    static NODE_DECLARATION(nPyObject_CallObject, Pointer);
    static NODE_DECLARATION(nPyObject_CallObject2, Pointer);
    static NODE_DECLARATION(nPyTuple_New, Pointer);
    static NODE_DECLARATION(nPyTuple_Size, int);
    static NODE_DECLARATION(nPyTuple_SetItem, int);
    static NODE_DECLARATION(nPyTuple_GetItem, Pointer);
    static NODE_DECLARATION(nPyString_Check, bool);
    static NODE_DECLARATION(nPyFunction_Check, bool);
    static NODE_DECLARATION(nPyImport_Import, Pointer);
    static NODE_DECLARATION(nPy_TYPE, Pointer);
    static NODE_DECLARATION(nPyModule_GetName, Pointer);
    static NODE_DECLARATION(nPyModule_GetFilename, Pointer);
    static NODE_DECLARATION(is_nil, bool);
    static NODE_DECLARATION(type_name, Pointer);

    static NODE_DECLARATION(classInstanceToPyObject, Pointer);
    static NODE_DECLARATION(PyObjectToString, Pointer);
    static NODE_DECLARATION(PyObjectToBool, bool);
    static NODE_DECLARATION(PyObjectToInt, int);
    static NODE_DECLARATION(PyObjectToFloat, float);
};

} // Mu

#endif
