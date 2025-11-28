

#include "pch.h"
#include "Core/Core.h"

#include "Platform/OpenGL/OpenGL_Core.h"

#include "Core/Window.h"

#include "Platform/OpenGL/Buffers/VertexArray.h"
#include "Platform/OpenGL/Buffers/IndexBuffer.h"
#include "Platform/OpenGL/OpenGL_Shader.h"
#include "Platform/OpenGL/OpenGL_Texture.h"

#include "Platform/OpenGL/OpenGL_Renderer.h"
#include "Core/Renderer.h"


float vertices[] = {
	//   pos.xy        uv.xy
	-0.5f, -0.5f,      0.0f, 0.0f, // bottom-left 0 
	 0.5f, -0.5f,      1.0f, 0.0f, // bottom-right 1
	 0.5f,  0.5f,      1.0f, 1.0f, // top-right 2
	-0.5f,  0.5f,      0.0f, 1.0f  // top-left 3
};

unsigned int indices[] = {
	0, 3, 2,
	2, 1, 0
};

int main() {
	using namespace Platform::OpenGL;

	std::unique_ptr<Core::IRenderer> m_Renderer = std::unique_ptr<Core::IRenderer>(Core::IRenderer::CreateRenderer());

	Core::WindowData m_WindowData;
	m_WindowData.Title  = "Platform - " + std::string(PLATFORM) + ", API - " + std::string((m_Renderer->GetAPI() == Core::RenderAPI::OPENGL) ? "OpenGL" : "DX11");
	m_WindowData.VSync  = false;
	m_WindowData.Width  = 1366;
	m_WindowData.Height = 768;

	std::unique_ptr<Core::IWindow> m_Window = std::unique_ptr<Core::IWindow>(Core::IWindow::CreateWindow(m_WindowData));
	
	Buffer::VertexBufferLayout QuadVBL;
	QuadVBL.Push<float>(2);
	QuadVBL.Push<float>(2);

	m_Renderer->CreateShader("QuadShader", unique(Shader, "QuadShader", "C:/shaders/test_shader.glsl"));
	auto QuadShader = m_Renderer->GetShader("QuadShader");

	m_Renderer->CreateTexture2D("QuadTexture0", unique(Texture2D, "QuadTexture0", "C:/shaders/babee.png"));
	auto QuadTexture0 = m_Renderer->GetTexture2D("QuadTexture0");

	m_Renderer->CreateTexture2D("QuadTexture1", unique(Texture2D, "QuadTexture1", "C:/shaders/babee_2.png"));
	auto QuadTexture1 = m_Renderer->GetTexture2D("QuadTexture1");

	m_Renderer->CreateTexture2D("QuadTexture2", unique(Texture2D, "QuadTexture2", "C:/shaders/babee_3.png"));
	auto QuadTexture2 = m_Renderer->GetTexture2D("QuadTexture2");

	m_Renderer->CreateVAO("QuadVAO", unique(Buffer::VertexArray));
	auto QuadVAO = m_Renderer->GetVAO("QuadVAO");
	QuadVAO->Bind();

	m_Renderer->CreateVBO("QuadVBO", unique(Buffer::VertexBuffer, sizeof(vertices), vertices));
	auto QuadVBO = m_Renderer->GetVBO("QuadVBO");
	QuadVBO->Bind();

	QuadVAO->AddDataToBuffer(*QuadVBO, QuadVBL);

	m_Renderer->CreateIBO("QuadIBO", unique(Buffer::IndexBuffer, 6u, indices));
	auto QuadIBO = m_Renderer->GetIBO("QuadIBO");

	QuadVAO->Unbind();
	QuadVBO->Unbind();
	QuadIBO->Unbind();

	while (m_Window->Running()) {
		m_Renderer->Clear({ 0.3f, 0.3f, 0.3f, 1.0f });

		QuadVAO->Bind();
		QuadIBO->Bind();

		QuadShader->Bind();

		QuadTexture0->Bind(0);
		QuadShader->SetUniform1i("u_Texture0", 0);

		QuadTexture1->Bind(1);
		QuadShader->SetUniform1i("u_Texture1", 1);

		QuadShader->SetUniform1f("u_MixAmount", 0.7f);

		m_Renderer->DrawIndexed(QuadIBO->GetIndicesCount());

		m_Window->OnUpdate();
	}

	m_Renderer->Shutdown();
}