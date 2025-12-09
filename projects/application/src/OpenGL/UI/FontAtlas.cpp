
#include "pch.h"

#include "Core/Core.h"

#include "OpenGL/Renderer/Texture2D.h"
#include "OpenGL/Maths.h"

#include "FontAtlas.h"

namespace OpenGL {

	// <------------------ Constructors/Deconstructor ------------------>

	FontAtlas::FontAtlas(const std::string& font_atlas_name, Core::Font* font) :
		m_Name(font_atlas_name), m_Font(font),
		m_AtlasWidth(0), m_AtlasHeight(0)
	{
		UploadAtlasData();
	}

	FontAtlas::~FontAtlas() {
		if(m_GlyphTexture)
			delete m_GlyphTexture;
	}

	// <------------------ Public Functions ------------------>

		// <------------------ Setters ------------------>

	void FontAtlas::SetFont(Core::Font* font) {
		if (m_Font == font)
			return;

		m_Font = font;
	}

	void FontAtlas::UploadAtlasData() {
		struct CharData {
			int Width, Height;
		};

		std::unordered_map<char, CharData> char_sizes;
		int max_height = 0;

		for (unsigned char c = 32; c < 127; c++) {
			if(!m_Font->LoadCharacter(c))
				continue;

			FT_Bitmap& bm = m_Font->GetFace()->glyph->bitmap;
			char_sizes[c] = {
				static_cast<int>(bm.width), static_cast<int>(bm.rows)
			};

			if (static_cast<int>(bm.rows) > max_height)
				max_height = bm.rows;
		}

		int padding = 1;
		int row_width = 0;
		int atlas_width = 0;
		int atlas_height = max_height;

		for (auto& [c, c_size] : char_sizes) {
			if (row_width + c_size.Width + padding > 2048) {
				atlas_height += max_height + padding;
				row_width = 0;
			}

			row_width += c_size.Width + padding;
			if (row_width > atlas_width)
				atlas_width = row_width;
		}

		m_AtlasWidth = atlas_width;
		m_AtlasHeight = atlas_height;

		std::vector<unsigned char> atlas_data(m_AtlasWidth* m_AtlasHeight, 0);

		uint32_t pen_x = 0, pen_y = 0;
		uint32_t row_height = max_height;

		for (unsigned char c = 32; c < 127; c++) {
			if(!m_Font->LoadCharacter(c))
				continue;

			FT_Bitmap& bm = m_Font->GetFace()->glyph->bitmap;

			if (bm.width == 0 || bm.rows == 0)
				continue;

			if (pen_x + bm.width + padding >= m_AtlasWidth) {
				pen_x = 0;
				pen_y += row_height + padding;
			}

			for (int row = 0; row < bm.rows; row++) {
				// Flip vertically by starting from the last row
				int source_row = bm.rows - 1 - row;
				memcpy(&atlas_data[(pen_y + row) * m_AtlasWidth + pen_x],
					&bm.buffer[source_row * bm.width],
					bm.width);
			}

			Glyph g;

			g.Width = bm.width;
			g.Height = bm.rows;
			g.BearingX = m_Font->GetFace()->glyph->bitmap_left;
			g.BearingY = m_Font->GetFace()->glyph->bitmap_top;
			g.Advance = m_Font->GetFace()->glyph->advance.x >> 6;


			g.uvMin = glm::vec2(
				float(pen_x) / float(m_AtlasWidth), 
				float(pen_y) / float(m_AtlasHeight)
			); 
			
			g.uvMax = glm::vec2(
				(float(pen_x + bm.width)) / float(m_AtlasWidth), 
				(float(pen_y + bm.rows)) / float(m_AtlasHeight)
			);


			m_GlyphsCollection[c] = g;
			
			pen_x += bm.width + padding;
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


		OpenGL::TextureData glyph_tex_data;
		glyph_tex_data.Name = "GlyphTex";
		glyph_tex_data.Path = "";
		glyph_tex_data.Width = m_AtlasWidth;
		glyph_tex_data.Height = m_AtlasHeight;
		glyph_tex_data.ImgFormat = ImageFormat::None;
		glyph_tex_data.TexFormat = TextureFormat::R;

		m_GlyphTexture = new OpenGL::Texture2D(glyph_tex_data);
		m_GlyphTexture->UploadTextureData(atlas_data.data(), m_AtlasWidth* m_AtlasHeight);
	}

}