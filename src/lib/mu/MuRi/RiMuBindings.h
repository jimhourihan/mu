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

#ifndef __RIMUBINDINGS_H__
#define __RIMUBINDINGS_H__

#include <vector>
#include <string>

#include <Mu/Module.h>
#include <Mu/Node.h>

#include <ri.h>

namespace RiMu {

typedef std::vector<RtLightHandle> LightHandles;

class RiMuBindings
{
public:
    RiMuBindings() {}
    ~RiMuBindings() {}
    
    static void addSymbols( Mu::Context *context );

    static NODE_DECLARATION( RiAttributeBegin, void );
    static NODE_DECLARATION( RiAttribute, void );
    static NODE_DECLARATION( RiAttributeEnd, void );

    static NODE_DECLARATION( RiTransformBegin, void );
    static NODE_DECLARATION( RiTransformEnd, void );
    static NODE_DECLARATION( RiTranslatef, void );
    static NODE_DECLARATION( RiTranslatev, void );
    static NODE_DECLARATION( RiRotate, void );
    static NODE_DECLARATION( RiScale, void );
    static NODE_DECLARATION( RiTransformF, void );
    static NODE_DECLARATION( RiTransformM, void );
    static NODE_DECLARATION( RiConcatTransformF, void );
    static NODE_DECLARATION( RiConcatTransformM, void );

    static NODE_DECLARATION( RiMotionBegin, void );
    static NODE_DECLARATION( RiMotionEnd, void );

    static NODE_DECLARATION( RiColor, void );
    static NODE_DECLARATION( RiColorf, void );
    static NODE_DECLARATION( RiOpacity, void );
    static NODE_DECLARATION( RiOpacityf, void );
    static NODE_DECLARATION( RiMatte, void );
    static NODE_DECLARATION( RiSurface, void );
    static NODE_DECLARATION( RiDisplacement, void );

    static NODE_DECLARATION( RiLightSource, int );
    static NODE_DECLARATION( RiIlluminate, void );

    static NODE_DECLARATION( RiBasis, void );
    static NODE_DECLARATION( RiPoints, void );
    static NODE_DECLARATION( RiCurves, void );
    static NODE_DECLARATION( RiSphere, void );
    static NODE_DECLARATION( RiPolygon, void );

    static NODE_DECLARATION( RiProcedural, void );
    static NODE_DECLARATION( RiTransformPoints, bool );

private:
    static void RiProceduralFinished( RtPointer data );
    static RtBasis &basisFromStr( std::string name );

    static bool parseTokens( const Mu::Node &node_, 
                             Mu::Thread &thread_,
                             RtToken *tokens,
                             RtPointer *pointers,
                             int &numTokens,
                             int &numP,
                             int startAtArg = 0 );

    static void freeTokens( RtToken *tokens,
                            int numTokens,
                            int startAtArg = 0 );

    static LightHandles m_lightHandles;
};

}  //  End namespace RiMu

#endif    // End #ifdef __RIMUBINDINGS_H__

