#ifndef __MuIO__ProcessType__h__
#define __MuIO__ProcessType__h__
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
#include <Mu/ClassInstance.h>
#include <Mu/Node.h>
#include <Mu/Thread.h>
#include <MuIO/OStreamType.h>
#include <MuIO/IStreamType.h>
#include <Mu/Vector.h>
#include <iosfwd>
#include <string>
#include "exec-stream.h"

namespace Mu {

class ProcessType : public Class
{
public:
    ProcessType(Context* c, const char* name, Class* super=0);
    virtual ~ProcessType();

    class PipeStream : public ClassInstance
    {
      public:
	PipeStream(const Class*);
        ~PipeStream();

        exec_stream_t* exec_stream;
        OStreamType::OStream* in;
        IStreamType::IStream* out;
        IStreamType::IStream* err;
    };

    //
    //	Return a new Object
    //

    virtual Object* newObject() const;
    virtual void deleteObject(Object*) const;

    //
    // Output the appropriate Value in human readable form (note: you
    // can call the static function if you already have a std::string.
    //

    virtual void outputValue(std::ostream&, const Value&, bool full=false) const;
    virtual void outputValueRecursive(std::ostream&,
                                      const ValuePointer,
                                      ValueOutputState&) const;

    //
    //	Load function is called when the symbol is added to the
    //	context.
    //

    virtual void load();

    static NODE_DECLARATION(construct, Pointer);
    static NODE_DECLARATION(toBool, bool);
    static NODE_DECLARATION(inStream, Pointer);
    static NODE_DECLARATION(outStream, Pointer);
    static NODE_DECLARATION(errStream, Pointer);
    static NODE_DECLARATION(close, bool);
    static NODE_DECLARATION(close_in, bool);
    static NODE_DECLARATION(kill, void);
    static NODE_DECLARATION(exit_code, int);

};

} // namespace Mu

#endif // __MuIO__ProcessType__h__
