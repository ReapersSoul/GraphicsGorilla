#include "Rectangle.hpp"

namespace GraphicsGorilla
{
  namespace TwoD
  {
	namespace Primitives
	{
	  namespace Outline
	  {
		void DrawRectangle(float width, float height, float line_thickness, glm::vec2 position, glm::vec4 color)
        {
          glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
          glEnable(GL_BLEND);
          glLineWidth(line_thickness);
          glBegin(GL_LINE_LOOP);
          glColor4f(color.x, color.y, color.z, color.w);
          glVertex2f(position.x, position.y);
          glVertex2f(position.x + width, position.y);
          glVertex2f(position.x + width, position.y + height);
          glVertex2f(position.x, position.y + height);
          glEnd();
          glDisable(GL_BLEND);
        }
	  }
	}
  }
}