#include "GraphicsGorilla.hpp"

namespace GraphicsGorilla
{

  namespace Primitives
  {
    namespace TwoD
    {
      namespace Splines
      {
        void DrawQuadraticBezier(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2, int segments, glm::vec4 color)
        {
          glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
          glEnable(GL_BLEND);
          glBegin(GL_LINE_STRIP);
          glColor4f(color.x, color.y, color.z, color.w);
          for (int i = 0; i <= segments; i++)
          {
            float t = float(i) / float(segments);
            float x = (1.0f - t) * (1.0f - t) * p0.x + 2.0f * (1.0f - t) * t * p1.x + t * t * p2.x;
            float y = (1.0f - t) * (1.0f - t) * p0.y + 2.0f * (1.0f - t) * t * p1.y + t * t * p2.y;
            glVertex2f(x, y);
          }
          glEnd();
          glDisable(GL_BLEND);
        }

        void DrawCubicBezier(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, int segments, glm::vec4 color)
        {
          glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
          glEnable(GL_BLEND);
          glBegin(GL_LINE_STRIP);
          glColor4f(color.x, color.y, color.z, color.w);
          for (int i = 0; i <= segments; i++)
          {
            float t = float(i) / float(segments);
            float x = (1.0f - t) * (1.0f - t) * (1.0f - t) * p0.x + 3.0f * (1.0f - t) * (1.0f - t) * t * p1.x + 3.0f * (1.0f - t) * t * t * p2.x + t * t * t * p3.x;
            float y = (1.0f - t) * (1.0f - t) * (1.0f - t) * p0.y + 3.0f * (1.0f - t) * (1.0f - t) * t * p1.y + 3.0f * (1.0f - t) * t * t * p2.y + t * t * t * p3.y;
            glVertex2f(x, y);
          }
          glEnd();
          glDisable(GL_BLEND);
        }

        void DrawCatmullRomSpline(glm::vec2 p0, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, int segments, glm::vec4 color)
        {
          glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
          glEnable(GL_BLEND);
          glBegin(GL_LINE_STRIP);
          glColor4f(color.x, color.y, color.z, color.w);
          for (int i = 0; i <= segments; i++)
          {
            float t = float(i) / float(segments);
            float x = 0.5f * ((2.0f * p1.x) + (-p0.x + p2.x) * t + (2.0f * p0.x - 5.0f * p1.x + 4.0f * p2.x - p3.x) * t * t + (-p0.x + 3.0f * p1.x - 3.0f * p2.x + p3.x) * t * t * t);
            float y = 0.5f * ((2.0f * p1.y) + (-p0.y + p2.y) * t + (2.0f * p0.y - 5.0f * p1.y + 4.0f * p2.y - p3.y) * t * t + (-p0.y + 3.0f * p1.y - 3.0f * p2.y + p3.y) * t * t * t);
            glVertex2f(x, y);
          }
          glEnd();
          glDisable(GL_BLEND);
        }

        void DrawBezierSpline(std::vector<glm::vec2> points, int segments, glm::vec4 color)
        {
          if (points.size() < 3)
          {
            return;
          }
          glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
          glEnable(GL_BLEND);
          glBegin(GL_LINE_STRIP);
          glColor4f(color.x, color.y, color.z, color.w);
          for (int i = 0; i < points.size() - 2; i += 2)
          {
            for (int i = 0; i <= segments; i++)
            {
              float t = float(i) / float(segments);
              float x = (1.0f - t) * (1.0f - t) * points[i].x + 2.0f * (1.0f - t) * t * points[i + 1].x + t * t * points[i + 2].x;
              float y = (1.0f - t) * (1.0f - t) * points[i].y + 2.0f * (1.0f - t) * t * points[i + 1].y + t * t * points[i + 2].y;
              glVertex2f(x, y);
            }
          }
          glEnd();
          glDisable(GL_BLEND);
        }
      }
    }

    namespace ThreeD
    {
      void DrawPyramid(float base, float height, glm::vec4 position, glm::vec4 color)
      {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glBegin(GL_TRIANGLES);
        glColor4f(color.x, color.y, color.z, color.w);
        // front face
        glVertex3f(position.x, position.y, position.z);
        glVertex3f(position.x + base, position.y, position.z);
        glVertex3f(position.x + base / 2, position.y + height, position.z);
        // left face
        glVertex3f(position.x, position.y, position.z);
        glVertex3f(position.x, position.y, position.z + base);
        glVertex3f(position.x + base / 2, position.y + height, position.z);
        // right face
        glVertex3f(position.x + base, position.y, position.z);
        glVertex3f(position.x + base, position.y, position.z + base);
        glVertex3f(position.x + base / 2, position.y + height, position.z);
        // back face
        glVertex3f(position.x, position.y, position.z + base);
        glVertex3f(position.x + base, position.y, position.z + base);
        glVertex3f(position.x + base / 2, position.y + height, position.z);
        glEnd();
        glDisable(GL_BLEND);
      }

      void DrawRectangularPrism(float width, float height, float depth, glm::vec4 position, glm::vec4 color)
      {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glBegin(GL_QUADS);
        glColor4f(color.x, color.y, color.z, color.w);
        // front face
        glVertex3f(position.x, position.y, position.z);
        glVertex3f(position.x + width, position.y, position.z);
        glVertex3f(position.x + width, position.y + height, position.z);
        glVertex3f(position.x, position.y + height, position.z);
        // back face
        glVertex3f(position.x, position.y, position.z + depth);
        glVertex3f(position.x + width, position.y, position.z + depth);
        glVertex3f(position.x + width, position.y + height, position.z + depth);
        glVertex3f(position.x, position.y + height, position.z + depth);
        // left face
        glVertex3f(position.x, position.y, position.z);
        glVertex3f(position.x, position.y, position.z + depth);
        glVertex3f(position.x, position.y + height, position.z + depth);
        glVertex3f(position.x, position.y + height, position.z);
        // right face
        glVertex3f(position.x + width, position.y, position.z);
        glVertex3f(position.x + width, position.y, position.z + depth);
        glVertex3f(position.x + width, position.y + height, position.z + depth);
        glVertex3f(position.x + width, position.y + height, position.z);
        // top face
        glVertex3f(position.x, position.y + height, position.z);
        glVertex3f(position.x + width, position.y + height, position.z);
        glVertex3f(position.x + width, position.y + height, position.z + depth);
        glVertex3f(position.x, position.y + height, position.z + depth);
        // bottom face
        glVertex3f(position.x, position.y, position.z);
        glVertex3f(position.x + width, position.y, position.z);
        glVertex3f(position.x + width, position.y, position.z + depth);
        glVertex3f(position.x, position.y, position.z + depth);
        glEnd();
        glDisable(GL_BLEND);
      }

      void DrawSphere(float radius, int segments, glm::vec4 position, glm::vec4 color)
      {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(color.x, color.y, color.z, color.w);
        glVertex3f(position.x, position.y, position.z);
        for (int i = 0; i <= segments; i++)
        {
          float theta = 2.0f * 3.14159f * float(i) / float(segments);
          float x = radius * cosf(theta);
          float y = radius * sinf(theta);
          glVertex3f(position.x + x, position.y + y, position.z);
        }
        glEnd();
        glDisable(GL_BLEND);
      }

    }
  }

  
}