#ifndef __runtime__IOModule__h__
#define __runtime__IOModule__h__
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
#include <Mu/Module.h>
#include <Mu/Node.h>

namespace Mu {

class IOModule : public Module
{
  public:
    IOModule(Context* c, const char *name);
    virtual ~IOModule();

    virtual void load();

    //
    //  Print Functions
    //

    static NODE_IMPLEMENTATION(printString, Pointer);
    static NODE_IMPLEMENTATION(print_int, Pointer);
    static NODE_IMPLEMENTATION(print_float, Pointer);
    static NODE_IMPLEMENTATION(print_double, Pointer);
    static NODE_IMPLEMENTATION(print_bool, Pointer);
    static NODE_IMPLEMENTATION(print_byte, Pointer);
    static NODE_IMPLEMENTATION(print_char, Pointer);
    static NODE_IMPLEMENTATION(print_endl, Pointer);
    static NODE_IMPLEMENTATION(print_flush, Pointer);

    static NODE_IMPLEMENTATION(readString, Pointer);
    static NODE_IMPLEMENTATION(read_int, int);
    static NODE_IMPLEMENTATION(read_float, float);
    static NODE_IMPLEMENTATION(read_double, double);
    static NODE_IMPLEMENTATION(read_bool, bool);
    static NODE_IMPLEMENTATION(read_byte, char);
    static NODE_IMPLEMENTATION(read_char, char);
    static NODE_IMPLEMENTATION(read_line, Pointer);
    static NODE_IMPLEMENTATION(read_all, Pointer);
    static NODE_IMPLEMENTATION(read_all_bytes, Pointer);

    static NODE_IMPLEMENTATION(in, Pointer);
    static NODE_IMPLEMENTATION(out, Pointer);
    static NODE_IMPLEMENTATION(err, Pointer);

    static NODE_IMPLEMENTATION(serialize, int);
    static NODE_IMPLEMENTATION(deserialize, Pointer);

    static NODE_IMPLEMENTATION(directory, Pointer);

    static NODE_IMPLEMENTATION(basename, Pointer);
    static NODE_IMPLEMENTATION(extension, Pointer);
    static NODE_IMPLEMENTATION(without_extension, Pointer);
    static NODE_IMPLEMENTATION(dirname, Pointer);
    static NODE_IMPLEMENTATION(exists, bool);
    static NODE_IMPLEMENTATION(expand, Pointer);
    static NODE_IMPLEMENTATION(join, Pointer);
    static NODE_IMPLEMENTATION(concat_paths, Pointer);
    static NODE_IMPLEMENTATION(path_separator, Pointer);
    static NODE_IMPLEMENTATION(concat_separator, Pointer);
};

} // namespace Mu

#endif // __runtime__IOModule__h__
