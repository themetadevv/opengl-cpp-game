

#include "pch.h"
#include "Core/Core.h"

#include "Platform/OpenGL/OpenGL_Core.h"

#include "Core/Window.h"

#include "Platform/OpenGL/Buffers/VertexArray.h"
#include "Platform/OpenGL/Buffers/IndexBuffer.h"
#include "Platform/OpenGL/OpenGL_Shader.h"
#include "Platform/OpenGL/OpenGL_Texture.h"


float vertices[] = {
	//   pos.xy        uv.xy
	-0.5f, -0.5f,      0.0f, 0.0f, // bottom-left 0 
	 0.5f, -0.5f,      1.0f, 0.0f, // bottom-right 1
	 0.5f,  0.5f,      1.0f, 1.0f, // top-right 2
	-0.5f,  0.5f,      0.0f, 1.0f  // top-left 3
};

unsigned int indices[]{
	0, 3, 2,
	2, 1, 0
};

int main() {
	using namespace Platform::OpenGL;

	Core::WindowData m_WindowData;
	m_WindowData.Title  = "Platform " + std::string(PLATFORM);
	m_WindowData.VSync  = false;
	m_WindowData.Width  = 1366;
	m_WindowData.Height = 768;

	std::unique_ptr<Core::IWindow> m_Window = std::unique_ptr<Core::IWindow>(Core::IWindow::CreateWindow(m_WindowData));

	Shader test_shader("TestShader", "C:/shaders/test_shader.glsl");
	Texture2D test_texture("TestTexture", "C:/shaders/babee.png");
	Texture2D test_texture_1("TestTexture", "C:/shaders/babee_2.png");

	Buffer::VertexArray VAO;
	VAO.Bind();

	Buffer::VertexBuffer VBO(sizeof(float) * 4 * 4, vertices);
	VBO.Bind();

	Buffer::VertexBufferLayout VBL;
	VBL.Push<float>(2);
	VBL.Push<float>(2);

	VAO.AddDataToBuffer(VBO, VBL);

	Buffer::IndexBuffer IBO(6, indices);

	VAO.Unbind();
	VBO.Unbind();
	IBO.Unbind();

	while (m_Window->Running()) {
		m_Window->ClearScreen({ 0.3f, 0.3f, 0.3f, 1.0f });

		VAO.Bind();
		IBO.Bind();
		test_shader.Bind();

		test_shader.SetUniform1i("u_Texture0", 0);
		test_shader.SetUniform1i("u_Texture1", 1);
		test_shader.SetUniform1f("u_MixAmount", 0.7f);

		test_texture.Bind(0);
		test_texture_1.Bind(1);
		
		GLCall(glDrawElements(GL_TRIANGLES, IBO.GetIndicesCount(), GL_UNSIGNED_INT, nullptr));

		m_Window->OnUpdate();
	}
}