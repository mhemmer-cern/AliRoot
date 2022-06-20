//**************************************************************************\
//* This file is property of and copyright by the ALICE Project            *\
//* ALICE Experiment at CERN, All rights reserved.                         *\
//*                                                                        *\
//* Primary Authors: Matthias Richter <Matthias.Richter@ift.uib.no>        *\
//*                  for The ALICE HLT Project.                            *\
//*                                                                        *\
//* Permission to use, copy, modify and distribute this software and its   *\
//* documentation strictly for non-commercial purposes is hereby granted   *\
//* without fee, provided that the above copyright notice appears in all   *\
//* copies and that both the copyright notice and this permission notice   *\
//* appear in the supporting documentation. The authors make no claims     *\
//* about the suitability of this software for any purpose. It is          *\
//* provided "as is" without express or implied warranty.                  *\
//**************************************************************************

/// \file GPUDisplayBackendOpenGL.h
/// \author David Rohr

#ifndef GPUDISPLAYBACKENDOPENGL_H
#define GPUDISPLAYBACKENDOPENGL_H

#include "GPUDisplayBackend.h"

#include <vector>

namespace GPUCA_NAMESPACE::gpu
{
struct GLfb {
  unsigned int fb_id = 0, fbCol_id = 0, fbDepth_id = 0;
  bool tex = false;
  bool msaa = false;
  bool depth = false;
  bool created = false;
};
class GPUDisplayBackendOpenGL : public GPUDisplayBackend
{
 public:
  GPUDisplayBackendOpenGL();
  ~GPUDisplayBackendOpenGL() override = default;
  int ExtInit() override;
  bool CoreProfile() override;
  unsigned int DepthBits() override;

 protected:
  void createFB(GLfb& fb, bool tex, bool withDepth, bool msaa, unsigned int width, unsigned int height);
  void deleteFB(GLfb& fb);

  unsigned int drawVertices(const vboList& v, const drawType t) override;
  void ActivateColor(std::array<float, 4>& color) override;
  void setQuality() override;
  void setDepthBuffer() override;
  void setFrameBuffer(unsigned int newID = 0);
  int InitBackendA() override;
  void ExitBackendA() override;
  void clearScreen(bool alphaOnly = false);
  void loadDataToGPU(size_t totalVertizes) override;
  void prepareDraw(const hmm_mat4& proj, const hmm_mat4& view, bool requestScreenshot, bool toMixBuffer, float includeMixImage) override;
  void resizeScene(unsigned int width, unsigned int height) override;
  void updateRenderer(bool withScreenshot);
  void ClearOffscreenBuffers();
  void finishDraw(bool doScreenshot, bool toMixBuffer, float includeMixImage) override;
  void finishFrame(bool doScreenshot, bool toMixBuffer, float includeMixImage) override;
  void prepareText() override;
  void finishText() override;
  void mixImages(float mixSlaveImage);
  void pointSizeFactor(float factor) override;
  void lineWidthFactor(float factor) override;
  size_t needMultiVBO() override { return 0x100000000ll; }
  void readImageToPixels();

  void addFontSymbol(int symbol, int sizex, int sizey, int offsetx, int offsety, int advance, void* data) override;
  void initializeTextDrawing() override;
  void OpenGLPrint(const char* s, float x, float y, float* color, float scale) override;

  struct FontSymbolOpenGL : public FontSymbol {
    unsigned int texId;
  };

  unsigned int mVertexShader;
  unsigned int mFragmentShader;
  unsigned int mVertexShaderTexture;
  unsigned int mFragmentShaderTexture;
  unsigned int mFragmentShaderText;
  unsigned int mShaderProgram;
  unsigned int mShaderProgramText;
  unsigned int mShaderProgramTexture;
  unsigned int mVertexArray;

  unsigned int mIndirectId;
  std::vector<unsigned int> mVBOId;
  std::vector<FontSymbolOpenGL> mFontSymbols;
  int mModelViewProjId;
  int mColorId;
  int mModelViewProjIdTexture;
  int mAlphaIdTexture;
  int mModelViewProjIdText;
  int mColorIdText;
  unsigned int mSPIRVModelViewBuffer;
  unsigned int mSPIRVColorBuffer;

  unsigned int VAO_text, VBO_text;

  unsigned int VAO_texture, VBO_texture;

  bool mSPIRVShaders = false;

  GLfb mMixBuffer;
  GLfb mOffscreenBufferMSAA, mOffscreenBuffer;
};
} // namespace GPUCA_NAMESPACE::gpu

#endif