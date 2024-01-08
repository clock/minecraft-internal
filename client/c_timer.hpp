#pragma once
#include "java.hpp"
#include <string>

class c_timer {
public:
	c_timer(jobject timer_instance);
	jclass get_class();
	float get_render_partial_ticks();
	float get_timer_speed();
	void set_timer_speed(float speed);
private:
	jobject timer_instance;
};