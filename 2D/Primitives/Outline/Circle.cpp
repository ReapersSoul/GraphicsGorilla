#include "Circle.hpp"

namespace GraphicsGorilla
{
  namespace TwoD
  {
	namespace Primitives
	{
	  namespace Outline
	  {
		void DrawCircle(float radius, int segments, float line_thickness, glm::vec2 position, glm::vec4 color)
        {
          glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
          glEnable(GL_BLEND);
          glLineWidth(line_thickness);
          glBegin(GL_LINE_LOOP);
          glColor4f(color.x, color.y, color.z, color.w);
          for (int i = 0; i <= segments; i++)
          {
            float angle = 2.0f * 3.14159f * float(i) / float(segments);
            float x = radius * cosf(angle);
            float y = radius * sinf(angle);
            glVertex2f(position.x + x, position.y + y);
          }
          glEnd();
          glDisable(GL_BLEND);
        }
	  }
	}
  }
}