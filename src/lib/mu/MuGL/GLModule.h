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

#ifndef __runtime__GLModule__h__
#define __runtime__GLModule__h__

#include <Mu/Module.h>
#include <Mu/Node.h>

// !!! ajg - too much editing ???

namespace Mu {

class GLModule : public Module
{
  public:
    GLModule(Context* c, const char *name);
    virtual ~GLModule();

    virtual void load();

    static void init(const char*, Context*);

    //
    // Note:  These are ALL the OpenGL 1.1 functions.  If they're commented 
    //        out, then they are either unimplemented, or implemented 
    //        slightly differently in Mu (like glColor*,  glVertex*, etc).
    //

    static NODE_DECLARATION(glAccum, void);
    static NODE_DECLARATION(glAlphaFunc, void);
//     static NODE_DECLARATION(glAreTexturesResident, bool);
    static NODE_DECLARATION(glArrayElement, void);
    static NODE_DECLARATION(glBegin, void);
    static NODE_DECLARATION(glBindTexture, void);
//     static NODE_DECLARATION(glBitmap, void);
    static NODE_DECLARATION(glBlendFunc, void);
    static NODE_DECLARATION(glCallList, void);
//     static NODE_DECLARATION(glCallLists, void);
    static NODE_DECLARATION(glClear, void);
    static NODE_DECLARATION(glClearAccum, void);
    static NODE_DECLARATION(glClearColor, void);
    static NODE_DECLARATION(glClearDepth, void);
    static NODE_DECLARATION(glClearIndex, void);
    static NODE_DECLARATION(glClearStencil, void);
    static NODE_DECLARATION(glClipPlane, void);
//     static NODE_DECLARATION(glColor3b, void);
//     static NODE_DECLARATION(glColor3bv, void);
//     static NODE_DECLARATION(glColor3d, void);
//     static NODE_DECLARATION(glColor3dv, void);
    static NODE_DECLARATION(glColor3f, void);
    static NODE_DECLARATION(glColor3fv, void);
//     static NODE_DECLARATION(glColor3i, void);
//     static NODE_DECLARATION(glColor3iv, void);
//     static NODE_DECLARATION(glColor3s, void);
//     static NODE_DECLARATION(glColor3sv, void);
//     static NODE_DECLARATION(glColor3ub, void);
//     static NODE_DECLARATION(glColor3ubv, void);
//     static NODE_DECLARATION(glColor3ui, void);
//     static NODE_DECLARATION(glColor3uiv, void);
//     static NODE_DECLARATION(glColor3us, void);
//     static NODE_DECLARATION(glColor3usv, void);
//     static NODE_DECLARATION(glColor4b, void);
//     static NODE_DECLARATION(glColor4bv, void);
//     static NODE_DECLARATION(glColor4d, void);
//     static NODE_DECLARATION(glColor4dv, void);
    static NODE_DECLARATION(glColor4f, void);
    static NODE_DECLARATION(glColor4fv, void);
//     static NODE_DECLARATION(glColor4i, void);
//     static NODE_DECLARATION(glColor4iv, void);
//     static NODE_DECLARATION(glColor4s, void);
//     static NODE_DECLARATION(glColor4sv, void);
//     static NODE_DECLARATION(glColor4ub, void);
//     static NODE_DECLARATION(glColor4ubv, void);
//     static NODE_DECLARATION(glColor4ui, void);
//     static NODE_DECLARATION(glColor4uiv, void);
//     static NODE_DECLARATION(glColor4us, void);
//     static NODE_DECLARATION(glColor4usv, void);
    static NODE_DECLARATION(glColorMask, void);
    static NODE_DECLARATION(glColorMaterial, void);
//     static NODE_DECLARATION(glColorPointer, void);
    static NODE_DECLARATION(glCopyPixels, void);
    static NODE_DECLARATION(glCopyTexImage1D, void);
    static NODE_DECLARATION(glCopyTexImage2D, void);
    static NODE_DECLARATION(glCopyTexSubImage1D, void);
    static NODE_DECLARATION(glCopyTexSubImage2D, void);
    static NODE_DECLARATION(glCullFace, void);
    static NODE_DECLARATION(glDeleteLists, void);
    static NODE_DECLARATION(glDeleteTextures, void);
    static NODE_DECLARATION(glDepthFunc, void);
    static NODE_DECLARATION(glDepthMask, void);
    static NODE_DECLARATION(glDepthRange, void);
    static NODE_DECLARATION(glDisable, void);
    static NODE_DECLARATION(glDisableClientState, void);
    static NODE_DECLARATION(glDrawArrays, void);
    static NODE_DECLARATION(glDrawBuffer, void);
    static NODE_DECLARATION(glDrawElements, void);
    static NODE_DECLARATION(glDrawPixels, void);
    static NODE_DECLARATION(glEdgeFlag, void);
//     static NODE_DECLARATION(glEdgeFlagPointer, void);
//     static NODE_DECLARATION(glEdgeFlagv, void);
    static NODE_DECLARATION(glEnable, void);
    static NODE_DECLARATION(glEnableClientState, void);
    static NODE_DECLARATION(glEnd, void);
    static NODE_DECLARATION(glEndList, void);
//     static NODE_DECLARATION(glEvalCoord1d, void);
//     static NODE_DECLARATION(glEvalCoord1dv, void);
    static NODE_DECLARATION(glEvalCoord1f, void);
//     static NODE_DECLARATION(glEvalCoord1fv, void);
//     static NODE_DECLARATION(glEvalCoord2d, void);
//     static NODE_DECLARATION(glEvalCoord2dv, void);
    static NODE_DECLARATION(glEvalCoord2f, void);
//     static NODE_DECLARATION(glEvalCoord2fv, void);
    static NODE_DECLARATION(glEvalMesh1, void);
    static NODE_DECLARATION(glEvalMesh2, void);
    static NODE_DECLARATION(glEvalPoint1, void);
    static NODE_DECLARATION(glEvalPoint2, void);
//     static NODE_DECLARATION(glFeedbackBuffer, void);
    static NODE_DECLARATION(glFinish, void);
    static NODE_DECLARATION(glFlush, void);
    static NODE_DECLARATION(glFogf, void);
    static NODE_DECLARATION(glFogfv, void);
    static NODE_DECLARATION(glFogi, void);
    static NODE_DECLARATION(glFogiv, void);
    static NODE_DECLARATION(glFrontFace, void);
    static NODE_DECLARATION(glFrustum, void);
    static NODE_DECLARATION(glGenLists, int);
    static NODE_DECLARATION(glGenTextures, Pointer);
    static NODE_DECLARATION(glGetBooleanv, Pointer);
    static NODE_DECLARATION(glGetClipPlane, Pointer);
//     static NODE_DECLARATION(glGetDoublev, void);
    static NODE_DECLARATION(glGetError, int);
    static NODE_DECLARATION(glGetFloatv, Pointer);
    static NODE_DECLARATION(glGetIntegerv, Pointer);
//     static NODE_DECLARATION(glGetLightfv, void);
//     static NODE_DECLARATION(glGetLightiv, void);
//     static NODE_DECLARATION(glGetMapdv, void);
//     static NODE_DECLARATION(glGetMapfv, void);
//     static NODE_DECLARATION(glGetMapiv, void);
//     static NODE_DECLARATION(glGetMaterialfv, void);
//     static NODE_DECLARATION(glGetMaterialiv, void);
//     static NODE_DECLARATION(glGetPixelMapfv, void);
//     static NODE_DECLARATION(glGetPixelMapuiv, void);
//     static NODE_DECLARATION(glGetPixelMapusv, void);
//     static NODE_DECLARATION(glGetPointerv, void);
//     static NODE_DECLARATION(glGetPolygonStipple, void);
    static NODE_DECLARATION(glGetString, Pointer);
//     static NODE_DECLARATION(glGetTexEnvfv, void);
//     static NODE_DECLARATION(glGetTexEnviv, void);
//     static NODE_DECLARATION(glGetTexGendv, void);
//     static NODE_DECLARATION(glGetTexGenfv, void);
//     static NODE_DECLARATION(glGetTexGeniv, void);
//     static NODE_DECLARATION(glGetTexImage, void);
//     static NODE_DECLARATION(glGetTexLevelParameterfv, void);
//     static NODE_DECLARATION(glGetTexLevelParameteriv, void);
//     static NODE_DECLARATION(glGetTexParameterfv, void);
//     static NODE_DECLARATION(glGetTexParameteriv, void);
    static NODE_DECLARATION(glHint, void);
    static NODE_DECLARATION(glIndexMask, void);
//     static NODE_DECLARATION(glIndexPointer, void);
//     static NODE_DECLARATION(glIndexd, void);
//     static NODE_DECLARATION(glIndexdv, void);
    static NODE_DECLARATION(glIndexf, void);
//     static NODE_DECLARATION(glIndexfv, void);
    static NODE_DECLARATION(glIndexi, void);
//     static NODE_DECLARATION(glIndexiv, void);
//     static NODE_DECLARATION(glIndexs, void);
//     static NODE_DECLARATION(glIndexsv, void);
//     static NODE_DECLARATION(glIndexub, void);
//     static NODE_DECLARATION(glIndexubv, void);
    static NODE_DECLARATION(glInitNames, void);
    static NODE_DECLARATION(glInterleavedArrays, void);
    static NODE_DECLARATION(glIsEnabled, bool);
    static NODE_DECLARATION(glIsList, bool);
    static NODE_DECLARATION(glIsTexture, bool);
    static NODE_DECLARATION(glLightModelf, void);
//     static NODE_DECLARATION(glLightModelfv, void);
    static NODE_DECLARATION(glLightModeli, void);
//     static NODE_DECLARATION(glLightModeliv, void);
    static NODE_DECLARATION(glLightf, void);
//     static NODE_DECLARATION(glLightfv, void);
    static NODE_DECLARATION(glLighti, void);
//     static NODE_DECLARATION(glLightiv, void);
    static NODE_DECLARATION(glLineStipple, void);
    static NODE_DECLARATION(glLineWidth, void);
    static NODE_DECLARATION(glListBase, void);
    static NODE_DECLARATION(glLoadIdentity, void);
//     static NODE_DECLARATION(glLoadMatrixd, void);
    static NODE_DECLARATION(glLoadMatrixf, void);
    static NODE_DECLARATION(glLoadName, void);
    static NODE_DECLARATION(glLogicOp, void);
//     static NODE_DECLARATION(glMap1d, void);
//     static NODE_DECLARATION(glMap1f, void);
//     static NODE_DECLARATION(glMap2d, void);
//     static NODE_DECLARATION(glMap2f, void);
//     static NODE_DECLARATION(glMapGrid1d, void);
    static NODE_DECLARATION(glMapGrid1f, void);
//     static NODE_DECLARATION(glMapGrid2d, void);
    static NODE_DECLARATION(glMapGrid2f, void);
    static NODE_DECLARATION(glMaterialf, void);
//     static NODE_DECLARATION(glMaterialfv, void);
    static NODE_DECLARATION(glMateriali, void);
//     static NODE_DECLARATION(glMaterialiv, void);
    static NODE_DECLARATION(glMatrixMode, void);
//     static NODE_DECLARATION(glMultMatrixd, void);
    static NODE_DECLARATION(glMultMatrixf, void);
    static NODE_DECLARATION(glNewList, void);
//     static NODE_DECLARATION(glNormal3b, void);
//     static NODE_DECLARATION(glNormal3bv, void);
//     static NODE_DECLARATION(glNormal3d, void);
//     static NODE_DECLARATION(glNormal3dv, void);
    static NODE_DECLARATION(glNormal3f, void);
    static NODE_DECLARATION(glNormal3fv, void);
//     static NODE_DECLARATION(glNormal3i, void);
//     static NODE_DECLARATION(glNormal3iv, void);
//     static NODE_DECLARATION(glNormal3s, void);
//     static NODE_DECLARATION(glNormal3sv, void);
//     static NODE_DECLARATION(glNormalPointer, void);
    static NODE_DECLARATION(glOrtho, void);
    static NODE_DECLARATION(glPassThrough, void);
//     static NODE_DECLARATION(glPixelMapfv, void);
//     static NODE_DECLARATION(glPixelMapuiv, void);
//     static NODE_DECLARATION(glPixelMapusv, void);
    static NODE_DECLARATION(glPixelStoref, void);
    static NODE_DECLARATION(glPixelStorei, void);
    static NODE_DECLARATION(glPixelTransferf, void);
    static NODE_DECLARATION(glPixelTransferi, void);
    static NODE_DECLARATION(glPixelZoom, void);
    static NODE_DECLARATION(glPointSize, void);
    static NODE_DECLARATION(glPolygonMode, void);
    static NODE_DECLARATION(glPolygonOffset, void);
    static NODE_DECLARATION(glPolygonStipple, void);
    static NODE_DECLARATION(glPopAttrib, void);
    static NODE_DECLARATION(glPopClientAttrib, void);
    static NODE_DECLARATION(glPopMatrix, void);
    static NODE_DECLARATION(glPopName, void);
//     static NODE_DECLARATION(glPrioritizeTextures, void);
    static NODE_DECLARATION(glPushAttrib, void);
    static NODE_DECLARATION(glPushClientAttrib, void);
    static NODE_DECLARATION(glPushMatrix, void);
    static NODE_DECLARATION(glPushName, void);
//     static NODE_DECLARATION(glRasterPos2d, void);
//     static NODE_DECLARATION(glRasterPos2dv, void);
    static NODE_DECLARATION(glRasterPos2f, void);
    static NODE_DECLARATION(glRasterPos2fv, void);
//     static NODE_DECLARATION(glRasterPos2i, void);
//     static NODE_DECLARATION(glRasterPos2iv, void);
//     static NODE_DECLARATION(glRasterPos2s, void);
//     static NODE_DECLARATION(glRasterPos2sv, void);
//     static NODE_DECLARATION(glRasterPos3d, void);
//     static NODE_DECLARATION(glRasterPos3dv, void);
    static NODE_DECLARATION(glRasterPos3f, void);
    static NODE_DECLARATION(glRasterPos3fv, void);
//     static NODE_DECLARATION(glRasterPos3i, void);
//     static NODE_DECLARATION(glRasterPos3iv, void);
//     static NODE_DECLARATION(glRasterPos3s, void);
//     static NODE_DECLARATION(glRasterPos3sv, void);
//     static NODE_DECLARATION(glRasterPos4d, void);
//     static NODE_DECLARATION(glRasterPos4dv, void);
//     static NODE_DECLARATION(glRasterPos4f, void);
//     static NODE_DECLARATION(glRasterPos4fv, void);
//     static NODE_DECLARATION(glRasterPos4i, void);
//     static NODE_DECLARATION(glRasterPos4iv, void);
//     static NODE_DECLARATION(glRasterPos4s, void);
//     static NODE_DECLARATION(glRasterPos4sv, void);
    static NODE_DECLARATION(glReadBuffer, void);
    static NODE_DECLARATION(glReadPixels, void);
//     static NODE_DECLARATION(glRectd, void);
//     static NODE_DECLARATION(glRectdv, void);
//     static NODE_DECLARATION(glRectf, void);
//     static NODE_DECLARATION(glRectfv, void);
//     static NODE_DECLARATION(glRecti, void);
//     static NODE_DECLARATION(glRectiv, void);
//     static NODE_DECLARATION(glRects, void);
//     static NODE_DECLARATION(glRectsv, void);
    static NODE_DECLARATION(glRenderMode, int);
//     static NODE_DECLARATION(glRotated, void);
    static NODE_DECLARATION(glRotatef, void);
//     static NODE_DECLARATION(glScaled, void);
    static NODE_DECLARATION(glScalef, void);
    static NODE_DECLARATION(glScissor, void);
//     static NODE_DECLARATION(glSelectBuffer, void);
    static NODE_DECLARATION(glShadeModel, void);
    static NODE_DECLARATION(glStencilFunc, void);
    static NODE_DECLARATION(glStencilMask, void);
    static NODE_DECLARATION(glStencilOp, void);
//     static NODE_DECLARATION(glTexCoord1d, void);
//     static NODE_DECLARATION(glTexCoord1dv, void);
    static NODE_DECLARATION(glTexCoord1f, void);
//     static NODE_DECLARATION(glTexCoord1fv, void);
//     static NODE_DECLARATION(glTexCoord1i, void);
//     static NODE_DECLARATION(glTexCoord1iv, void);
//     static NODE_DECLARATION(glTexCoord1s, void);
//     static NODE_DECLARATION(glTexCoord1sv, void);
//     static NODE_DECLARATION(glTexCoord2d, void);
//     static NODE_DECLARATION(glTexCoord2dv, void);
    static NODE_DECLARATION(glTexCoord2f, void);
    static NODE_DECLARATION(glTexCoord2fv, void);
//     static NODE_DECLARATION(glTexCoord2i, void);
//     static NODE_DECLARATION(glTexCoord2iv, void);
//     static NODE_DECLARATION(glTexCoord2s, void);
//     static NODE_DECLARATION(glTexCoord2sv, void);
//     static NODE_DECLARATION(glTexCoord3d, void);
//     static NODE_DECLARATION(glTexCoord3dv, void);
    static NODE_DECLARATION(glTexCoord3f, void);
    static NODE_DECLARATION(glTexCoord3fv, void);
//     static NODE_DECLARATION(glTexCoord3i, void);
//     static NODE_DECLARATION(glTexCoord3iv, void);
//     static NODE_DECLARATION(glTexCoord3s, void);
//     static NODE_DECLARATION(glTexCoord3sv, void);
//     static NODE_DECLARATION(glTexCoord4d, void);
//     static NODE_DECLARATION(glTexCoord4dv, void);
//     static NODE_DECLARATION(glTexCoord4f, void);
//     static NODE_DECLARATION(glTexCoord4fv, void);
//     static NODE_DECLARATION(glTexCoord4i, void);
//     static NODE_DECLARATION(glTexCoord4iv, void);
//     static NODE_DECLARATION(glTexCoord4s, void);
//     static NODE_DECLARATION(glTexCoord4sv, void);
//     static NODE_DECLARATION(glTexCoordPointer, void);
    static NODE_DECLARATION(glTexEnvf, void);
//     static NODE_DECLARATION(glTexEnvfv, void);
    static NODE_DECLARATION(glTexEnvi, void);
//     static NODE_DECLARATION(glTexEnviv, void);
//     static NODE_DECLARATION(glTexGend, void);
//     static NODE_DECLARATION(glTexGendv, void);
    static NODE_DECLARATION(glTexGenf, void);
//     static NODE_DECLARATION(glTexGenfv, void);
    static NODE_DECLARATION(glTexGeni, void);
//     static NODE_DECLARATION(glTexGeniv, void);
    static NODE_DECLARATION(glTexImage1D, void);
    static NODE_DECLARATION(glTexImage2D, void);
    static NODE_DECLARATION(glTexParameterf, void);
//     static NODE_DECLARATION(glTexParameterfv, void);
    static NODE_DECLARATION(glTexParameteri, void);
//     static NODE_DECLARATION(glTexParameteriv, void);
    static NODE_DECLARATION(glTexSubImage1D, void);
    static NODE_DECLARATION(glTexSubImage2D, void);
//     static NODE_DECLARATION(glTranslated, void);
    static NODE_DECLARATION(glTranslatef, void);
//     static NODE_DECLARATION(glVertex2d, void);
//     static NODE_DECLARATION(glVertex2dv, void);
    static NODE_DECLARATION(glVertex2f, void);
    static NODE_DECLARATION(glVertex2fv, void);
//     static NODE_DECLARATION(glVertex2i, void);
//     static NODE_DECLARATION(glVertex2iv, void);
//     static NODE_DECLARATION(glVertex2s, void);
//     static NODE_DECLARATION(glVertex2sv, void);
//     static NODE_DECLARATION(glVertex3d, void);
//     static NODE_DECLARATION(glVertex3dv, void);
    static NODE_DECLARATION(glVertex3f, void);
    static NODE_DECLARATION(glVertex3fv, void);
//     static NODE_DECLARATION(glVertex3i, void);
//     static NODE_DECLARATION(glVertex3iv, void);
//     static NODE_DECLARATION(glVertex3s, void);
//     static NODE_DECLARATION(glVertex3sv, void);
//     static NODE_DECLARATION(glVertex4d, void);
//     static NODE_DECLARATION(glVertex4dv, void);
//     static NODE_DECLARATION(glVertex4f, void);
//     static NODE_DECLARATION(glVertex4fv, void);
//     static NODE_DECLARATION(glVertex4i, void);
//     static NODE_DECLARATION(glVertex4iv, void);
//     static NODE_DECLARATION(glVertex4s, void);
//     static NODE_DECLARATION(glVertex4sv, void);
//     static NODE_DECLARATION(glVertexPointer, void);
    static NODE_DECLARATION(glViewport, void);

    static NODE_DECLARATION(glVertexPointer4fv, void);
    static NODE_DECLARATION(glVertexPointer3fv, void);
    static NODE_DECLARATION(glVertexPointer2fv, void);
    static NODE_DECLARATION(glNormalPointer3fv, void);
    static NODE_DECLARATION(glColorPointer4fv, void);
    static NODE_DECLARATION(glColorPointer3fv, void);
    static NODE_DECLARATION(glIndexPointer, void);
    static NODE_DECLARATION(glTexCoordPointer4fv, void);
    static NODE_DECLARATION(glTexCoordPointer3fv, void);
    static NODE_DECLARATION(glTexCoordPointer2fv, void);
    static NODE_DECLARATION(glTexCoordPointer1f, void);
};

} // namespace Mu

#endif // __runtime__GLModule__h__
