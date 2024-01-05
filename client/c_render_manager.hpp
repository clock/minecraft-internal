#pragma once
#include <jni.h>
#include "java.hpp"
#include <Windows.h>

class c_render_manager {
public:
	c_render_manager(jobject render_instance);
	jclass get_class();
	void cleanup();

	double get_render_posx();
	double get_render_posy();
	double get_render_posz();
private:
	jobject render_instance;
};