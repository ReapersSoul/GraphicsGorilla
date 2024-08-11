#include "Triangle.hpp"

namespace GraphicsGorilla
{
  namespace TwoD
  {
    namespace Primitives
    {
      namespace Filled
      {
        void DrawTriangle(float base, float height, glm::vec2 position, glm::vec4 color)
        {
          glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
          glEnable(GL_BLEND);
          glBegin(GL_TRIANGLES);
          glColor4f(color.x, color.y, color.z, color.w);
          glVertex2f(position.x, position.y);
          glVertex2f(position.x + base, position.y);
          glVertex2f(position.x + base / 2, position.y + height);
          glEnd();
          glDisable(GL_BLEND);
        }
      }
    }
  }
}
