#ifndef __MuLang__OStreamType__h__
#define __MuLang__OStreamType__h__
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
#include <Mu/PrimitiveObject.h>
#include <Mu/PrimitiveType.h>
#include <Mu/Thread.h>
#include <Mu/Vector.h>
#include <MuIO/StreamType.h>
#include <iosfwd>
#include <iostream>
#include <string>

namespace Mu {

//
//  class OStreamType
//
//  
//

class OStreamType : public StreamType
{
  public:
    OStreamType(Context* c, const char* name, Class *super);
    ~OStreamType();

    class OStream : public StreamType::Stream
    {
      public:
	OStream(const Class*);
        ~OStream();

        std::ostream*   _ostream;

      private:
	friend class OStreamType;
    };

    //
    //	Return a new Object
    //

    virtual Object* newObject() const;
    virtual void deleteObject(Object*) const;


    //
    //	Load function is called when the symbol is added to the
    //	context.
    //

    virtual void load();

    //
    //  Functions
    //

    static NODE_DECLARATION(putc, Pointer);
    static NODE_DECLARATION(write, Pointer);
    static NODE_DECLARATION(writeBytes, Pointer);

    static NODE_DECLARATION(tell, int);
    static NODE_DECLARATION(seek, Pointer);
};

} // namespace Mu

#endif // __MuLang__OStreamType__h__
