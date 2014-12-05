#ifndef __MuLang__RegexType__h__
#define __MuLang__RegexType__h__
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
#include <iosfwd>
#ifdef MU_USE_PCRE
    #include <pcre.h>
    #include <pcreposix.h>
#else
    #include <regex.h>
#endif
#include <string>
#include <sys/types.h>

namespace Mu {

//
//  class RegexType
//
//  A non-mutable string type.
//

class RegexType : public Class
{
  public:
    RegexType(Context* c, Class *super=0);
    ~RegexType();

    class Regex : public ClassInstance
    {
      public:
	Regex(const Class*);
	Regex(const Class*, Thread&, const char* s=0, int flags=0);
        ~Regex();

        Mu::String& string() { return _std_string; }
	const Mu::String& string() const { return _std_string; }

        int flags() const { return _flags; }
        int maxMatches() const { return _regex.re_nsub; }

        void throwError(Thread&m, int);
        void compile(Thread&, int flags);
        bool matches(Thread&, const Mu::String&, int flags);
        bool smatch(Thread&, const Mu::String&, int flags,
                    regmatch_t* matches, size_t num);
        
      private:
        Mu::String              _std_string;
        regex_t                 _regex;
        int                     _flags;
	friend class RegexType;
    };

    //
    //	Return a new Object
    //

    virtual Object* newObject() const;
    virtual void deleteObject(Object*) const;
    virtual void freeze();

    //
    // Output the appropriate Value in human readable form (note: you
    // can call the static function if you already have a std::string.
    //

    virtual void outputValue(std::ostream&, const Value&, bool full=false) const;
    virtual void outputValueRecursive(std::ostream&, const ValuePointer, ValueOutputState&) const;
    static void outputQuotedRegex(std::ostream&, const std::string&);

    //
    //	Load function is called when the symbol is added to the
    //	context.
    //

    virtual void load();

    //
    //	Constant
    //

    static NODE_DECLARATION(from_string, Pointer);
    static NODE_DECLARATION(construct, Pointer);
    static NODE_DECLARATION(dereference, Pointer);
    static NODE_DECLARATION(print, void);
    static NODE_DECLARATION(match, bool);
    static NODE_DECLARATION(smatch, Pointer);
    static NODE_DECLARATION(replace, Pointer);
};

} // namespace Mu

#endif // __MuLang__RegexType__h__
