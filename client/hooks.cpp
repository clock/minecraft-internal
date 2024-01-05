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

		LPVOID wglSwapBuffers = (LPVOID)GetProcAddress(GetModuleHandle(L"opengl32.dll"), "wglSwapBuffers");
		MH_CreateHook(wglSwapBuffers, (LPVOID)hooks::wglSwapBuffersHook, (LPVOID*)&hooks::wglSwapBuffersOriginal);

		MH_EnableHook(MH_ALL_HOOKS);
	}

	void shutdown() {
		MH_DisableHook(MH_ALL_HOOKS);
		MH_RemoveHook(MH_ALL_HOOKS);
		MH_Uninitialize();
	}

}