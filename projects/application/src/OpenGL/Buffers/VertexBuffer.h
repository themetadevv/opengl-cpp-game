#pragma once


namespace OpenGL::Buffer {
	class VertexBuffer {
	private:
		unsigned int m_RendererID;
		unsigned int m_BufferUsage;

	public:
		VertexBuffer(unsigned int size, const void* data);
		~VertexBuffer();

		void UpdateBufferData(unsigned int size, const void* data) const;
		void SetBufferUsage(unsigned int usage);

		void Bind() const;
		void Unbind() const;
	};
}