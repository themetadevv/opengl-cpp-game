
#include "pch.h"
#include "Core/Core.h"

#include "OpenGL/OpenGL.h"

#include "OpenGL/UI/FontAtlas.h"

#include "Text.h"

namespace OpenGL::Objects::UI {

	TextRenderer::TextRenderer(const TextRendererData& text_renderer_data, Renderer* renderer) :
		m_TextRendererData(text_renderer_data), m_Renderer(renderer)
	{
		constexpr size_t MAX_CHARACTERS = 1024;
		m_VAO = unique(Buffer::VertexArray);
		m_VBO = unique(Buffer::VertexBuffer, sizeof(TextVertex) * MAX_CHARACTERS * 6, nullptr);
	

		m_VAO->Bind();
		
		vbl.Push<float>(2); // position
		vbl.Push<float>(2); // tex_coords
		m_VAO->AddDataToBuffer(*m_VBO, vbl);
		m_VAO->Unbind();
		m_VBO->Unbind();
	}

	TextRenderer::~TextRenderer() {

	}

	bool TextRenderer::SetFontAtlas(FontAtlas* font_atlas) {
		if (m_TextRendererData.TextFontAtlas != font_atlas) {
			if (font_atlas == nullptr) {
				Log("FontAtlas* Set was null! shader name : ");
				return false;
			}

			m_TextRendererData.TextFontAtlas = font_atlas;
		}

		return true;
	}

	bool TextRenderer::SetShader(Shader* shader) {
		if (m_TextRendererData.TextShader != shader) {
			if (shader == nullptr) {
				Log("Shader* Set was null! shader name : ");
				return false;
			}
			
			m_TextRendererData.TextShader = shader;
		}

		return true;
	}

	bool TextRenderer::DrawText(const std::string& text /*= "SampleText"*/, std::pair<float , float> position, float scale, const Color& text_color) {
		if (m_TextRendererData.TextShader == nullptr) {
			Log("Text Shader* is null");
			return false;
		}

		m_TextRendererData.TextShader->Bind();
		m_TextRendererData.TextShader->SetUniform4f(ShaderConst::UCOLOR, { text_color.R, text_color.G, text_color.B, text_color.A });
		m_TextRendererData.TextShader->SetUniformMat4("u_Projection", m_Renderer->GetProjectionMatrix());
		m_TextRendererData.TextShader->SetUniform1i("text", 0);

		std::vector<TextVertex> text_vertices;
		for (unsigned char c : text) {
			const Glyph& g = m_TextRendererData.TextFontAtlas->GetGlyph(c);

			float xpos = (position.first + g.BearingX) * scale;
			float ypos = (position.second - (g.Height - g.BearingY)) * scale;
			float w = g.Width * scale;
			float h = g.Height * scale;

			text_vertices.push_back({ {xpos,     ypos + h}, {g.uvMin.x, g.uvMax.y} });
			text_vertices.push_back({ {xpos,     ypos    }, {g.uvMin.x, g.uvMin.y} });
			text_vertices.push_back({ {xpos + w, ypos    }, {g.uvMax.x, g.uvMin.y} });
			
			text_vertices.push_back({ {xpos,     ypos + h}, {g.uvMin.x, g.uvMax.y} });
			text_vertices.push_back({ {xpos + w, ypos    }, {g.uvMax.x, g.uvMin.y} });
			text_vertices.push_back({ {xpos + w, ypos + h}, {g.uvMax.x, g.uvMax.y} });		

			position.first += g.Advance * scale;
		}

		m_TextRendererData.TextFontAtlas->GetGlyphTexture()->OverrideBind(0);
		m_VAO->Bind();
		m_VBO->Bind();
		m_VBO->UpdateBufferData(text_vertices.size() * sizeof(TextVertex), text_vertices.data());

		GLCall(glDrawArrays(GL_TRIANGLES, 0, text_vertices.size()));

		m_VBO->Unbind();
		m_VAO->Unbind();

		m_TextRendererData.TextShader->Unbind();
		return true;
	}

}