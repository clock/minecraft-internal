#include "hooks.hpp"
#include "globals.hpp"
#include "imgui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK hooks::hook_wnd_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_KEYDOWN) {
		if (wParam == VK_INSERT) {
			globals::menu_open = !globals::menu_open;
		}
		if (wParam == VK_ESCAPE && globals::menu_open)
			globals::menu_open = false;
	}

	if (globals::menu_open)
	{
		ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
		return true;
	}

	return CallWindowProc(hooks::original_wnd_proc, hwnd, msg, wParam, lParam);
}