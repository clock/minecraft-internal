#include "esp.hpp"
#include <iostream>
#include "world_to_screen.h"
#include "globals.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"

void esp::draw() {
	/*
	if (esp::test_point.value.empty())
		return;

	ImGui::GetBackgroundDrawList()->AddText(
		ImVec2(esp::test_point.pos.x, esp::test_point.pos.y),
		ImColor(255, 255, 255),
		esp::test_point.value.c_str()
	);
	*/
	return;
}

void esp::update_data() {
	if (globals::minecraft == nullptr)
		return;

	if (globals::world == nullptr)
		return;
}