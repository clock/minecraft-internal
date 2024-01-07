#include "hooks.hpp"
#include "globals.hpp"
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"
#include "esp.hpp"

bool hooks::wgl_swap_buffers_hook(HDC hdc) {
    // this will be in the config system in the future
    static float slide = 0.f;

    static bool once = [](HDC hdc) -> bool {

        auto context = ImGui::CreateContext();
        ImGui::SetCurrentContext(context);

        ImGui_ImplWin32_Init(WindowFromDC(hdc));
        ImGui_ImplOpenGL2_Init();

        auto& io = ImGui::GetIO();
        io.IniFilename = nullptr;
        io.LogFilename = nullptr;

        return true;

    }(hdc);

    // Start the ImGui frame
    ImGui_ImplWin32_NewFrame();
    ImGui_ImplOpenGL2_NewFrame();
    ImGui::NewFrame();

    if (globals::menu_open) {
        ImGui::SetNextWindowSize({ 300, 200 }, ImGuiCond_Once);
        ImGui::Begin("test gui", 0);

        ImGui::SliderFloat("slider 1", &slide, 0.f, 1.f);

        ImGui::End();
    }

    esp::run();

    ImGui::EndFrame();
    
    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    return hooks::wgl_swap_buffers_original(hdc);
}