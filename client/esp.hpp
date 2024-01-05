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

namespace esp {
	void run(c_entity* local_player, c_world* world, c_render_manager* render_manager);
}