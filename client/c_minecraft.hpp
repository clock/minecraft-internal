#pragma once
#include <string>
#include <unordered_map>
#include <jni.h>
#include "c_entity.hpp"
#include "c_world.hpp"
#include "c_render_manager.hpp"

class c_minecraft {
public:
	jclass get_class();
	jobject get_instance();
	c_entity get_local_player();
	c_world get_world();
	c_render_manager get_render_manager();
};

