#include "misc.hpp"
#include "globals.hpp"
#include <TlHelp32.h>
#include <psapi.h>
#include <chrono>
#include <iomanip>
#include <sstream>

void misc::draw() {

	if (globals::minecraft == nullptr)
		return;

	if (globals::world == nullptr)
		return;

    if (!misc::watermark.display)
		return;

	ImGui::GetBackgroundDrawList()->AddText(
		ImVec2(1, 1),
		misc::watermark.color,
		"cheat_name"
	);

	ImGui::GetBackgroundDrawList()->AddText(
		ImVec2(1, 1 + ImGui::CalcTextSize(misc::watermark.value.c_str()).y),
		ImColor(30,215,96),
		misc::watermark.value.c_str()
	);
}

void misc::update_data() {

    if (globals::minecraft == nullptr || globals::world == nullptr) {
        misc::watermark.display = false;
        return;
    }

    std::shared_ptr<c_entity> local_player = std::make_shared<c_entity>(globals::minecraft->get_local_player());

    // i only wanna display it in game
    if (local_player == nullptr || !local_player.get() || !local_player || !local_player->is_valid()) {
        misc::watermark.display = false;
        return;
    }

    misc::watermark.display = true;

    static auto last_time_check = std::chrono::high_resolution_clock::now();
    static float timer = 25.0f;
    const float check_time = 30.0f;

    auto current_time = std::chrono::high_resolution_clock::now();
    float delta_time = std::chrono::duration<float>(current_time - last_time_check).count();
    last_time_check = current_time;
    timer += delta_time;

    if (timer > check_time && misc::spotify_pid == 0) {
        auto snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(PROCESSENTRY32);

        while (Process32NextW(snap, &entry)) {
            if (std::wstring(entry.szExeFile) == L"Spotify.exe") {
                misc::spotify_pid = entry.th32ProcessID;
                break;
            }
        }
        CloseHandle(snap);
        timer = 0.0f;
    }

    if (misc::spotify_pid == 0) {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(1) << (check_time - timer);
        misc::watermark.value = "spotify not available " + stream.str();
        return;
    }

    if (misc::spotify_pid != 0 && misc::spotify_hwnd == nullptr) {
        std::vector<DWORD> pids = { misc::spotify_pid };
        EnumWindows([](HWND hwnd, LPARAM l_param) -> BOOL {
            const auto& pids = *reinterpret_cast<std::vector<DWORD>*>(l_param);
            DWORD win_id;
            GetWindowThreadProcessId(hwnd, &win_id);
            if (std::find(pids.begin(), pids.end(), win_id) != pids.end()) {
                std::wstring title(GetWindowTextLength(hwnd) + 1, L'\0');
                GetWindowTextW(hwnd, &title[0], (int)title.size());
                if (!title.empty() && title.find(L"-") != std::wstring::npos) {
                    misc::spotify_hwnd = hwnd;
                    return FALSE;
                }
            }
            return TRUE;
            }, reinterpret_cast<LPARAM>(&pids));
    }

    if (misc::spotify_hwnd != nullptr) {
        
        std::string title(GetWindowTextLengthA(misc::spotify_hwnd) + 1, '\0');
        GetWindowTextA(misc::spotify_hwnd, &title[0], (int)title.size());

        if (!title.empty() && title.find("-") != std::string::npos) {
            if (title.length() > 1)
				misc::watermark.value = title.substr(0, 24) + "...";
        }
        else {
            misc::spotify_hwnd = nullptr;
            misc::spotify_pid = 0;
            timer = 0;
        }
    }
    else {
        misc::spotify_hwnd = nullptr;
        misc::spotify_pid = 0;
        timer = 0;
    }
}