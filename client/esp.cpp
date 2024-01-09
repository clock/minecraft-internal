#include "esp.hpp"
#include <iostream>
#include "world_to_screen.h"
#include "globals.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"
#include <algorithm>
#include "renderer.hpp"

void esp::draw() {
	
	if (globals::minecraft == nullptr)
		return;

	if (globals::world == nullptr)
		return;

	if (globals::render_manager == nullptr)
		return;

	for (auto data : esp::entity_points) {

		esp::box(data);
		esp::name(data);
		esp::health(data);

	}

	if (esp::proj_matrix_arr[0] == 0.f || esp::model_matrix_arr[0] == 0.f)
		return;

	esp::block_esp();

	return;
}

void esp::block_esp() {
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(esp::proj_matrix_arr);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(esp::model_matrix_arr);

	glPushMatrix();
	glEnable(GL_LINE_SMOOTH);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	glDepthMask(false);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glLineWidth(1.f);

	for (const auto& block : esp::block_points)
		renderer::gl::draw_outlined_box(block.bounding_box);

	glDisable(GL_BLEND);
	glDepthMask(true);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LINE_SMOOTH);
	glPopMatrix();

	glPopMatrix();
}

void esp::name(esp_data data) {
	
	// since they already have names above their head, we don't need to draw the name if they are too close
	if (data.distance < 10)
		return;

	std::string name = data.name;

	// truncate name if too long (old ayyware crasher meme)
	if (name.length() > 16)
		name = name.substr(0, 16) + "...";

	ImGui::GetBackgroundDrawList()->AddText(
		ImVec2(data.box.x + data.box.w / 2 - ImGui::CalcTextSize(name.c_str()).x / 2, data.box.y - ImGui::CalcTextSize(name.c_str()).y - 1),
		ImColor(255, 255, 255),
		name.c_str()
	);

}

void esp::box(esp_data data) {

	ImGui::GetBackgroundDrawList()->AddRect(
		ImVec2((float)(data.box.x), (float)(data.box.y)),
		ImVec2((float)(data.box.x + data.box.w), (float)(data.box.y + data.box.h)),
		ImColor(255, 255, 255)
	);

	// cool outer online only
	ImGui::GetBackgroundDrawList()->AddRect(
		ImVec2((float)(data.box.x - 1), (float)(data.box.y - 1)),
		ImVec2((float)(data.box.x + data.box.w + 1), (float)(data.box.y + data.box.h + 1)),
		ImColor(0, 0, 0, 180)
	);

}

void esp::health(esp_data data) {

	if (data.box.h <= 0)
		return;

	// health bar will be green if health is near max (or max) and red if health is low
	const float health_percentage = (float)data.health / (float)data.max_health;

	// calculate the color
	ImColor health_color = ImColor(
		0,
		255,
		0
	);

	// lerp lambda
	auto lerp = [](float a, float b, float f) -> float {
		return a + f * (b - a);
	};

	// lerp the color
	health_color.Value.x = lerp(255, 0, health_percentage);
	health_color.Value.y = lerp(0, 255, health_percentage);

	int bar_size = 0;
	if (data.max_health > 0)
		bar_size = std::clamp(int(data.health * data.box.h) / data.max_health, 0, data.box.h);
	else
		bar_size = 0;

	ImGui::GetBackgroundDrawList()->AddRect(
		ImVec2((float)(data.box.x - 6), (float)(data.box.y - 1)),
		ImVec2((float)(data.box.x - 2), (float)(data.box.y + data.box.h + 1)),
		ImColor(0, 0, 0, 180)
	);

	ImGui::GetBackgroundDrawList()->AddRectFilled(
		ImVec2((float)(data.box.x - 5), (float)(data.box.y)),
		ImVec2((float)(data.box.x - 3), (float)(data.box.y + data.box.h)),
		ImColor(0, 0, 0, 65)
	);

	ImGui::GetBackgroundDrawList()->AddRectFilled(
		ImVec2((float)(data.box.x - 5), (float)(data.box.y + (data.box.h - bar_size))),
		ImVec2((float)(data.box.x - 3), (float)(data.box.y + data.box.h)),
		health_color
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

	auto projection_matrix = render_info.get_projection_matrix();
	auto modelview_matrix = render_info.get_modelview_matrix();

	convert_matrix_to_glfloat(projection_matrix, esp::proj_matrix_arr);
	convert_matrix_to_glfloat(modelview_matrix, esp::model_matrix_arr);

	auto viewport = render_info.get_viewport();
	esp::screen_size = Vector2((float)(viewport[2]), (float)(viewport[3]));
	
	std::vector<esp_data> point_buffer;
	std::vector<block_data> block_buffer;
	
	// example of how to add a block to the block buffer
	/*
	Vector3 block_pos = Vector3(5, 78, -4);
	block_pos = block_pos - Vector3(globals::render_manager->get_render_posx(), globals::render_manager->get_render_posy(), globals::render_manager->get_render_posz());
	block_buffer.push_back(block_data(BoundingBox(block_pos.x, block_pos.y, block_pos.z, block_pos.x + 1, block_pos.y + 1, block_pos.z + 1)));

	block_pos = Vector3(5, 78, -5);
	block_pos = block_pos - Vector3(globals::render_manager->get_render_posx(), globals::render_manager->get_render_posy(), globals::render_manager->get_render_posz());
	block_buffer.push_back(block_data(BoundingBox(block_pos.x, block_pos.y, block_pos.z, block_pos.x + 1, block_pos.y + 1, block_pos.z + 1)));
	*/

	for (auto player : players) {

		if (player->get_id() == local_player->get_id())
			continue;

		if (player->is_valid() == false)
			continue;

		double x = player->get_x();
		double y = player->get_y();
		double z = player->get_z();

		double dist = sqrt(pow(x - local_player->get_x(), 2) + pow(y - local_player->get_y(), 2) + pow(z - local_player->get_z(), 2));

		if (dist > esp::max_distance)
			continue;

		std::string player_name = player->get_name();

		esp_data data;
		box_t box;
		if (!esp::compute_box(player, local_player, box))
			continue;

		data.name = player_name;
		data.box = box;
		data.health = (int)player->get_health();
		data.max_health = (int)player->get_max_health();
		data.distance = (float)dist;

		point_buffer.push_back(data);
	}

	esp::entity_points = point_buffer;
	esp::block_points = block_buffer;
}

bool esp::compute_box(std::shared_ptr<c_entity> player, std::shared_ptr<c_entity> local_player, box_t& bbox) {

	double x = player->get_x();
	double y = player->get_y();
	double z = player->get_z();

	float player_offset = 2.125f;
	if (player->is_sneaking())
		player_offset -= .175f;

	float local_player_offset = 3.4f;
	if (local_player->is_sneaking())
		local_player_offset -= .175f;

	Vector3 entity_pos = Vector3((float)x, (float)y, (float)z);
	Vector3 entity_tick_prev_pos = Vector3((float)player->get_prev_x(), (float)player->get_prev_y(), (float)player->get_prev_z());

	Vector3 render_pos = Vector3((float)globals::render_manager->get_render_posx(), (float)globals::render_manager->get_render_posy() + local_player_offset, (float)globals::render_manager->get_render_posz());
	Vector3 orgin{ render_pos - entity_tick_prev_pos + (entity_tick_prev_pos - entity_pos) * globals::timer->get_render_partial_ticks() };

	Vector2 bottom;

	if (!c_world_to_screen::world_to_screen((orgin), esp::model_matrix, esp::proj_matrix, (int)esp::screen_size.x, (int)esp::screen_size.y, bottom))
		return false;

	Vector2 top;

	orgin.y -= player_offset;
	if (!c_world_to_screen::world_to_screen((orgin), esp::model_matrix, esp::proj_matrix, (int)esp::screen_size.x, (int)esp::screen_size.y, top))
		return false;

	bbox.x = int(top.x - ((bottom.y - top.y) / 2) / 2);
	bbox.y = int(top.y);

	bbox.w = int((bottom.y - top.y) / 2);
	bbox.h = int(bottom.y - top.y);

	return true;
}