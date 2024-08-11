#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../Filled/Rectangle.hpp"
#include "../Outline/Rectangle.hpp"

namespace GraphicsGorilla
{
  namespace TwoD
  {
	namespace Primitives
	{
	  namespace Stroked
	  {
		void DrawRectangle(float width, float height, float line_thickness, glm::vec2 position, glm::vec4 FillColor, glm::vec4 StrokeColor)
        {
          Filled::DrawRectangle(width, height, position, FillColor);
          Outline::DrawRectangle(width, height, line_thickness, position, StrokeColor);
        }
	  }
	}
  }
}