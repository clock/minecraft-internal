#pragma once
#include "java.hpp"
#include <jni.h>
#include <Windows.h>
#include <gl/GL.h>
#include "c_entity.hpp"
#include "c_world.hpp"
#include "c_active_render_info.hpp"
#include "c_render_manager.hpp"
#include "geometry.h"

struct esp_data {
	Vector2 pos;
	std::string value;
};

namespace esp {
	inline esp_data test_point;
	void update_data();
	void draw();
}