#pragma once

#include <free_type.h>

// too basic font system

namespace Core {
	struct FontSpecification {
		std::string Name;
		std::string Path;

		int Size = 10;
		int FaceIndex = 0;
	};

	enum class FontStyle {
		None = -1,
		Regular,
		Bold,
		Italic
	};

	class Font {
	private:
		// <------------------ Private Members ------------------>

		FontSpecification m_FontSpecification;
		FontStyle m_CurrentFontStyle;

		FT_Library m_FTLibrary;
		FT_Face m_Face;

	public:
		// <------------------ Constructors/Deconstructor ------------------>

		Font(const FontSpecification& font_spec);
		~Font();

	private:
		// <------------------ Private Functions ------------------>

		bool LoadFont();

	public:
		// <------------------ Public Functions ------------------>

		bool LoadCharacter(unsigned char c);

		// <------------------ Setters ------------------>

		void SetFontSize(int size);
		void SetFaceIndex(int index = 0);
		

		// <------------------ Getters ------------------>

		FT_Library GetLibrary() {
			return m_FTLibrary;
		}

		std::string GetFontName() const { return m_FontSpecification.Name; }
		std::string GetFontPath() const { return m_FontSpecification.Path; }
		FT_Face& GetFace() { return m_Face; }

		int GetFontSize() const { return m_FontSpecification.Size; }
		
	};
}