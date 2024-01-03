#define _WINSOCKAPI_
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <cstdint>
#include "include/MinHook.h"
#include "hooks.hpp"

void unload(void* instance);

const wchar_t* title = L"minecraft backtrack";
bool attached = false;

void main_thread(void* instance) {

	// setup console
	attached = AllocConsole() && SetConsoleTitleW(title);
	freopen_s(reinterpret_cast<FILE**>stdin, "CONIN$", "r", stdin);
	freopen_s(reinterpret_cast<FILE**>stdout, "CONOUT$", "w", stdout);

	if (!attached)
		unload(instance);

	// init hooks
	hooks::init();

	// keeping the thread alive
	while (!GetAsyncKeyState(VK_END)) {

		Sleep(1);
	}

	// sleep, shutdown, sleep, unload
	Sleep(1000);
	hooks::shutdown();
	Sleep(1000);
	unload(instance);
}

void unload(void* instance) {
	auto console_window = GetConsoleWindow();
	FreeConsole();
	PostMessageA(console_window, WM_QUIT, 0, 0);
	FreeLibraryAndExitThread((HMODULE)instance, 0);
}

int __stdcall DllMain(void* instance, unsigned long reason_to_call, void* reserved) {
	if (reason_to_call != DLL_PROCESS_ATTACH)
		return TRUE;

	CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main_thread, instance, 0, nullptr));

	return TRUE;
}