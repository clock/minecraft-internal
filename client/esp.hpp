#pragma once
#include "java.hpp"
#include <jni.h>
#include <Windows.h>
#include <gl/GL.h>
#include "c_entity.hpp"
#include "c_world.hpp"
#include "c_active_render_info.hpp"
#include "common.hpp"
#include "c_render_manager.hpp"
#include "geometry.h"

struct Data {
	Vector2 pos;
	std::string value;
};

namespace esp {
	inline Data test_point;
	void update_date();
	void run();
}