#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

void GLClearErrors();
const char* GLGetErrorEnumName(GLenum error_code);
bool GLCheckError(const char* func_name, unsigned int func_call_line_no, const char* in_file);

#ifdef ENABLE_DEBUGGING
	#define GLCall(X) GLClearErrors(); X; CORE_ASSERT(GLCheckError(#X, __LINE__, __FILE__)) 
#else
#define GLCall(X) X
#endif