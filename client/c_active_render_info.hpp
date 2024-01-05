#pragma once
#include <jni.h>
#include "java.hpp"
#include <Windows.h>
#include <gl/GL.h>

class c_active_render_info {
public:
	c_active_render_info();
	jclass get_class();
	void cleanup();

	std::unique_ptr<GLint[]> get_viewport();
	std::unique_ptr<GLfloat[]> get_modelview_matrix();
	std::unique_ptr<GLfloat[]> get_projection_matrix();
};