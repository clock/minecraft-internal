#include "gui.hpp"
#include <WinUser.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"

void gui::draw() {
    ImGui::SetNextWindowSize({ 300, 200 }, ImGuiCond_Once);
    ImGui::Begin("test gui", 0);

    ImGui::SliderFloat("slider 1", &slide, 0.f, 1.f);

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