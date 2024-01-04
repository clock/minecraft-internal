#pragma once
#include <string>
#include "java.hpp"
#include <string>

class c_entity {
public:
	c_entity(jobject player_instance);
	double get_x();
	double get_y();
	double get_z();
	int get_id();
	bool is_valid();
	bool is_dead();
	std::string get_name();

	void cleanup();

	jclass get_class();
private:
	jobject player_instance;
};