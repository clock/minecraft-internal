#include "gui.hpp"
#include <WinUser.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"
#include "globals.hpp"
#include "config.hpp"

void gui::draw() {
    ImGui::SetNextWindowSize({ 300, 200 }, ImGuiCond_Once);
    ImGui::Begin("test gui", 0);

    ImGui::Checkbox("aimbot", config::get<bool>("aimbot_enabled"));
    ImGui::SliderFloat("smoothing", config::get<float>("aimbot_smoothing"), 1.f, 100.f, "%.2f");
    ImGui::SliderFloat("target distance", config::get<float>("aimbot_target_dist"), 1.f, 10.f, "%.2f");

    const char* smoothing_modes[] = { "linear", "exponential", "sinusoidal", "logarithmic", "lerp", "smoothstep" };
    ImGui::Combo("smoothing mode", (int*)config::get<SmoothingMode>("aimbot_smoothing_mode"), smoothing_modes, IM_ARRAYSIZE(smoothing_modes));

    const char* aimbot_modes[] = { "angle", "mouse" };
    ImGui::Combo("aimbot mode", (int*)config::get<AimbotMode>("aimbot_mode"), aimbot_modes, IM_ARRAYSIZE(aimbot_modes));

    ImGui::Checkbox("esp", config::get<bool>("esp_enabled"));
    ImGui::SliderFloat("max distance", config::get<float>("esp_max_distance"), 1.f, 100.f, "%.2f");
    ImGui::Checkbox("player box", config::get<bool>("esp_player_box"));
    ImGui::Checkbox("player health", config::get<bool>("esp_player_health"));
    ImGui::Checkbox("player name", config::get<bool>("esp_player_name"));
    ImGui::Checkbox("block esp", config::get<bool>("esp_block_esp"));

    ImGui::End();
}

void gui::init(HDC hdc) {

    auto context = ImGui::CreateContext();
    ImGui::SetCurrentContext(context);

    ImGui_ImplWin32_Init(WindowFromDC(hdc));
    ImGui_ImplOpenGL2_Init();

    auto& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;

    globals::imgui_init = true;
}

void gui::shutdown() {
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void gui::begin() {
    ImGui_ImplWin32_NewFrame();
    ImGui_ImplOpenGL2_NewFrame();
    ImGui::NewFrame();
}

void gui::end() {
    ImGui::EndFrame();

    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}