
#include "pch.h"
#include "Core/Core.h"

#include "VertexBuffer.h"

#include "OpenGL/OpenGL_Core.h"

namespace OpenGL::Buffer {

	VertexBuffer::VertexBuffer(unsigned int size, const void* data) 
		: m_RendererID(0), m_BufferUsage(GL_DYNAMIC_DRAW)
	{
		GLCall(glGenBuffers(1, &m_RendererID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, m_BufferUsage));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, NULL));
	}

	VertexBuffer::~VertexBuffer() {
		GLCall(glDeleteBuffers(1, &m_RendererID));
	}

	void VertexBuffer::UpdateBufferData(unsigned int size, const void* data) const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void VertexBuffer::SetBufferUsage(unsigned int usage) {
		if (m_BufferUsage == usage)
			return;

		m_BufferUsage = usage;
	}

	void VertexBuffer::Bind() const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	}

	void VertexBuffer::Unbind() const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, NULL));
	}
}