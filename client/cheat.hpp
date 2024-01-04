#pragma
#include "c_minecraft.hpp"
#include "c_world.hpp"
#include "legit.hpp"

inline void run_cheat(std::unique_ptr<c_minecraft> minecraft, std::unique_ptr<c_world> world) {
	
	// get local player as shared_ptr
	std::shared_ptr<c_entity> local_player = std::make_shared<c_entity>(minecraft->get_local_player());
	
	/*
		later i would like to somehow make it so we only loop through the players once
		that way we can do all the checks in one loop instead of looping through the players every time we want to do a check
	*/

	// run legit
	Legit::run(local_player, std::move(world));

	// run visuals
	// visuals::run(local_player, std::move(world));

	// run misc
	// misc::run(local_player, std::move(world));
}