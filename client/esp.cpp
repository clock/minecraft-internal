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

		esp::box(player.box);

	}
	
	return;
}

void esp::box(box_t box) {
	
	if (globals::minecraft == nullptr)
		return;

	if (globals::world == nullptr)
		return;

	if (globals::render_manager == nullptr)
		return;

	ImGui::GetBackgroundDrawList()->AddRect(
		ImVec2(box.x, box.y),
		ImVec2(box.x + box.w, box.y + box.h),
		ImColor(255, 255, 255)
	);

	// cool outer online only
	ImGui::GetBackgroundDrawList()->AddRect(
		ImVec2(box.x - 1, box.y - 1),
		ImVec2(box.x + box.w + 1, box.y + box.h + 1),
		ImColor(0, 0, 0, 180)
	);

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

	if (render_info.get_class() == nullptr)
		return;

	std::vector<esp_data> point_buffer;

	for (auto player : players) {

		if (player->get_id() == local_player->get_id())
			continue;

		if (player->is_valid() == false)
			continue;

		std::string player_name = player->get_name();

		esp_data data;
		box_t box;
		esp::compute_box(player, local_player, render_info, box);
		data.value = player_name;
		data.box = box;

		point_buffer.push_back(data);
	}

	esp::test_point = point_buffer;
}

bool esp::compute_box(std::shared_ptr<c_entity> player, std::shared_ptr<c_entity> local_player, c_active_render_info render_info, box_t& bbox) {

	auto viewport = render_info.get_viewport();
	ImVec2 screenSize = ImVec2(viewport[2], viewport[3]);

	double x = player->get_x();
	double y = player->get_y();
	double z = player->get_z();

	double dist = sqrt(pow(x - local_player->get_x(), 2) + pow(y - local_player->get_y(), 2) + pow(z - local_player->get_z(), 2));

	if (dist > esp::max_distance)
		return false;

	float player_offset = 2.25;
	if (player->is_sneaking())
		player_offset -= .175;

	float local_player_offset = 3.4;
	if (local_player->is_sneaking())
		local_player_offset -= .175;

	Vector2 bottom;

	Vector3 render_pos = Vector3(globals::render_manager->get_render_posx(), globals::render_manager->get_render_posy() + local_player_offset, globals::render_manager->get_render_posz());
	if (!c_world_to_screen::world_to_screen((render_pos)-Vector3(x, y, z), render_info.get_modelview_matrix(), render_info.get_projection_matrix(), (int)screenSize.x, (int)screenSize.y, bottom))
		return false;

	Vector2 top;

	y += player_offset;
	if (!c_world_to_screen::world_to_screen((render_pos)-Vector3(x, y, z), render_info.get_modelview_matrix(), render_info.get_projection_matrix(), (int)screenSize.x, (int)screenSize.y, top))
		return false;

	bbox.x = int(top.x - ((bottom.y - top.y) / 2) / 2);
	bbox.y = int(top.y);

	bbox.w = int((bottom.y - top.y) / 2);
	bbox.h = int(bottom.y - top.y);

	return true;
}