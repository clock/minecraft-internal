#include "hooks.hpp"
#include "include/MinHook.h"
#include <iostream>

namespace hooks {

	void init() {
		MH_Initialize();

		//MH_CreateHookApi(L"ws2_32.dll", "WSASend", &hooks::WSASendHook, reinterpret_cast<void**>(&hooks::WSASendOriginal));
		//MH_CreateHookApi(L"ws2_32.dll", "WSARecv", &hooks::WSARecvHook, reinterpret_cast<void**>(&hooks::WSARecvOriginal));
		//MH_CreateHookApi(L"ws2_32.dll", "recv", &hooks::recvHook, reinterpret_cast<void**>(&hooks::recvOriginal));
		//MH_CreateHookApi(L"ws2_32.dll", "send", &hooks::sendHook, reinterpret_cast<void**>(&hooks::sendOriginal));

		LPVOID wgl_swap_buffers = nullptr;
		HMODULE h_module_opengl = GetModuleHandle(L"opengl32.dll");

		if (h_module_opengl != NULL)
			wgl_swap_buffers = (LPVOID)GetProcAddress(h_module_opengl, "wglSwapBuffers");
		MH_CreateHook(wgl_swap_buffers, (LPVOID)hooks::wgl_swap_buffers_hook, (LPVOID*)&hooks::wgl_swap_buffers_original);
		original_wnd_proc = (template_wnd_proc)SetWindowLongPtr(FindWindow(TEXT("LWJGL"), NULL), GWLP_WNDPROC, (LONG_PTR)hooks::hook_wnd_proc);
		MH_EnableHook(MH_ALL_HOOKS);
	}

	void shutdown() {
		SetWindowLongPtr(FindWindow(TEXT("LWJGL"), NULL), GWLP_WNDPROC, (LONG_PTR)original_wnd_proc);
		MH_DisableHook(MH_ALL_HOOKS);
		MH_RemoveHook(MH_ALL_HOOKS);
		MH_Uninitialize();
	}

}