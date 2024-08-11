#include "FrameBuffer.hpp"

namespace GraphicsGorilla
{
  void FrameBuffer::DrawToFB(glm::vec4 BackgroundColor, std::function<void()> drawFunction)
  {
    Bind();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearBufferfv(GL_COLOR, 0, glm::value_ptr(BackgroundColor));
    float clear = 1.0f;
    glClearBufferfv(GL_DEPTH, 0, &clear);
    drawFunction();
    glDisable(GL_BLEND);
    Unbind();
  }

  FrameBuffer::FrameBuffer()
  {
    width = 0;
    height = 0;
    ID = -1;
    textureColorBuffer = -1;
    RBO = -1;
  }

  bool FrameBuffer::Init(int width, int height)
  {
    this->width = width;
    this->height = height;
    glGenFramebuffers(1, &ID);
    Bind();

    glGenTextures(1, &textureColorBuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);
    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
      std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
      return false;
    }
    Unbind();
    return true;
  }

  FrameBuffer::~FrameBuffer()
  {
    glDeleteFramebuffers(1, &ID);
    glDeleteTextures(1, &textureColorBuffer);
    glDeleteRenderbuffers(1, &RBO);
  }

  void FrameBuffer::Bind()
  {
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &LastBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
    glViewport(0, 0, width, height);
  }

  void FrameBuffer::Unbind()
  {
    glBindFramebuffer(GL_FRAMEBUFFER, LastBuffer);
  }

  unsigned int FrameBuffer::GetTexture()
  {
    return textureColorBuffer;
  }

  glm::vec2 FrameBuffer::GetSize()
  {
    return glm::vec2(width, height);
  }

  void FrameBuffer::DrawFBToScreen(glm::vec2 position, glm::vec2 size, glm::vec4 tint)
  {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    int lastTexture;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTexture);
    glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
    // draw a quad
    glColor4f(tint.x, tint.y, tint.z, tint.w);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(position.x, position.y);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(position.x + size.x, position.y);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(position.x + size.x, position.y + size.y);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(position.x, position.y + size.y);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, lastTexture);
  }
}