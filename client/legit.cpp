#include "legit.hpp"
#include <iostream>
#include <Windows.h>
#include "math.hpp"
#include "globals.hpp"
#include <cmath>
#include <random>
#include <chrono>
#include "config.hpp"

void legit::run() {

	printf("%i\n", *config::get<bool>("aimbot_enabled"));

	if (!config::get<bool>("aimbot_enabled"))
		return;

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

enum SmoothingMode {
	LINEAR,
	EXPONENTIAL,
	SINUSOIDAL,
	LOGARITHMIC,
	LERP,
	SMOOTHSTEP
};

void legit::angle_aimbot(c_entity* local_player, c_entity* target) {
	// get the local player's yaw and pitch
	Vector2 local_angles = Vector2(local_player->get_yaw(), local_player->get_pitch());

	Vector3 player_pos = Vector3((float)target->get_x(), (float)target->get_y(), (float)target->get_z());
	Vector3 player_prev_pos = Vector3((float)target->get_prev_x(), (float)target->get_prev_y(), (float)target->get_prev_z());
	Vector3 local_pos = Vector3(globals::render_manager->get_render_posx(), globals::render_manager->get_render_posy() + 3.4f, globals::render_manager->get_render_posz());

	float partial_ticks = globals::timer->get_render_partial_ticks();
	Vector3 origin = player_prev_pos + (player_pos - player_prev_pos) * partial_ticks;

	Vector2 player_head_pos = math::get_angles(local_pos, Vector3((float)origin.x, (float)origin.y + 3.4f, (float)origin.z));
	Vector2 player_foot_pos = math::get_angles(local_pos, origin);

	// get the difference between the local player's yaw and the player's yaw
	Vector2 head_diff = math::wrap_angle_to_180(local_angles.Invert() - player_head_pos.Invert());
	Vector2 foot_diff = math::wrap_angle_to_180(local_angles.Invert() - player_foot_pos.Invert());

	SmoothingMode mode = SmoothingMode::LOGARITHMIC;

	const float smooth = 10000000;

	float target_yaw;
	float target_pitch;

	switch (mode) {
		case LINEAR:
			target_yaw = local_angles.x + (head_diff.x / smooth);
			target_pitch = local_angles.y + (head_diff.y / smooth);
			break;
		case EXPONENTIAL:
			target_yaw = local_angles.x + (head_diff.x / pow(smooth, 2));
			target_pitch = local_angles.y + (head_diff.y / pow(smooth, 2));
			break;
		case SINUSOIDAL:
			target_yaw = local_angles.x + sin(math::pi / 2 * (head_diff.x / 180)) * smooth;
			target_pitch = local_angles.y + sin(math::pi / 2 * (head_diff.y / 180)) * smooth;
			break;
		case LOGARITHMIC:
			auto sign = [](auto val) {
				return (val > 0) - (val < 0);
				};
			target_yaw = local_angles.x + (log(1 + abs(head_diff.x)) * sign(head_diff.x) / log(smooth + 1));
			target_pitch = local_angles.y + (log(1 + abs(head_diff.y)) * sign(head_diff.y) / log(smooth + 1));
			break;
		case LERP:
		{
			auto lerp = [](float start, float end, float t) {
				return start + t * (end - start);
				};
			target_yaw = lerp(local_angles.x, local_angles.x + head_diff.x, 1 / smooth);
			target_pitch = lerp(local_angles.y, local_angles.y + head_diff.y, 1 / smooth);
		}
		break;
		case SMOOTHSTEP:
		{
			auto smoothstep = [](float edge0, float edge1, float x) {
				x = std::clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
				return x * x * (3 - 2 * x);
				};
			target_yaw = local_angles.x + smoothstep(0, 1, 1 / smooth) * head_diff.x;
			target_pitch = local_angles.y + smoothstep(0, 1, 1 / smooth) * head_diff.y;
		}
		break;
		default:
			target_yaw = local_angles.x + (head_diff.x / smooth);
			target_pitch = local_angles.y + (head_diff.y / smooth);
			break;
	}

	// set the local player's yaw and pitch to the target yaw and pitch
	local_player->set_yaw(target_yaw);
	local_player->set_pitch(target_pitch);
}