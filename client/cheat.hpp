#pragma once
#include "c_minecraft.hpp"
#include "c_world.hpp"
#include "legit.hpp"
#include "globals.hpp"
#include "esp.hpp"
#include "misc.hpp"

inline void run_cheat() {
	
	if (globals::world.get() == nullptr)
		return;

	if (globals::minecraft.get() == nullptr)
		return;

	if (globals::render_manager.get() == nullptr)
		return;

	// get local player as shared_ptr
	//std::shared_ptr<c_entity> local_player = std::make_shared<c_entity>(globals::minecraft->get_local_player());
	
	// should get players from world too later

	/*
		later i would like to somehow make it so we only loop through the players once
		that way we can do all the checks in one loop instead of looping through the players every time we want to do a check
	*/

	//if (local_player.get() == nullptr)
		//return;

	// run legitbot
	//Legit::run(local_player.get(), globals::world.get());
	
	// run visuals
	esp::update_data();

	// run misc
	misc::update_data();
}