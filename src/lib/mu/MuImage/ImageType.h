#ifndef __MuLang__ImageType__h__
#define __MuLang__ImageType__h__
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
#include <Mu/Vector.h>
#include <MuLang/StringType.h>
#include <MuLang/DynamicArray.h>
#include <iosfwd>
#include <string>

namespace Mu {

//
//  class ImageType
//
//  
//

class ImageType : public Class
{
  public:
    ImageType(Context* c, Class *super=0);
    ~ImageType();

    struct ImageStruct
    {
        const StringType::String* name;
        DynamicArray*             data;
        int                       width;
        int                       height;

        Vector4f* row(int y) { return data->data<Vector4f>() + (y * width); }
        Vector4f& pixel(int x,int y) { return data->data<Vector4f>()[x + y * width]; }
        Vector4f  sample(float x, float y);
    };

    //
    //	Load function is called when the symbol is added to the
    //	context.
    //

    virtual void load();

    //
    //	Constant
    //

    static NODE_DECLARATION(construct,Pointer);
    static NODE_DECLARATION(dereference,Pointer);
    static NODE_DECLARATION(print,void);
    static NODE_DECLARATION(sample, Vector4f);
};

} // namespace Mu

#endif // __MuLang__ImageType__h__
