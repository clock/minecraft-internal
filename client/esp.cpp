#include "esp.hpp"
#include <iostream>
#include "world_to_screen.h"
#include "globals.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"

void esp::run() {

	if (esp::test_point.value.empty())
		return;

	ImGui::GetBackgroundDrawList()->AddText(
		ImVec2(esp::test_point.pos.x, esp::test_point.pos.y),
		ImColor(255, 255, 255),
		esp::test_point.value.c_str()
	);

	return;
}

void esp::update_date() {
	if (!globals::minecraft)
		return;

	if (!globals::world)
		return;
	
	// get local player
	auto local_player = std::make_shared<c_entity>(globals::minecraft->get_local_player());

	//if (!local_player)
		//return;

	esp::test_point.pos = Vector2(10, 10);
	esp::test_point.value = std::to_string(local_player->get_x());
}