#pragma once

// Multi monitor support is not implemented!

namespace Core {
	enum class VideoMode {
		None = -1,
		Windowed,
		Borderless, // still windowed not true full screen (a.k.a Borderless FullScreen / Borderless Window)
		Fullscreen, // true full screen
	};

	enum class WindowState : uint32_t {
		None = -1,
		Maximized = 1 << 0, 
		Minimized = 1 << 1,
		InputFocused = 1 << 2,
	};

	inline WindowState operator|(WindowState state_a, WindowState state_b) {
		return static_cast<WindowState>(
			static_cast<uint32_t>(state_a) | static_cast<uint32_t>(state_b)
		);
	}

	inline WindowState& operator|=(WindowState& state_a, WindowState state_b) {
		state_a = state_a | state_b;
		return state_a;
	}

	inline WindowState operator&(WindowState a, WindowState b) {
		return static_cast<uint32_t>(a) & static_cast<uint32_t>(b) 
			? b : WindowState::None;
	}

	struct WindowSpecification {
	public:
		std::string Title;
		std::pair<int, int> Size = {600, 400};
		bool VSync = false;
		VideoMode VidMode = VideoMode::Windowed;
		WindowState WinState = WindowState::None;
	};

	class Window {
	private: 
		// <------------------ Private Members ------------------>

		// Window Specification
		WindowSpecification m_WindowSpecs;

		// Window Enum
		VideoMode m_CurrentVideoMode;
		WindowState m_CurrentWindowState;

		// Window Pointers
		GLFWwindow* m_WindowHandle;
		GLFWmonitor* m_PrimaryMonitorHandle;

		std::pair<int, int> m_WindowPosition;

		bool m_Initialized;
		bool m_Running;

	public:
		// <------------------ Constructors/Deconstructor ------------------>

		Window(const WindowSpecification& window_specs);
		~Window();

	public:
		// <------------------ Setters ------------------>

		void SetWindowSize(int w, int h);
		void SetWindowVSync(bool val);
		void SetVideoMode(VideoMode vm);
		void SetWindowState(WindowState ws);

		// <------------------ Getters ------------------>

		// Window Specification
		inline std::pair<int, int> GetWindowSize() const { return m_WindowSpecs.Size; }
		inline std::pair<int, int> GetWindowPosition() const { return m_WindowPosition; }

		// Window Enum
		inline VideoMode   GetCurrentVideoMode() const { return m_CurrentVideoMode; }
		inline WindowState GetCurrentWindowState() const { return m_CurrentWindowState; }

		// Window Pointers
		inline GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }

		inline bool Running() const {
			return m_Running;
		}

	public:
		// <------------------ Functions ------------------>

		void Update();
		void Shutdown();
	};
}