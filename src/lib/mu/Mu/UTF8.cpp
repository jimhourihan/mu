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

#include <Mu/utf8_v2/checked.h>
#include <Mu/utf8_v2/unchecked.h>
#include <Mu/UTF8.h>

namespace Mu {
using namespace std;
using namespace utf8;

size_t
UTF8len(const char* s)
{
    size_t size = 0;
    for (; *s; unchecked::next(s)) size++;
    return size;
}

UTF32Char
UTF8convert(const char* s, int& nbytes)
{
    const size_t l = internal::sequence_length(s);
    nbytes = l;
    UTF32Char c;
    utf8to32(s, s + l, &c);
    return c;
}


void
UTF8tokenize(STLVector<String>::Type &tokens, 
             const String& str, 
             String delimiters)
{
    String::size_type lastPos = str.find_first_not_of(delimiters, 0);
    String::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (pos != String::npos || lastPos != String::npos)
    {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}

void
UTF8tokenize(APIAllocatable::STLVector<String>::Type &tokens, 
             const String& str, 
             String delimiters)
{
    String::size_type lastPos = str.find_first_not_of(delimiters, 0);
    String::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (pos != String::npos || lastPos != String::npos)
    {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}

UTF16String
UTF16convert(const Mu::String& s)
{
    const char* c = s.c_str();
    int n = s.size();
    int i = 0;
    UTF16String u;

    while (i < n)
    {
        int nc;
        u.push_back(UTF16String::value_type(UTF8convert(c + i, nc)));
        i += nc;
    }
    
    return u;
}

} // namespace Mu
