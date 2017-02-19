// The MIT License (MIT)
//
// This is free and unencumbered software released into the public domain.
// 
// Anyone is free to copy, modify, publish, use, compile, sell, or distribute
// this software, either in source code form or as a compiled binary, for any
// purpose, commercial or non - commercial, and by any means.
// 
// In jurisdictions that recognize copyright laws, the author or authors of
// this software dedicate any and all copyright interest in the software to
// the public domain.We make this dedication for the benefit of the public
// at large and to the detriment of our heirs and successors.We intend this
// dedication to be an overt act of relinquishment in perpetuity of all
// present and future rights to this software under copyright law.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL
// THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#pragma once
#ifndef MagnumImgui_h__
#define MagnumImgui_h__

#include <Magnum/Platform/Sdl2Application.h>
#include <Magnum/AbstractShaderProgram.h>
#include <Magnum/Math/Matrix4.h>
#include <Magnum/Texture.h>
#include <Magnum/Buffer.h>
#include <Magnum/Mesh.h>
#include <Magnum/Timeline.h>
#include <Magnum/Attribute.h>

class ImguiShader : public Magnum::AbstractShaderProgram
{
public:
  typedef Magnum::Attribute<0, Magnum::Vector2> Position;
  typedef Magnum::Attribute<1, Magnum::Vector2> TextureCoordinates;
  typedef Magnum::Attribute<2, Magnum::Vector4> Color;

  ImguiShader();

  ImguiShader& setProjectMatrix(const Magnum::Matrix4& matrix)
  {
    setUniform(mProjMatrixUniform, matrix);
    return *this;
  }

  ImguiShader& setTexture(Magnum::Texture2D& texture)
  {
    texture.bind(TextureLayer);
    return *this;
  }

private:
  enum : Magnum::Int { TextureLayer = 0 };

  Magnum::Int mProjMatrixUniform;
};


class MagnumImgui
{
public:
  MagnumImgui();
  ~MagnumImgui();

  void newFrame(const Magnum::Vector2i &winSize, const Magnum::Vector2i &viewportSize);

  void drawFrame();

  void mousePressEvent(const Magnum::Platform::Application::MouseEvent& event);

  void mouseReleaseEvent(const Magnum::Platform::Application::MouseEvent& event);

  void mouseScrollEvent(const Magnum::Platform::Application::MouseScrollEvent& event);

  void mouseMoveEvent(const Magnum::Platform::Application::MouseMoveEvent& event);

  void keyPressEvent(const Magnum::Platform::Application::KeyEvent& event);

  void keyReleaseEvent(const Magnum::Platform::Application::KeyEvent& event);

  void textInputEvent(const Magnum::Platform::Application::TextInputEvent& event);

private:
  ImguiShader mShader;
  Magnum::Texture2D mTexture;
  Magnum::Buffer mVertexBuffer;
  Magnum::Buffer mIndexBuffer;
  Magnum::Timeline mTimeline;
  Magnum::Mesh mMesh;

  bool mMousePressed[3] = { false, false, false };
  float mMouseScroll = 0.0f;
  Magnum::Vector2i mMousePos;

private:
  void init();
  void load();

  void keyPressReleaseEvent(const Magnum::Platform::Application::KeyEvent& event, bool value);
  void mousePressReleaseEvent(const Magnum::Platform::Application::MouseEvent& event, bool value);
};


#endif // MagnumImgui_h__

