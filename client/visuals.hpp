#pragma once
#include <string>
#include "c_entity.hpp"
#include "c_world.hpp"
#include "c_render_manager.hpp"

namespace visuals {
	void run(c_entity* local_player, c_world* world, c_render_manager* render_manager);
}