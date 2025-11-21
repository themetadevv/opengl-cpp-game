
#include "pch.h"
#include "Window.h"

#include "Platform/Windows/WindowsWindow.h"

namespace Core {
	IWindow* IWindow::CreateWindow(const WindowData& window_data) {
#ifdef PLATFORM_WINDOWS
		return new Platform::Windows::Window(window_data);
#endif
	}
}