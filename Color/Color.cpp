#include "Color.hpp"

namespace GraphicsGorilla
{
	namespace Color
	{
		glm::vec4 Lerp(const glm::vec4 &a, const glm::vec4 &b, float t)
		{
			return a + t * (b - a);
		}

		glm::vec4 Random()
		{
			return Random(1.0f);
		}

		glm::vec4 Random(float alpha)
		{
			float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			return glm::vec4(r, g, b, alpha);
		}

		glm::vec4 RGBAtoHSVA(const glm::vec4 &color)
		{
			float r = color.x;
			float g = color.y;
			float b = color.z;
			float a = color.w;
			float max = std::max(r, std::max(g, b));
			float min = std::min(r, std::min(g, b));
			float h = 0.0f;
			if (max == r)
			{
				h = (g - b) / (max - min);
			}
			else if (max == g)
			{
				h = 2.0f + (b - r) / (max - min);
			}
			else
			{
				h = 4.0f + (r - g) / (max - min);
			}
			h *= 60.0f;
			if (h < 0.0f)
			{
				h += 360.0f;
			}
			float s = (max == 0.0f) ? 0.0f : (1.0f - (min / max));
			return glm::vec4(h, s, max, a);
		}

		glm::vec4 HSVAtoRGBA(const glm::vec4 &color)
		{
			float h = map(color.x, 0.0f, 1.0f, 0.0f, 360.0f);
			float s = color.y;
			float v = color.z;
			float a = color.w;
			float c = v * s;
			float x = c * (1.0f - std::abs(fmod(h / 60.0f, 2.0f) - 1.0f));
			float m = v - c;
			float r = 0.0f;
			float g = 0.0f;
			float b = 0.0f;
			if (h >= 0.0f && h < 60.0f)
			{
				r = c;
				g = x;
				b = 0.0f;
			}
			else if (h >= 60.0f && h < 120.0f)
			{
				r = x;
				g = c;
				b = 0.0f;
			}
			else if (h >= 120.0f && h < 180.0f)
			{
				r = 0.0f;
				g = c;
				b = x;
			}
			else if (h >= 180.0f && h < 240.0f)
			{
				r = 0.0f;
				g = x;
				b = c;
			}
			else if (h >= 240.0f && h < 300.0f)
			{
				r = x;
				g = 0.0f;
				b = c;
			}
			else if (h >= 300.0f && h < 360.0f)
			{
				r = c;
				g = 0.0f;
				b = x;
			}
			return glm::vec4(r + m, g + m, b + m, a);
		}
		glm::vec4 RGBA(float r, float g, float b, float a)
		{
			return glm::vec4(r, g, b, a);
		}
		glm::vec4 HSVA(float h, float s, float v, float a)
		{
			return glm::vec4(h, s, v, a);
		}

		float map(float value, float start1, float stop1, float start2, float stop2)
		{
			return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
		}
	}
}