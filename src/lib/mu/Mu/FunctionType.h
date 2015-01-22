#ifndef __Mu__FunctionType__h__
#define __Mu__FunctionType__h__
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
#include <Mu/Node.h>
#include <Mu/Class.h>
#include <Mu/Signature.h>

namespace Mu {

class FunctionType : public Class
{
  public:
    FunctionType(Context* context, const char* name);
    FunctionType(Context* context, const char* name, const Signature*);
    virtual ~FunctionType();

    const Signature*    signature() const { return _signature; }

    //
    //  Type API
    //

    virtual void        serialize(std::ostream&,
                                  Archive::Writer&,
                                  const ValuePointer) const;

    virtual void        deserialize(std::istream&, 
                                    Archive::Reader&,
                                    ValuePointer) const;
    
    virtual void        reconstitute(Archive::Reader&, Object*) const;

    virtual Object*	newObject() const;
    virtual void 	nodeEval(void*, const Node*,Thread &t) const;
    virtual void	deleteObject(Object*) const;

    virtual void	outputNode(std::ostream&,const Node*) const;
    virtual void        outputValueRecursive(std::ostream&,
                                             const ValuePointer,
                                             ValueOutputState&) const;

    virtual void        load();

    //
    //  Match. If a function type A is compatible with B, it means
    //  that a function object of type A can be held in a variable of
    //  type B.
    //
    //  This can be the case if one or more of the arguments of A are
    //  base classes of the arguments in B. And/Or if A's return type
    //  is a sub-class of B's return type.
    //
    //  NOTE: Read the above again! It can be very confusing.
    //

    MatchResult         match(const Type*, Bindings&) const;

  private:
    static MU_NODE_DECLARATION(dereference, Pointer);
    static MU_NODE_DECLARATION(disambiguate, Pointer);
    static MU_NODE_DECLARATION(ambiguate, Pointer);
    static MU_NODE_DECLARATION(assign, Pointer);
    static MU_NODE_DECLARATION(eq, bool);
    static MU_NODE_DECLARATION(print, void);

    static MU_NODE_DECLARATION(call, void);

  private:
    const Signature*    _signature;

};

} // namespace Mu

#endif // __Mu__FunctionType__h__
