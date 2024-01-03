#pragma once
#include <string>
#include <unordered_map>
#include <jni.h>
#include "c_entity.hpp"

class c_minecraft {
public:
	jclass get_class();
	jobject get_instance();
	c_entity get_local_player();
};