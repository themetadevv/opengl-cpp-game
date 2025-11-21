#pragma once

#include "Core/Window.h"

namespace Platform::Windows {
	class Window : public Core::IWindow {
	private:
		Core::WindowData m_WindowData;
		GLFWwindow* m_Window;
		bool m_WindowRunning;

		void Initialize();

	public:
		Window(const Core::WindowData& window_data);

		Core::WindowData GetWindowData() const override;
		Core::NativeWindowHandle GetWindowHandle() const override;
		bool Running() const override;

		void OnUpdate(const glm::vec4& clear_color) override;
	};
}