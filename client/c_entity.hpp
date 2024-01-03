#pragma once
#include <string>
#include "java.hpp"

class c_entity {
public:
	c_entity(jobject player_instance);
	~c_entity();
	double get_x();
	double get_y();
	double get_z();

	void cleanup();

	jclass get_class();
private:
	jobject player_instance;
};