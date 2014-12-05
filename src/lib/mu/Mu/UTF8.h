#ifndef __Mu__UTF8__h__
#define __Mu__UTF8__h__
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
#include <stdlib.h>
#include <Mu/config.h>
#include <Mu/GarbageCollector.h>

namespace Mu {

//
//  Return the length (num characters) of a UTF-8 string
//  Assumes a proper UTF-8 string
//

size_t UTF8len(const char* s);

//
//  Convert the UTF-8 possibly multibyte character at c
//  into a UTF-32 encoding
//
//  Assumes a proper UTF-8 string
//

UTF32Char UTF8convert(const char* c, int& n);

//
//  Tokenize a string into a buffer
//

void UTF8tokenize(STLVector<Mu::String>::Type &tokens,
                  const Mu::String& str, 
                  Mu::String delimiters = " ");

void UTF8tokenize(APIAllocatable::STLVector<Mu::String>::Type &tokens,
                  const Mu::String& str, 
                  Mu::String delimiters = " ");

//
//  Convert a UTF-8 string in to a UTF32 string
//

Mu::UTF16String UTF16convert(const Mu::String& s);

} // namespace Mu

#endif // __Mu__UTF8__h__
