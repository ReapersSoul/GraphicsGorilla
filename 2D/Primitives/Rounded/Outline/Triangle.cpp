#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace GraphicsGorilla
{
  namespace TwoD
  {
    namespace Primitives
    {
      namespace Rounded
      {
        namespace Outline
        {
          void DrawTriangle(float base, float height, float radius, float line_thickness, glm::vec2 position, glm::vec4 color)
          {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glLineWidth(line_thickness);
            glBegin(GL_LINE_LOOP);
            glColor4f(color.x, color.y, color.z, color.w);
            // top left corner
            for (int i = 0; i <= 90; i++)
            {
              float angle = 3.14159f * float(i) / 180.0f;
              float x = radius * cosf(angle);
              float y = radius * sinf(angle);
              glVertex2f(position.x + x, position.y + y + height - radius);
            }
            // top right corner
            for (int i = 90; i <= 180; i++)
            {
              float angle = 3.14159f * float(i) / 180.0f;
              float x = radius * cosf(angle);
              float y = radius * sinf(angle);
              glVertex2f(position.x + base - radius + x, position.y + y + height - radius);
            }
            // bottom corner
            for (int i = 180; i <= 360; i++)
            {
              float angle = 3.14159f * float(i) / 180.0f;
              float x = radius * cosf(angle);
              float y = radius * sinf(angle);
              glVertex2f(position.x + base / 2 + x, position.y + y);
            }
            glEnd();
            glDisable(GL_BLEND);
          }
        }
      }
    }
  }
}