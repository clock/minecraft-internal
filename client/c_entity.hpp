#pragma once
#include <string>
#include "java.hpp"

class c_entity {
public:
	c_entity(jobject player_instance);
	float get_x();
	float get_y();
	float get_z();

	// idk
	void cleanup();
private:
	jobject player_instance;
};