#pragma once

#include "Core/Font.h"

namespace OpenGL {
	struct Glyph {
		Vector2 uvMin;
		Vector2 uvMax;
		uint32_t Width;
		uint32_t Height;
		uint32_t BearingX;
		uint32_t BearingY;
		uint32_t Advance;
	};

	class FontAtlas {
	private:
		// <------------------ Private Members ------------------>

		// FontAtlas Specifications
		std::string m_Name;
		Core::Font* m_Font;
		uint32_t m_AtlasWidth;
		uint32_t m_AtlasHeight;

		OpenGL::Texture2D* m_GlyphTexture;
		std::unordered_map<char, Glyph> m_GlyphsCollection;

	public:
		// <------------------ Constructors/Deconstructor ------------------>

		FontAtlas(const std::string& font_atlas_name, Core::Font* font);
		~FontAtlas();

	public:
		// <------------------ Public Functions ------------------>

		// <------------------ Setters ------------------>

		void SetFont(Core::Font* font);

		// <------------------ Getters ------------------>

		std::string GetAtlasName() const { return m_Name; }
		std::string GetAtlasFontName() const { return m_Font->GetFontName(); }

		const Glyph& GetGlyph(char c) const { return m_GlyphsCollection.at(c); }
		Texture2D* GetGlyphTexture() const { return m_GlyphTexture; }

		uint32_t GetWidth() {
			return m_AtlasWidth;
		}

		uint32_t GetHeight() {
			return m_AtlasHeight;
		}

	private:
		// <------------------ Private Functions ------------------>

		// ts made me cry
		void UploadAtlasData();
	};
}