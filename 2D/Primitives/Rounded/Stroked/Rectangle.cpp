#include "Rectangle.hpp"
#include "../Filled/Rectangle.hpp"
#include "../Outline/Rectangle.hpp"

namespace GraphicsGorilla
{
	namespace TwoD
	{
		namespace Primitives
		{
			namespace Rounded
			{
			namespace Stroked
			{
				void DrawRectangle(float width, float height, float radius, float line_thickness, glm::vec2 position, glm::vec4 FillColor, glm::vec4 StrokeColor)
				{
					Rounded::Filled::DrawRectangle(width, height, radius, position, FillColor);
					Rounded::Outline::DrawRectangle(width, height, radius, line_thickness, position, StrokeColor);
				}
			}
			}
		}
	}
}