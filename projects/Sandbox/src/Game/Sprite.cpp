
#include "pch.h"
#include "Core/Core.h"

#include "Sprite.h"

namespace Game {
	Sprite::Sprite(const std::string& name, Platform::OpenGL::Renderer* renderer) :
		m_Renderer(renderer)
	{
		m_SpriteData.Name = name;
		m_SpriteData.Shader = nullptr;
		m_SpriteData.Texture = nullptr;
		m_SpriteData.Color = Vector3(1.0f);
		m_SpriteData.Mesh = nullptr;
	}

	bool Sprite::SetShader(Platform::OpenGL::Shader* shader) {
		if (m_SpriteData.Shader != shader) {
			m_SpriteData.Shader = shader;
			return true;
		}
		
		std::cout << "Same Shader was Set Again!\n";
		return false;
	}

	bool Sprite::SetTexture(Platform::OpenGL::Texture2D* texture) {
		if (m_SpriteData.Texture != texture) {
			m_SpriteData.Texture = texture;
			return true;
		}

		std::cout << "Same Texture was Set Again!\n";
		return false;
	}

	bool Sprite::SetMesh(Platform::OpenGL::IMesh* mesh) {
		if (m_SpriteData.Mesh != mesh) {
			m_SpriteData.Mesh = mesh;
			return true;
		}

		std::cout << "Same Mesh was Set Again!\n";
		return false;
	}

	void Sprite::SetSize(const Vector2& size) {
		m_SpriteData.Transform.Size = size;
	}

	void Sprite::SetPosition(const Vector2& position) {
		m_SpriteData.Transform.Position = position;
	}

	void Sprite::SetRotation(const float& rot) {
		m_SpriteData.Transform.Rotation = rot;
	}

	void Sprite::SetColor(const Vector3& val) {
		m_SpriteData.Color = val;
	}

	void Sprite::SetMVP(const Mat4& view, const Mat4& projection) {
		m_SpriteData.Shader->Bind();
		Mat4 u_MVP = projection * view * m_SpriteData.Transform.GetModelMatrix();
		m_SpriteData.Shader->SetUniformMat4(ShaderConst::UMVP, u_MVP);
		m_SpriteData.Shader->Unbind();
	}

	void Sprite::Draw() {
		m_SpriteData.Shader->Bind();
		
		bool texture_attached = (m_SpriteData.Texture != nullptr);

		m_SpriteData.Shader->SetUniform1i(ShaderConst::UTEX_ATTACHED, texture_attached);
		m_SpriteData.Shader->SetUniform4f(ShaderConst::UCOLOR, { m_SpriteData.Color, 1.0f });

		if (m_SpriteData.Texture != nullptr) {
			m_SpriteData.Texture->Bind(0);
			m_SpriteData.Shader->SetUniform1i(ShaderConst::UTEX, 0);
		}

		if (m_SpriteData.Mesh->GetMeshType() == Platform::OpenGL::MeshType::Quad) {
			m_Renderer->DrawIndexed(
				m_SpriteData.Mesh->GetVAO(),
				m_SpriteData.Mesh->GetIBO()
			);
		}
		else if (m_SpriteData.Mesh->GetMeshType() == Platform::OpenGL::MeshType::Triangle) {
			m_Renderer->DrawArray(m_SpriteData.Mesh->GetVAO());
		}
	}
}