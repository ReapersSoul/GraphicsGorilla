#include "Triangle.hpp"

#include "../Filled/Triangle.hpp"
#include "../Outline/Triangle.hpp"

namespace GraphicsGorilla
{
  namespace TwoD
  {
	namespace Primitives
	{
		namespace Rounded{
	  namespace Stroked
	  {
		void DrawTriangle(float base, float height, float radius, float line_thickness, glm::vec2 position, glm::vec4 FillColor, glm::vec4 StrokeColor)
          {
            Rounded::Filled::DrawTriangle(base, height, radius, position, FillColor);
            Rounded::Outline::DrawTriangle(base, height, radius, line_thickness, position, StrokeColor);
          }
	  }
		}
	}
  }
}