#include "hooks.hpp"
#include "globals.hpp"
#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_opengl2.h"
#include "esp.hpp"
#include "misc.hpp"
#include "gui.hpp"

bool hooks::wgl_swap_buffers_hook(HDC hdc) {

    static bool once = [](HDC hdc) -> bool {
        gui::init(hdc);
        return true;
    }(hdc);

    gui::begin();

    if (globals::menu_open)
        gui::draw();

    esp::draw();
    misc::draw();

    gui::end();

    return hooks::wgl_swap_buffers_original(hdc);
}