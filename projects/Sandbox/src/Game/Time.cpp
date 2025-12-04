
#include "pch.h"
#include "Core/Core.h"

#include "Time.h"

namespace Game {
	Time::Time() 
		: m_DeltaTime(0.0f), m_ElapsedTime(0.0f)
	{
		m_LastTime = glfwGetTime();
	}

	void Time::Update() {
		double current_time = glfwGetTime();
		m_DeltaTime = current_time - m_LastTime;
		m_LastTime = current_time;
		m_ElapsedTime += m_DeltaTime;

		m_FrameCount++;
		m_FPSTimer += m_DeltaTime;

		if (m_FPSTimer >= 1.0) {
			m_FPS = m_FrameCount;
			m_FrameCount = 0.0;
			m_FPSTimer = 0.0;
		}
	}

}