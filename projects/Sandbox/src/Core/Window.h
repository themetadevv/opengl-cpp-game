#pragma once

#include "pch.h"
#include "Core.h"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <glm/glm.hpp>


namespace Core {
	struct WindowData {
	public:
		std::string Title;
		unsigned int Width, Height;
		bool VSync;
	};

	struct NativeWindowHandle {
		enum class Type {
			Win32 = 0,
			GLFW
		};

		Type type;
		void* handle;
	};

	class IWindow {
	public:
		virtual ~IWindow() {}

		virtual WindowData GetWindowData() const = 0;
		virtual NativeWindowHandle GetWindowHandle() const = 0;
		virtual bool Running() const = 0;

		virtual void OnUpdate(const glm::vec4& clear_color) = 0;

		static IWindow* CreateWindow(const WindowData& window_data);
	};
}