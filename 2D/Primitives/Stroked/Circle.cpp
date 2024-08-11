#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../Filled/Circle.hpp"
#include "../Outline/Circle.hpp"

namespace GraphicsGorilla
{
  namespace TwoD
  {
	namespace Primitives
	{
	  namespace Stroked
	  {
		void DrawCircle(float radius, int segments, float line_thickness, glm::vec2 position, glm::vec4 FillColor, glm::vec4 StrokeColor)
        {
          Filled::DrawCircle(radius, segments, position, FillColor);
          Outline::DrawCircle(radius, segments, line_thickness, position, StrokeColor);
        }
	  }
	}
  }
}