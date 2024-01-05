#define _WINSOCKAPI_
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <cstdint>
#include "include/MinHook.h"
#include "hooks.hpp"
#include "java.hpp"
#include "mappings.hpp"
#include "c_minecraft.hpp"
#include "cheat.hpp"

void unload(void* instance, const char* reason = "No reason given.");

const wchar_t* title = L"minecraft backtrack";
bool attached = false;

void main_thread(void* instance) {

	_CrtSetBreakAlloc(160);
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);

	// setup console
	attached = AllocConsole() && SetConsoleTitleW(title);
	freopen_s(reinterpret_cast<FILE**>stdin, "CONIN$", "r", stdin);
	freopen_s(reinterpret_cast<FILE**>stdout, "CONOUT$", "w", stdout);

	while (!(GetModuleHandleA(("jvm.dll"))))
		Sleep(500);

	if (!attached)
		unload(instance);

	// init jvm stuff
	jsize count;

	if (JNI_GetCreatedJavaVMs(&java_instance->vm, 1, &count) != JNI_OK || count == 0)
		unload(instance, "JavaVM not found.\n");

	jint res = java_instance->vm->GetEnv((void**)&java_instance->env, JNI_VERSION_1_8);

	if (res == JNI_EDETACHED)
		res = java_instance->vm->AttachCurrentThread((void**)&java_instance->env, nullptr);

	if (java_instance->env == nullptr)
		unload(instance);

	hooks::init();

	java_instance->get_loaded_classes();

	// init mappings
	init_mappings(); // in the end we will have a server that sends us the mappings for different version support.

	// keeping the thread alive
	while (!GetAsyncKeyState(VK_END)) {

		// not quite sure if having these in a loop here will cause a memory leaks, but i don't think so.

		// get minecraft instance
		auto minecraft = std::make_unique<c_minecraft>();

		// get world instance
		auto world = std::make_unique<c_world>(minecraft->get_world());

		run_cheat(std::move(minecraft), std::move(world));
		Sleep(1);
	}

	// sleep, shutdown, sleep, unload
	Sleep(1000);
	hooks::shutdown();
	Sleep(1000);
	unload(instance);
}

void unload(void* instance, const char* reason) {
	printf("Unloading: %s\n", reason);
	auto console_window = GetConsoleWindow();
	FreeConsole();
	PostMessageA(console_window, WM_QUIT, 0, 0);
	FreeLibraryAndExitThread((HMODULE)instance, 0);
}

int __stdcall DllMain(void* instance, unsigned long reason_to_call, void* reserved) {
	if (reason_to_call != DLL_PROCESS_ATTACH)
		return TRUE;

	HANDLE threadHandle = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main_thread, instance, 0, nullptr);
	if (threadHandle != NULL)
		CloseHandle(threadHandle);

	return TRUE;
}