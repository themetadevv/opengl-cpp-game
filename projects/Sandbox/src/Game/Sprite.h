#pragma once

#include "Platform/OpenGL/OpenGL.h"

namespace Game {
	struct SpriteData {
		std::string Name;
		Platform::OpenGL::Shader* Shader;
		Platform::OpenGL::Texture2D* Texture;
		Vector3 Color;
		Transform2D Transform;
		Platform::OpenGL::IMesh* Mesh;
	};

	class Sprite {
	private:
		Platform::OpenGL::Renderer* m_Renderer;
		SpriteData m_SpriteData;

	public:
		Sprite(const std::string& name, Platform::OpenGL::Renderer* renderer);

		bool SetShader(Platform::OpenGL::Shader* shader);
		bool SetTexture(Platform::OpenGL::Texture2D* texture);
		bool SetMesh(Platform::OpenGL::IMesh* mesh);

		void SetSize(const Vector2& size);
		void SetPosition(const Vector2& position);
		void SetRotation(const float& rot);
		
		void SetColor(const Vector3& val);
		void SetMVP(const Mat4& view, const Mat4& projection);

		inline const std::string& GetSpriteName() const {
			return m_SpriteData.Name;
		}

		inline const Platform::OpenGL::Shader* GetBoundShader() const {
			CORE_ASSERT(m_SpriteData.Shader, ("No! Shader was Bound in Sprite -> " + m_SpriteData.Name + "\n").c_str());
			return m_SpriteData.Shader;
		}

		inline const Platform::OpenGL::Texture2D* GetBoundTexture() const {
			CORE_ASSERT(m_SpriteData.Texture, ("No! Texture was Bound in Sprite -> " + m_SpriteData.Name + "\n").c_str());
			return m_SpriteData.Texture;
		}

		inline const Mat4 GetSpriteTransfMatrix() {
			return m_SpriteData.Transform.GetModelMatrix();
		}

		void Draw();
	};
}

