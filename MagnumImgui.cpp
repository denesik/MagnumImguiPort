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
#include "MagnumImgui.h"

#include <Magnum/Context.h>
#include <Magnum/Version.h>
#include <Magnum/Shader.h>
#include <Magnum/ImageView.h>
#include <Magnum/PixelFormat.h>
#include <Magnum/TextureFormat.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Renderer.h>

#include "imgui/imgui.h"

using namespace Magnum;

void MagnumImgui::init()
{
  ImGuiIO& io = ImGui::GetIO();
  io.KeyMap[ImGuiKey_Tab] = ImGuiKey_Tab;
  io.KeyMap[ImGuiKey_LeftArrow] = ImGuiKey_LeftArrow;
  io.KeyMap[ImGuiKey_RightArrow] = ImGuiKey_RightArrow;
  io.KeyMap[ImGuiKey_UpArrow] = ImGuiKey_UpArrow;
  io.KeyMap[ImGuiKey_DownArrow] = ImGuiKey_DownArrow;
  io.KeyMap[ImGuiKey_PageUp] = ImGuiKey_PageUp;
  io.KeyMap[ImGuiKey_PageDown] = ImGuiKey_PageDown;
  io.KeyMap[ImGuiKey_Home] = ImGuiKey_Home;
  io.KeyMap[ImGuiKey_End] = ImGuiKey_End;
  io.KeyMap[ImGuiKey_Delete] = ImGuiKey_Delete;
  io.KeyMap[ImGuiKey_Backspace] = ImGuiKey_Backspace;
  io.KeyMap[ImGuiKey_Enter] = ImGuiKey_Enter;
  io.KeyMap[ImGuiKey_Escape] = ImGuiKey_Escape;
  io.KeyMap[ImGuiKey_A] = ImGuiKey_A;
  io.KeyMap[ImGuiKey_C] = ImGuiKey_C;
  io.KeyMap[ImGuiKey_V] = ImGuiKey_V;
  io.KeyMap[ImGuiKey_X] = ImGuiKey_X;
  io.KeyMap[ImGuiKey_Y] = ImGuiKey_Y;
  io.KeyMap[ImGuiKey_Z] = ImGuiKey_Z;

//   io.SetClipboardTextFn = ;
//   io.GetClipboardTextFn = ;

  mTimeline.start();
}

void MagnumImgui::load()
{
  ImGuiIO& io = ImGui::GetIO();
  unsigned char* pixels;
  int width, height;
  int pixel_size;
  io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height, &pixel_size);

  ImageView2D image{ PixelFormat::RGBA, PixelType::UnsignedByte, { width, height },{ pixels, std::size_t(pixel_size * width * height) } };

  mTexture.setMagnificationFilter(Sampler::Filter::Linear)
    .setMinificationFilter(Sampler::Filter::Linear)
    .setStorage(0, TextureFormat::RGBA, image.size())
    .setImage(0, TextureFormat::RGBA, image);

    mMesh.setPrimitive(MeshPrimitive::Triangles);
    mMesh.addVertexBuffer(mVertexBuffer, 0, ImguiShader::Position{}, ImguiShader::TextureCoordinates{}, 
      ImguiShader::Color(ImguiShader::Color::Components::Four, ImguiShader::Color::DataType::UnsignedByte, ImguiShader::Color::DataOption::Normalized));
}

void MagnumImgui::keyPressReleaseEvent(const Platform::Application::KeyEvent& event, bool value)
{
  ImGuiIO& io = ImGui::GetIO();

  const auto &mods = event.modifiers();
  if (mods & Platform::Application::KeyEvent::Modifier::Shift) io.KeyShift = value;
  if (mods & Platform::Application::KeyEvent::Modifier::Ctrl) io.KeyCtrl = value;
  if (mods & Platform::Application::KeyEvent::Modifier::Alt) io.KeyAlt = value;

  switch (event.key())
  {
  case Platform::Application::KeyEvent::Key::Tab:
    io.KeysDown[ImGuiKey_Tab] = value;
    break;
  case Platform::Application::KeyEvent::Key::Up:
    io.KeysDown[ImGuiKey_UpArrow] = value;
    break;
  case Platform::Application::KeyEvent::Key::Down:
    io.KeysDown[ImGuiKey_DownArrow] = value;
    break;
  case Platform::Application::KeyEvent::Key::Left:
    io.KeysDown[ImGuiKey_LeftArrow] = value;
    break;
  case Platform::Application::KeyEvent::Key::Right:
    io.KeysDown[ImGuiKey_RightArrow] = value;
    break;
  case Platform::Application::KeyEvent::Key::Home:
    io.KeysDown[ImGuiKey_Home] = value;
    break;
  case Platform::Application::KeyEvent::Key::End:
    io.KeysDown[ImGuiKey_End] = value;
    break;
  case Platform::Application::KeyEvent::Key::PageUp:
    io.KeysDown[ImGuiKey_PageUp] = value;
    break;
  case Platform::Application::KeyEvent::Key::PageDown:
    io.KeysDown[ImGuiKey_PageDown] = value;
    break;
  case Platform::Application::KeyEvent::Key::Enter:
    io.KeysDown[ImGuiKey_Enter] = value;
    break;
  case Platform::Application::KeyEvent::Key::Esc:
    io.KeysDown[ImGuiKey_Escape] = value;
    break;
  case Platform::Application::KeyEvent::Key::Backspace:
    io.KeysDown[ImGuiKey_Backspace] = value;
    break;
  case Platform::Application::KeyEvent::Key::Delete:
    io.KeysDown[ImGuiKey_Delete] = value;
    break;
  case Platform::Application::KeyEvent::Key::A:
    io.KeysDown[ImGuiKey_A] = value;
    break;
  case Platform::Application::KeyEvent::Key::C:
    io.KeysDown[ImGuiKey_C] = value;
    break;
  case Platform::Application::KeyEvent::Key::V:
    io.KeysDown[ImGuiKey_V] = value;
    break;
  case Platform::Application::KeyEvent::Key::X:
    io.KeysDown[ImGuiKey_X] = value;
    break;
  case Platform::Application::KeyEvent::Key::Y:
    io.KeysDown[ImGuiKey_Y] = value;
    break;
  case Platform::Application::KeyEvent::Key::Z:
    io.KeysDown[ImGuiKey_Z] = value;
    break;
  default:
    break;
  }
}

void MagnumImgui::mousePressReleaseEvent(const Platform::Application::MouseEvent& event, bool value)
{
  switch (event.button())
  {
  case Magnum::Platform::Application::MouseEvent::Button::Left:
    mMousePressed[0] = value;
    break;
  case Magnum::Platform::Application::MouseEvent::Button::Right:
    mMousePressed[1] = value;
    break;
  case Magnum::Platform::Application::MouseEvent::Button::Middle:
    mMousePressed[2] = value;
    break;
  default:
    break;
  }
}

MagnumImgui::MagnumImgui()
{
  init();
  load();
}

MagnumImgui::~MagnumImgui()
{
  ImGui::Shutdown();
}

void MagnumImgui::newFrame(const Vector2i &winSize, const Vector2i &viewportSize)
{
  mTimeline.nextFrame();

  ImGuiIO& io = ImGui::GetIO();

  // Setup display size (every frame to accommodate for window resizing)
  io.DisplaySize = ImVec2((float)winSize.x(), (float)winSize.y());
  io.DisplayFramebufferScale = ImVec2(winSize.x() > 0 ? ((float)viewportSize.x() / winSize.x()) : 0,
    winSize.y() > 0 ? ((float)viewportSize.y() / winSize.y()) : 0);

  io.DeltaTime = mTimeline.previousFrameDuration();
  io.MousePos = ImVec2(float(mMousePos.x()), float(mMousePos.y()));

  for (int i = 0; i < 3; i++)
  {
    io.MouseDown[i] = mMousePressed[i];    
  }

  io.MouseWheel = mMouseScroll;
  mMouseScroll = 0.0f;

  ImGui::NewFrame();
}

void MagnumImgui::drawFrame()
{
  ImGui::Render();

  ImGuiIO& io = ImGui::GetIO();
  int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
  int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
  if (fb_width == 0 || fb_height == 0)
    return;

  auto draw_data = ImGui::GetDrawData();
  if (!draw_data)
    return;

  draw_data->ScaleClipRects(io.DisplayFramebufferScale);

  Renderer::enable(Renderer::Feature::Blending);
  Renderer::setBlendEquation(Magnum::Renderer::BlendEquation::Add, Magnum::Renderer::BlendEquation::Add);
  Renderer::setBlendFunction(Renderer::BlendFunction::SourceAlpha, Renderer::BlendFunction::OneMinusSourceAlpha);
  Renderer::disable(Renderer::Feature::FaceCulling);
  Renderer::disable(Renderer::Feature::DepthTest);
  Renderer::enable(Renderer::Feature::ScissorTest);

  const Matrix4 ortho_projection
  {
    { 2.0f / io.DisplaySize.x, 0.0f,                   0.0f, 0.0f },
    { 0.0f,                  2.0f / -io.DisplaySize.y, 0.0f, 0.0f },
    { 0.0f,                  0.0f,                  -1.0f, 0.0f },
    { -1.0f,                  1.0f,                   0.0f, 1.0f },
  };
  mShader.setProjectMatrix(ortho_projection);
  mShader.setTexture(mTexture);

  for (int n = 0; n < draw_data->CmdListsCount; n++)
  {
    const ImDrawList* cmd_list = draw_data->CmdLists[n];
    ImDrawIdx idx_buffer_offset = 0;

    mVertexBuffer.setData({ cmd_list->VtxBuffer.Data, std::size_t(cmd_list->VtxBuffer.Size) }, BufferUsage::StreamDraw);
    mIndexBuffer.setData({ cmd_list->IdxBuffer.Data, std::size_t(cmd_list->IdxBuffer.Size) }, BufferUsage::StreamDraw);
    
    for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
    {
      const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];

      Renderer::setScissor({ {(int)pcmd->ClipRect.x, fb_height - (int)(pcmd->ClipRect.w)}, {(int)(pcmd->ClipRect.z), fb_height - (int)(pcmd->ClipRect.y)} });

      mMesh.setCount(pcmd->ElemCount);
      mMesh.setIndexBuffer(mIndexBuffer, idx_buffer_offset * sizeof(ImDrawIdx), sizeof(ImDrawIdx) == 2 ? Mesh::IndexType::UnsignedShort : Mesh::IndexType::UnsignedInt);

      idx_buffer_offset += pcmd->ElemCount;

      mMesh.draw(mShader);
    }
  }

  Renderer::disable(Renderer::Feature::ScissorTest);
}

void MagnumImgui::mousePressEvent(const Platform::Application::MouseEvent& event)
{
  mousePressReleaseEvent(event, true);
}

void MagnumImgui::mouseReleaseEvent(const Platform::Application::MouseEvent& event)
{
  mousePressReleaseEvent(event, false);
}

void MagnumImgui::mouseScrollEvent(const Platform::Application::MouseScrollEvent& event)
{
  mMouseScroll += event.offset().y();
}

void MagnumImgui::mouseMoveEvent(const Platform::Application::MouseMoveEvent& event)
{
  mMousePos = event.position();
}

void MagnumImgui::keyPressEvent(const Platform::Application::KeyEvent& event)
{
  keyPressReleaseEvent(event, true);
}

void MagnumImgui::keyReleaseEvent(const Platform::Application::KeyEvent& event)
{
  keyPressReleaseEvent(event, false);
}

void MagnumImgui::textInputEvent(const Platform::Application::TextInputEvent& event)
{
  ImGuiIO& io = ImGui::GetIO();
  io.AddInputCharactersUTF8(event.text().data());
}

ImguiShader::ImguiShader()
{
  const char *vertex_shader =
    "uniform mat4 ProjMtx;\n"
    "layout(location = 0) in vec2 Position;\n"
    "layout(location = 1) in vec2 UV;\n"
    "layout(location = 2) in vec4 Color;\n"
    "out vec2 Frag_UV;\n"
    "out vec4 Frag_Color;\n"
    "void main()\n"
    "{\n"
    "	Frag_UV = UV;\n"
    "	Frag_Color = Color;\n"
    "	gl_Position = ProjMtx * vec4(Position.xy,0,1);\n"
    "}\n";

  const char* fragment_shader =
    "uniform sampler2D Texture;\n"
    "in vec2 Frag_UV;\n"
    "in vec4 Frag_Color;\n"
    "out vec4 Out_Color;\n"
    "void main()\n"
    "{\n"
    "	Out_Color = Frag_Color * texture( Texture, Frag_UV.st);\n"
    "}\n";

  MAGNUM_ASSERT_VERSION_SUPPORTED(Version::GL330);

  Shader vert{ Version::GL330, Shader::Type::Vertex };
  Shader frag{ Version::GL330, Shader::Type::Fragment };

  vert.addSource({ vertex_shader });
  frag.addSource({ fragment_shader });

  CORRADE_INTERNAL_ASSERT_OUTPUT(Shader::compile({ vert, frag }));

  attachShaders({ vert, frag });

  CORRADE_INTERNAL_ASSERT_OUTPUT(link());

  mProjMatrixUniform = uniformLocation("ProjMtx");

  setUniform(uniformLocation("Texture"), TextureLayer);
}

