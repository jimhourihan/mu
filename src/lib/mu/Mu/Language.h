#ifndef __Mu__Language__h__
#define __Mu__Language__h__
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
#include <vector>

namespace Mu {

class Symbol;
class Type;
class Function;
class Thread;
class Class;

//
//  class Language
//
//  This class describes characteristics of a language implemented on
//  top of Mu.
//

class Language
{
  public:
    MU_GC_NEW_DELETE

    Language(const String& name,
	     const String& nameSpaceSeparator);
    virtual ~Language();

    //
    //	Types
    //

    typedef const String& StringRef;
    typedef STLVector<const Function*>::Type FunctionVector;
    typedef STLVector<const Type*>::Type     TypeVector;

    //
    //	Public API
    //

    const String&	    name() const { return _name; }
    const String&	    nameSpaceSeparator() const { return _nsSeparator; }

    void                    verbose(bool b) { _verbose = b; }


  private:
    String		    _name;
    String		    _nsSeparator;
    bool                    _verbose;
};


} // namespace Mu

#endif // __Mu__Language__h__
