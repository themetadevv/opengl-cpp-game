#include "pch.h"

#include <glm/glm.hpp>

#include "Core/Window.h"
#include "Platform/Windows/WindowsWindow.h"
#include "Platform/OpenGL/OpenGL_Shader.h"

int main() {
	Core::WindowData m_WindowData;
	m_WindowData.Title = "Platform : Windows, Type : GLFW";
	m_WindowData.Width = 1366;
	m_WindowData.Height = 768;
	m_WindowData.VSync = true;

	std::unique_ptr<Core::IWindow> m_NativeWindow = std::unique_ptr<Core::IWindow>(Core::IWindow::CreateWindow(m_WindowData));

	Platform::OpenGL::Shader shader("TestShader", "C:/shaders/test_shader.glsl");

	while (m_NativeWindow->Running()) {

		m_NativeWindow->OnUpdate(glm::vec4(1.0f, 0.3f, 0.5f, 1.0f));
	}
}