#include "hooks.hpp"
#include "globals.hpp"
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"

bool hooks::wgl_swap_buffers_hook(HDC hdc) {

    static bool setup = false;
    static float slide = 0.f;

    if (!setup) {
        setup = true;

        auto context = ImGui::CreateContext();
        ImGui::SetCurrentContext(context);

        ImGui_ImplWin32_Init(WindowFromDC(hdc));
        ImGui_ImplOpenGL2_Init();

        auto& io = ImGui::GetIO();

        io.IniFilename = nullptr;
        io.LogFilename = nullptr;
    }

    if (globals::menu_open) {
        ImGui_ImplWin32_NewFrame();
        ImGui_ImplOpenGL2_NewFrame();
        ImGui::NewFrame();

        ImGui::GetBackgroundDrawList()->AddRectFilled({ 25, 25 }, { 100, 100 }, ImColor(255, 0, 0));

        ImGui::SetNextWindowSize({ 300, 200 }, ImGuiCond_Once);
        ImGui::Begin("test gui", 0); {
            ImGui::SliderFloat("slider 1", &slide, 0.f, 1.f);
        }

        ImGui::End();

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    }

	return hooks::wgl_swap_buffers_original(hdc);
}