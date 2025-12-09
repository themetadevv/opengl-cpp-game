#pragma once

#include "OpenGL/Buffers/VertexArray.h"
#include "OpenGL/Buffers/VertexBuffer.h"
#include "OpenGL/Buffers/IndexBuffer.h"


namespace OpenGL {
	class Renderer {
	private:
		Mat4 m_ProjectionMatrix;
		Mat4 m_ViewMatrix;

		void Initialize();
		void Shutdown();

		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
			GLCall(glViewport(0, 0, width, height));
		}

	public:
		Renderer();
		~Renderer();

		void SetViewport(GLFWwindow* window_handle) const {
			glfwSetFramebufferSizeCallback(window_handle, FramebufferSizeCallback);
		}

		void SetProjectionMatrix(const Mat4& proj_matrix) {
			m_ProjectionMatrix = proj_matrix;
		}

		void SetViewMatrix(const Mat4& view_matrix) {
			m_ViewMatrix = view_matrix;
		}

		Mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
		Mat4 GetViewMatrix() const { return m_ViewMatrix; }

		void Clear(const glm::vec4& color);

		void DrawArray(Buffer::VertexArray* vao);
		void DrawIndexed(Buffer::VertexArray* vao, Buffer::IndexBuffer* ibo);		

	};
}