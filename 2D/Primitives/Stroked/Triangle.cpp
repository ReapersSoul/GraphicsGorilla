#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../Filled/Triangle.hpp"
#include "../Outline/Triangle.hpp"

namespace GraphicsGorilla
{
  namespace TwoD
  {
	namespace Primitives
	{
	  namespace Stroked
	  {
		void DrawTriangle(float base, float height, float line_thickness, glm::vec2 position, glm::vec4 FillColor, glm::vec4 StrokeColor)
        {
          Filled::DrawTriangle(base, height, position, FillColor);
          Outline::DrawTriangle(base, height, line_thickness, position, StrokeColor);
        }
	  }
	}
  }
}