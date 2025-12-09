
#include "pch.h"
#include "Core/Core.h"

#include "Sprite.h"

namespace Game {
	Sprite::Sprite(const std::string& name)
	{
		m_SpriteData.Name = name;
	}

	void Sprite::ClearShader() {
		m_SpriteData.SpriteShader = nullptr;
	}

	void Sprite::ClearTexture() {
		m_SpriteData.Texture = nullptr;
	}

	void Sprite::ClearMesh() {
		m_SpriteData.Mesh = nullptr;
	}

	bool Sprite::SetShader(OpenGL::Shader* shader) {
		if (m_SpriteData.SpriteShader != shader) {
			m_SpriteData.SpriteShader = shader;
			return true;
		}
		
		Log("Same Shader was Set Again!");
		return false;
	}

	bool Sprite::SetTexture(OpenGL::Texture2D* texture) {
		if (m_SpriteData.Texture != texture) {
			m_SpriteData.Texture = texture;
			return true;
		}

		Log("Same Texture was Set Again!");
		return false;
	}

	bool Sprite::SetMesh(OpenGL::IMesh* mesh) {
		if (m_SpriteData.Mesh != mesh) {
			m_SpriteData.Mesh = mesh;
			return true;
		}

		Log("Same Mesh was Set Again!");
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

	void Sprite::SetColor(const Color& val) {
		m_SpriteData.SpriteColor = val;
	}

	void Sprite::Draw(OpenGL::Renderer* r) {
		m_SpriteData.SpriteShader->Bind();
		
		bool texture_attached = (m_SpriteData.Texture != nullptr);

		m_SpriteData.SpriteShader->SetUniform1i(ShaderConst::UTEX_ATTACHED, texture_attached);
		m_SpriteData.SpriteShader->SetUniform4f(ShaderConst::UCOLOR, { m_SpriteData.SpriteColor.R, m_SpriteData.SpriteColor.G, m_SpriteData.SpriteColor.B, m_SpriteData.SpriteColor.A });

		Mat4 u_MVP = r->GetProjectionMatrix() * r->GetViewMatrix() * m_SpriteData.Transform.GetModelMatrix();
		m_SpriteData.SpriteShader->SetUniformMat4(ShaderConst::UMVP, u_MVP);

		if (m_SpriteData.Texture != nullptr) {
			m_SpriteData.Texture->OverrideBind(0);
			m_SpriteData.SpriteShader->SetUniform1i(ShaderConst::UTEX, 0);
		}

		if (m_SpriteData.Mesh->GetMeshType() == OpenGL::MeshType::Quad) {
			r->DrawIndexed(
				m_SpriteData.Mesh->GetVAO(),
				m_SpriteData.Mesh->GetIBO()
			);
		}
		else if (m_SpriteData.Mesh->GetMeshType() == OpenGL::MeshType::Triangle) {
			r->DrawArray(m_SpriteData.Mesh->GetVAO());
		}

		m_SpriteData.SpriteShader->Unbind();
	}
}