#pragma once

namespace Game {
	class Time {
	private:
		double m_LastTime;
		double m_DeltaTime;
		double m_ElapsedTime;

		double m_FPS;
		double m_FrameCount;
		double m_FPSTimer;

	public:
		Time(const Time&) = delete;
		Time& operator=(const Time&) = delete;

		Time();

		void Update();

		inline const float& GetDeltaTime() const {
			return static_cast<float>(m_DeltaTime);
		}

		inline const float& GetElapsedTime() const {
			return static_cast<float>(m_ElapsedTime);
		}

		inline const float& GetFPS() const {
			return static_cast<float>(m_FPS);
		}

		static Time& GetTime() {
			static Time static_time_instance;
			return static_time_instance;
		}
	};
}