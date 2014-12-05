#ifndef __MuLang__ExceptionType__h__
#define __MuLang__ExceptionType__h__
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
#include <Mu/Exception.h>
#include <Mu/Node.h>
#include <iosfwd>
#include <string>

namespace Mu { 

//
//  class ExceptionType
//
//  A non-mutable string type.
//

class ExceptionType : public Class
{
  public:
    ExceptionType(Context*, Class *super=0);
    ~ExceptionType();

    class Exception : public ClassInstance
    {
      public:
	Exception(const Class*);

	Mu::String& string() { return _string; }
	const Mu::String& string() const { return _string; }

        void setBackTrace(Mu::Exception& e) { _backtrace = e.backtrace(); }
        const Thread::BackTrace& backtrace() const { return _backtrace; }
        Thread::BackTrace& backtrace() { return _backtrace; }

        String backtraceAsString() const;

      private:
	Mu::String _string;
        Thread::BackTrace _backtrace;
    };

    //
    //	Return a new Object
    //

    virtual Object* newObject() const;
    virtual void deleteObject(Object*) const;

    //
    //	Output the symbol name
    //	Output the appropriate Value in human readable form
    //

    virtual void outputValueRecursive(std::ostream&,
                                      const ValuePointer,
                                      ValueOutputState&) const;

    //
    //	Load function is called when the symbol is added to the
    //	context.
    //

    virtual void load();

    virtual void freeze();

    //
    //	Nodes
    //

    static NODE_DECLARATION(construct,Pointer);
    static NODE_DECLARATION(stringCast,Pointer);
    static NODE_DECLARATION(dereference,Pointer);
    static NODE_DECLARATION(print,void);
    static NODE_DECLARATION(assign,Pointer);
    static NODE_DECLARATION(equals,bool);
    static NODE_DECLARATION(copy,Pointer);
    static NODE_DECLARATION(mu__try,void);
    static NODE_DECLARATION(mu__catch,bool);
    static NODE_DECLARATION(mu__catch_all,bool);
    static NODE_DECLARATION(mu__exception,Pointer);
    static NODE_DECLARATION(mu__throw,void);
    static NODE_DECLARATION(mu__throw_exception,void);
    static NODE_DECLARATION(mu__rethrow,void);
    static NODE_DECLARATION(backtrace,Pointer);
};

} // namespace Mu

#endif // __MuLang__ExceptionType__h__
