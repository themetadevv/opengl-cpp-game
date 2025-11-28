#pragma once

#include "Core/Renderer.h"

namespace Platform::OpenGL {
	class OpenGL_Renderer : public Core::IRenderer {
	private:
		std::unordered_map<std::string, std::unique_ptr<Shader>>               m_Shaders;
		std::unordered_map<std::string, std::unique_ptr<Texture2D>>	           m_Textures2D;
		std::unordered_map<std::string, std::unique_ptr<Buffer::VertexBuffer>> m_VertexBuffers;
		std::unordered_map<std::string, std::unique_ptr<Buffer::IndexBuffer>>  m_IndexBuffers;
		std::unordered_map<std::string, std::unique_ptr<Buffer::VertexArray>>  m_VertexArray;

	public:
		OpenGL_Renderer() {
			Initialize();
		}

		void Initialize() override;
		void Shutdown() override;

		void Clear(const glm::vec4& color) override;
		void DrawIndexed(unsigned int index_count) override;

		void CreateShader(const std::string& shader_name, std::unique_ptr<Shader> shader) override;
		void CreateTexture2D(const std::string& texture_name, std::unique_ptr<Texture2D> texture_2d) override;
		void CreateVAO(const std::string& obj_name, std::unique_ptr<Buffer::VertexArray> vao) override;
		void CreateVBO(const std::string& obj_name, std::unique_ptr<Buffer::VertexBuffer> vbo) override;
		void CreateIBO(const std::string& obj_name, std::unique_ptr<Buffer::IndexBuffer> ibo) override;

		Shader* GetShader(const std::string& shader_name) const override;
		Texture2D* GetTexture2D(const std::string& texture_name) const override;
		Buffer::VertexArray*  GetVAO(const std::string& obj_name) const override;
		Buffer::VertexBuffer* GetVBO(const std::string& obj_name) const override;
		Buffer::IndexBuffer*  GetIBO(const std::string& obj_name) const override;

		inline Core::RenderAPI GetAPI() const override {
			return Core::RenderAPI::OPENGL;
		}
	};
}