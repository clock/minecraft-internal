#include "legit.hpp"
#include <iostream>
#include <Windows.h>
#include "math.hpp"
#include "globals.hpp"

void legit::run() {

	if (globals::minecraft == nullptr)
		return;

	if (globals::world == nullptr)
		return;

	std::shared_ptr<c_entity> local_player = std::make_shared<c_entity>(globals::minecraft->get_local_player());

	if (local_player == nullptr || !local_player.get() || !local_player || !local_player->is_valid())
		return;
	
	std::shared_ptr<c_entity> target = std::make_shared<c_entity>(legit::get_closest_player(local_player.get(), globals::world.get()));

	if (target == nullptr || !target.get() || !target || !target->is_valid())
		return;

	// hello! for anyone reading this comment i currently dont understand too much on aim assist detetction serverside in mc
	// so there will be two versions of aim assist, one that is based on angles and one that is based on mouse movement
	// the mouse movement one will just world to screen and move mouse accordingly not having to worry about any messed up math

	// config system later
	bool used_angle_based = true;

	// angle based aim assist
	if (used_angle_based)
		legit::angle_aimbot(local_player.get(), target.get());
	
	// mouse based aim assist

}

c_entity legit::get_closest_player(c_entity* local_player, c_world* world) {

	if (world == nullptr)
		return c_entity(nullptr);

	if (local_player == nullptr)
		return c_entity(nullptr);

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

		// config system later
		if (dist > 5)
			continue;

		// if the distance is less than the closest distance
		if (dist < closest_dist) {
			// set the closest distance to the distance
			closest_dist = (float)dist;
			// set the closest player to the player
			closest_player = player;
		}

	}

	if (closest_player == nullptr)
		return c_entity(nullptr);

	return *closest_player;
}

void legit::angle_aimbot(c_entity* local_player, c_entity* target) {
	// get the local player's yaw and pitch
	Vector2 local_angles = Vector2(local_player->get_yaw(), local_player->get_pitch());

	Vector3 player_pos = Vector3((float)target->get_x(), (float)target->get_y(), (float)target->get_z());
	Vector3 local_pos = Vector3((float)local_player->get_x(), (float)local_player->get_y() + 3.4f, (float)local_player->get_z());

	Vector2 player_head_pos = math::get_angles(local_pos, Vector3((float)player_pos.x, (float)player_pos.y + 3.4f, (float)player_pos.z));
	Vector2 player_foot_pos = math::get_angles(local_pos, player_pos);

	// get the difference between the local player's yaw and the player's yaw
	Vector2 head_diff = math::wrap_angle_to_180(local_angles.Invert() - player_head_pos.Invert());
	Vector2 foot_diff = math::wrap_angle_to_180(local_angles.Invert() - player_foot_pos.Invert());

	const float smooth = 10;

	float target_yaw = local_angles.x + ((head_diff.x) / smooth);
	float target_pitch = local_angles.y + ((head_diff.y) / smooth);

	// set the local player's yaw and pitch to the target yaw and pitch
	local_player->set_yaw(target_yaw);
	local_player->set_pitch(target_pitch);
}