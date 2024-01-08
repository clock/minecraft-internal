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

	for (auto player : esp::test_point) {

		ImGui::GetBackgroundDrawList()->AddText(
			ImVec2(player.pos.x, player.pos.y),
			ImColor(255, 255, 255),
			player.value.c_str()
		);
	}
	
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

	c_active_render_info render_info = c_active_render_info();

	std::vector<esp_data> point_buffer;

	float y_offset = 3.4;
	if (local_player->is_sneaking())
		y_offset -= .175;

	auto viewport = render_info.get_viewport();
	ImVec2 screenSize = ImVec2(viewport[2], viewport[3]);

	for (auto player : players) {

		if (player->get_id() == local_player->get_id())
			continue;

		if (player->is_valid() == false)
			continue;

		double x = player->get_x();
		double y = player->get_y();
		double z = player->get_z();

		float player_offset = 3.4;
		if (player->is_sneaking())
			player_offset -= .175;

		// get distance between local player and player
		double dist = sqrt(pow(x - local_player->get_x(), 2) + pow(y - local_player->get_y(), 2) + pow(z - local_player->get_z(), 2));

		if (dist > 35)
			continue;

		// get player name
		std::string name = player->get_name();

		Vector2 p;

		Vector3 render_pos = Vector3(globals::render_manager->get_render_posx(), globals::render_manager->get_render_posy() + y_offset, globals::render_manager->get_render_posz());
		c_world_to_screen::world_to_screen((render_pos) - Vector3(x,y,z), render_info.get_modelview_matrix(), render_info.get_projection_matrix(), (int)screenSize.x, (int)screenSize.y, p);
		
		esp_data data;
		data.pos = p;
		data.value = name;

		point_buffer.push_back(data);
	}

	esp::test_point = point_buffer;
}