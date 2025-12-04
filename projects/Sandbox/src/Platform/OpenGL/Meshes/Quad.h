#pragma once

#include "Platform/OpenGL/Renderer/Mesh.h"

namespace Platform::OpenGL::Mesh {
	class Quad : public IMesh {
	private:
		MeshType m_MeshType;
		std::unique_ptr<Buffer::VertexArray>  m_VAO;
		std::unique_ptr<Buffer::VertexBuffer> m_VBO;
		std::unique_ptr<Buffer::IndexBuffer>  m_IBO;

	public:
		Quad();

		inline const MeshType& GetMeshType() const override {
			return m_MeshType;
		}

		inline Buffer::VertexArray* GetVAO() const override {
			return m_VAO.get();
		}

		inline Buffer::IndexBuffer* GetIBO() const override {
			return m_IBO.get();
		}
	};
}