
#include "pch.h"
#include "Core/Core.h"

#include "Platform/OpenGL/OpenGL_Core.h"

#include "Platform/OpenGL/OpenGL_Shader.h"
#include "Platform/OpenGL/OpenGL_Texture.h"

#include "Platform/OpenGL/Buffers/IndexBuffer.h"
#include "Platform/OpenGL/Buffers/VertexArray.h"
#include "Platform/OpenGL/Buffers/VertexBuffer.h"
#include "Platform/OpenGL/Buffers/VertexBufferLayout.h"

#include "Core/Window.h"

#include "OpenGL_Renderer.h"

namespace Platform::OpenGL {


	void OpenGL_Renderer::Initialize() {

	}

	void OpenGL_Renderer::Shutdown() {
		m_VertexBuffers.clear();
		m_IndexBuffers.clear();
		m_VertexArray.clear();
	}

	void OpenGL_Renderer::Clear(const glm::vec4& color) {
		GLCall(glClearColor(color.x, color.y, color.z, color.w));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
	
	void OpenGL_Renderer::DrawIndexed(unsigned int index_count) {
		glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGL_Renderer::CreateShader(const std::string& shader_name, std::unique_ptr<Shader> shader) {
		if (!m_Shaders.contains(shader_name))
			m_Shaders.emplace(shader_name, std::move(shader));
		else
			std::cout << "Shader : " << shader_name << " Already exists! in Renderer" << "\n";
	}

	void OpenGL_Renderer::CreateTexture2D(const std::string& texture_name, std::unique_ptr<Texture2D> texture_2d) {
		if (!m_Textures2D.contains(texture_name))
			m_Textures2D.emplace(texture_name, std::move(texture_2d));
		else
			std::cout << "Texture2D : " << texture_name << " Already exists! in Renderer" << "\n";
	}

	void OpenGL_Renderer::CreateVAO(const std::string& obj_name, std::unique_ptr<Buffer::VertexArray> vao) {
		if (!m_VertexArray.contains(obj_name))
			m_VertexArray.emplace(obj_name, std::move(vao));
		else
			std::cout << "VAO : " << obj_name << " Already exists! in Renderer" << "\n";
	}

	void OpenGL_Renderer::CreateVBO(const std::string& obj_name, std::unique_ptr<Buffer::VertexBuffer> vbo) {
		if (!m_VertexBuffers.contains(obj_name))
			m_VertexBuffers.emplace(obj_name, std::move(vbo));
		else
			std::cout << "VBO : " << obj_name << " Already exists! in Renderer" << "\n";
	}

	void OpenGL_Renderer::CreateIBO(const std::string& obj_name, std::unique_ptr<Platform::OpenGL::Buffer::IndexBuffer> ibo) {
		if (!m_IndexBuffers.contains(obj_name))
			m_IndexBuffers.emplace(obj_name, std::move(ibo));
		else
			std::cout << "IBO : " << obj_name << " Already exists! in Renderer" << "\n";
	}

	Buffer::VertexArray* OpenGL_Renderer::GetVAO(const std::string& obj_name) const {
		auto it = m_VertexArray.find(obj_name);
		if (it != m_VertexArray.end())
			return it->second.get();

		std::cout << "VAO : " << obj_name << " Not Found! in Renderer\n";
		return nullptr;
	}

	Buffer::VertexBuffer* OpenGL_Renderer::GetVBO(const std::string& obj_name) const {
		auto it = m_VertexBuffers.find(obj_name);
		if (it != m_VertexBuffers.end())
			return it->second.get();

		std::cout << "VBO : " << obj_name << " Not Found! in Renderer\n";
		return nullptr;
	}

	Buffer::IndexBuffer* OpenGL_Renderer::GetIBO(const std::string& obj_name) const {
		auto it = m_IndexBuffers.find(obj_name);
		if (it != m_IndexBuffers.end())
			return it->second.get();

		std::cout << "IBO : " << obj_name << " Not Found! in Renderer\n";
		return nullptr;
	}

	Shader* OpenGL_Renderer::GetShader(const std::string& shader_name) const {
		auto it = m_Shaders.find(shader_name);
		if (it != m_Shaders.end())
			return it->second.get();

		std::cout << "Shader : " << shader_name << " Not Found! in Renderer\n";
		return nullptr;
	}

	Texture2D* OpenGL_Renderer::GetTexture2D(const std::string& texture_name) const {
		auto it = m_Textures2D.find(texture_name);
		if (it != m_Textures2D.end())
			return it->second.get();

		std::cout << "Texture2D : " << texture_name<< " Not Found! in Renderer\n";
		return nullptr;
	}

}
