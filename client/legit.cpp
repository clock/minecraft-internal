#include "legit.hpp"
#include <iostream>
#include <Windows.h>

void Legit::run(c_entity* local_player, c_world* world) {

	if (local_player == nullptr)
		return;
	
	auto players = world->get_players();

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
		double dist = sqrt(pow(x - local_player->get_x(), 2) + pow(y - local_player->get_y(), 2) + pow(z - local_player->get_z(), 2));

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

	printf("closest player: %s %f\\%f\\%f\n", closest_player->get_name().c_str(), closest_player->get_x(), closest_player->get_y(), closest_player->get_z());
	

}