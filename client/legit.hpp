#pragma once
#include "c_entity.hpp"
#include "c_world.hpp"

namespace legit {
	void run();
	void angle_aimbot(c_entity* local_player, c_entity* target);
	c_entity get_closest_player(c_entity* local_player, c_world* world);
}