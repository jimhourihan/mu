#ifndef __MuLang__NilType__h__
#define __MuLang__NilType__h__
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
#include <Mu/Class.h>
#include <Mu/Node.h>
#include <iosfwd>

namespace Mu {

//
//  class NilType
//
//  This type is of "nebulous" ancestry. This makes it possible to
//  cast NilType objects to any other class. So, nil inherts from all
//  types.
//
//  Has a single value => Pointer(0).
//

class NilType : public Class
{
  public:
    NilType(Context* context);
    ~NilType();

    //
    //	Type API
    //

    virtual Object* newObject() const;
    virtual Value nodeEval(const Node*, Thread&) const;
    virtual void nodeEval(void*, const Node*, Thread&) const;

    //
    //	Output the symbol name
    //	Output the appropriate Value in human readable form
    //

    virtual void outputValue(std::ostream&, const Value&, bool full=false) const;
    virtual void outputValueRecursive(std::ostream&, const ValuePointer, ValueOutputState&) const;

    //
    //	Load function is called when the symbol is added to the
    //	context.
    //

    virtual void load();

protected:
    //
    //  This is part of the Class API relevant to NilType
    //

    virtual bool nebulousIsA(const Class*) const;
};

} // namespace Mu

#endif // __MuLang__NilType__h__
