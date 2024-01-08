#include "esp.hpp"
#include <iostream>
#include "world_to_screen.h"
#include "globals.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"

void esp::draw() {
	
	if (globals::minecraft == nullptr)
		return;

	if (globals::world == nullptr)
		return;

	if (globals::render_manager == nullptr)
		return;

	ImGui::GetBackgroundDrawList()->AddText(
		ImVec2(esp::test_point.pos.x, esp::test_point.pos.y),
		ImColor(255, 255, 255),
		"hi!"
	);
	
	return;
}

void esp::update_data() {
	if (globals::minecraft == nullptr)
		return;

	if (globals::world == nullptr)
		return;

	if (globals::render_manager == nullptr)
		return;

	std::shared_ptr<c_entity> local_player = std::make_shared<c_entity>(globals::minecraft->get_local_player());

	if (local_player == nullptr || !local_player.get() || !local_player || !local_player->is_valid())
		return;

	auto players = globals::world->get_players();

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

	c_active_render_info render_info = c_active_render_info();

	Vector2 p;

	auto viewport = render_info.get_viewport();
	
	ImVec2 screenSize = ImVec2(viewport[2], viewport[3]);



	c_world_to_screen::world_to_screen(Vector3(closest_player->get_x(), closest_player->get_y(), closest_player->get_z()) - Vector3(local_player->get_x(), local_player->get_y(), local_player->get_z()), render_info.get_modelview_matrix(), render_info.get_projection_matrix(), (int)screenSize.x, (int)screenSize.y, p);

	esp::test_point.pos = p;

	//printf("%f : %f\n", esp::test_point.pos.x, esp::test_point.pos.y);

	printf("%f %f %f\n", globals::render_manager->get_render_posx(), globals::render_manager->get_render_posy(), globals::render_manager->get_render_posz());
}