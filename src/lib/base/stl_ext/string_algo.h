//
//  Copyright (c) 2010, Jim Hourihan
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
//     * Neither the name of stl_ext nor the names of its
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
#ifndef __stl_ext_string_algo__h__
#define __stl_ext_string_algo__h__
#include <string>
#include <vector>
#include <stl_ext/stl_ext_config.h>

namespace stl_ext {

//
//  Tokenize, like the C function. Returns a vector of strings with
//  the tokens in it. Lifted from some linux help site.
//

STL_EXT_EXPORT void tokenize(std::vector<std::string> &tokens,
                             const std::string& str, 
                             std::string delimiters = " ");

//
//  Wrap the text to some column width, break at char
//

STL_EXT_EXPORT std::string wrap(const std::string& text,
                                char wrapChar = ' ',
                                const std::string& breakString = "\n",
                                std::string::size_type column = 65);

// Returns the directory part of the path
STL_EXT_EXPORT std::string dirname( std::string path );

// Returns the file part of the path
STL_EXT_EXPORT std::string basename( std::string path );

// Returns "file" for "/tmp/file.tif"
STL_EXT_EXPORT std::string prefix( std::string path );

// Returns the file extension (if there is one, "" otherwise )
STL_EXT_EXPORT std::string extension( std::string path );

// Returns a hash value for the given string
STL_EXT_EXPORT unsigned long hash(const std::string& s);

} // namespace stl_ext

#endif
