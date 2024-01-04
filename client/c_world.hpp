#pragma once
#include <string>
#include <jni.h>
#include "java.hpp"
#include "c_entity.hpp"
#include <vector>

class c_world {
public:
	c_world(jobject world_instance);
	jclass get_class();
	std::vector<std::shared_ptr<c_entity>> get_players();
	void cleanup();
private:
	jobject world_instance;
};