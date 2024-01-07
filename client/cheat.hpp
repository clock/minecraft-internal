#pragma once
#include "c_minecraft.hpp"
#include "c_world.hpp"
#include "legit.hpp"
#include "visuals.hpp"

inline void run_cheat(std::unique_ptr<c_minecraft> minecraft, std::unique_ptr<c_world> world, std::unique_ptr<c_render_manager> render_manager) {
	
	if (world.get() == nullptr)
		return;

	if (minecraft.get() == nullptr)
		return;

	if (render_manager.get() == nullptr)
		return;

	// get local player as shared_ptr
	std::shared_ptr<c_entity> local_player = std::make_shared<c_entity>(minecraft->get_local_player());
	
	// should get players from world too later

	/*
		later i would like to somehow make it so we only loop through the players once
		that way we can do all the checks in one loop instead of looping through the players every time we want to do a check
	*/

	if (local_player.get() == nullptr)
		return;

	// run legitbot
	Legit::run(local_player.get(), world.get());
	
	// run visuals
	//visuals::run(local_player.get(), world.get(), render_manager.get());

	// run misc
	//misc::run(local_player, std::move(world));
}