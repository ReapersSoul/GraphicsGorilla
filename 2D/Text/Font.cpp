#include "Font.hpp"

namespace GraphicsGorrila
{
	namespace TwoD
	{
		namespace Text
		{
			Font::~Font()
			{
				for (auto &pair : characters)
				{
					glDeleteTextures(1, &pair.second.textureID);
				}
				FT_Done_Face(face);
			}

			bool Font::load(const std::string &fontPath, int size)
			{
				FT_Error error = FT_Init_FreeType(&library);
				if (error)
				{
					return false;
				}
				error = FT_New_Face(library, fontPath.c_str(), 0, &face);
				if (error)
				{
					return false;
				}
				error = FT_Set_Pixel_Sizes(face, 0, size);
				if (error)
				{
					return false;
				}
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				for (GLubyte c = 0; c < 128; c++)
				{
					if (FT_Load_Char(face, c, FT_LOAD_RENDER))
					{
						continue;
					}
					GLuint texture;
					glGenTextures(1, &texture);
					glBindTexture(GL_TEXTURE_2D, texture);

					// Create an RGBA buffer from the luminance buffer
					FT_Bitmap &bitmap = face->glyph->bitmap;
					std::vector<GLubyte> rgbaBuffer(bitmap.width * bitmap.rows * 4);
					for (int y = 0; y < bitmap.rows; ++y)
					{
						for (int x = 0; x < bitmap.width; ++x)
						{
							GLubyte luminance = bitmap.buffer[y * bitmap.width + x];
							rgbaBuffer[(y * bitmap.width + x) * 4 + 0] = 255;		// R
							rgbaBuffer[(y * bitmap.width + x) * 4 + 1] = 255;		// G
							rgbaBuffer[(y * bitmap.width + x) * 4 + 2] = 255;		// B
							rgbaBuffer[(y * bitmap.width + x) * 4 + 3] = luminance; // A
						}
					}

					glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.width, bitmap.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaBuffer.data());
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

					Character character = {
						texture,
						bitmap.width,
						bitmap.rows,
						face->glyph->bitmap_left,
						face->glyph->bitmap_top,
						face->glyph->advance.x};
					characters.insert(std::pair<GLchar, Character>(c, character));
				}
				return true;
			}

			void Font::render(const std::string &text, float x, float y, float scale, const glm::vec4 &color)
			{
				glEnable(GL_TEXTURE_2D);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glEnable(GL_BLEND);
				glPushMatrix();
				glTranslatef(x, y, 0);
				glScalef(scale * 0.01, scale * 0.01, 1);
				glColor4f(color.x, color.y, color.z, color.w); // Ensure alpha is set

				for (auto &c : text)
				{
					Character ch = characters[c];
					GLfloat xpos = ch.bearingX * scale;
					GLfloat ypos = ch.bearingY * scale;
					GLfloat w = ch.width * scale;
					GLfloat h = ch.height * scale;
					GLfloat vertices[6][4] = {
						{xpos, ypos - h, 0.0, 0.0},
						{xpos, ypos, 0.0, 1.0},
						{xpos + w, ypos, 1.0, 1.0},
						{xpos, ypos - h, 0.0, 0.0},
						{xpos + w, ypos, 1.0, 1.0},
						{xpos + w, ypos - h, 1.0, 0.0}};
					glBindTexture(GL_TEXTURE_2D, ch.textureID);
					glBegin(GL_TRIANGLES);
					for (int i = 0; i < 6; i++)
					{
						glTexCoord2f(vertices[i][2], 1 - vertices[i][3]);
						glVertex2f(vertices[i][0], vertices[i][1]);
					}
					glEnd();
					glTranslatef((ch.advance >> 6) * scale, 0, 0);
				}
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_BLEND);
				glPopMatrix();
			}
			void Font::setPixelSize(int size)
			{
				FT_Set_Pixel_Sizes(face, 0, size);
			}
		}
	}
}