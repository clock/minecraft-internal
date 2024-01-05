#include "esp.hpp"
#include <iostream>
#include "world_to_screen.h"

void esp::run(c_entity* local_player, c_world* world, c_render_manager* render_manager) {

	// make active render info
	auto active_render_info = c_active_render_info();

	// get the viewport
	auto viewport = active_render_info.get_viewport();

	// get the projection matrix
	auto projection_matrix = active_render_info.get_projection_matrix();

	// get the modelview matrix
	auto modelview_matrix = active_render_info.get_modelview_matrix();

	// render position
	float pos_x = (float)render_manager->get_render_posx();
	float pos_y = (float)render_manager->get_render_posy();
	float pos_z = (float)render_manager->get_render_posz();

	// get list of players
	auto players = world->get_players();

	//// loop through players
	//for (auto player : players) {

	//	if (player->get_id() == local_player->get_id())
	//		continue;

	//	Vector2 screen_pos;

	//	// get player position
	//	Vector3 player_pos = Vector3(player->get_x(), player->get_y(), player->get_z());

	//	// get player screen position
	//	if (!c_world_to_screen::world_to_screen(player_pos, screen_pos, modelview_matrix.get(), projection_matrix.get(), viewport.get())) {
	//		continue;
	//	}

	//	// get player name
	//	std::string player_name = player->get_name();

	//	std::cout << player_name << ": " << screen_pos.x << ", " << screen_pos.y << "\n";

	//	break;
	//}


	float closest_dist = 9999;
	std::shared_ptr<c_entity> closest_player = nullptr;

	for (auto player : players) {

		if (player->get_id() == local_player->get_id())
			continue;

		if (player->is_valid() == false)
			continue;

		double x = player->get_x();
		double y = player->get_y();
		double z = player->get_z();

		// get distance between local player and player
		float dist = sqrt(pow(x - local_player->get_x(), 2) + pow(y - local_player->get_y(), 2) + pow(z - local_player->get_z(), 2));

		// if the distance is less than the closest distance
		if (dist < closest_dist) {
			// set the closest distance to the distance
			closest_dist = dist;
			// set the closest player to the player
			closest_player = player;
		}

	}

	if (closest_player == nullptr)
		return;

	Vector2 screen_pos;

	// get player position
	Vector3 player_pos = Vector3(closest_player->get_x(), closest_player->get_y(), closest_player->get_z());

	// get player screen position
	c_world_to_screen::world_to_screen(player_pos, screen_pos, modelview_matrix.get(), projection_matrix.get(), viewport.get());

	// get player name
	std::string player_name = closest_player->get_name();

	std::cout << player_name << ": " << screen_pos.x << ", " << screen_pos.y << "\n";

	return;
}