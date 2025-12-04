#pragma once

#include "Platform/OpenGL/Buffers/VertexArray.h"
#include "Platform/OpenGL/Buffers/IndexBuffer.h"

namespace Platform::OpenGL {
	enum class MeshType {
		NONE = -1,
		Quad,
		Triangle
	};

	class IMesh {
	public:
		virtual ~IMesh() = default;

		virtual const MeshType& GetMeshType() const = 0;
		virtual Buffer::VertexArray* GetVAO() const = 0;

		virtual Buffer::IndexBuffer* GetIBO() const {
			return nullptr;
		}
	};
}