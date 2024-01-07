#pragma once
#define _WINSOCKAPI_
#include <WinSock2.h>

namespace hooks {

    typedef LRESULT(CALLBACK* template_wnd_proc) (HWND, UINT, WPARAM, LPARAM);
    inline template_wnd_proc original_wnd_proc;
    LRESULT CALLBACK hook_wnd_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    void init();
    void shutdown();

    inline int(__stdcall* wsasend_original)(
        SOCKET s,
        LPWSABUF lp_buffers,
        DWORD dw_buffer_count,
        LPDWORD lp_number_of_bytes_sent,
        DWORD dw_flags,
        LPWSAOVERLAPPED lp_overlapped,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE lp_completion_routine);

    int __stdcall wsasend_hook(
        SOCKET s,
        LPWSABUF lp_buffers,
        DWORD dw_buffer_count,
        LPDWORD lp_number_of_bytes_sent,
        DWORD dw_flags,
        LPWSAOVERLAPPED lp_overlapped,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE lp_completion_routine);

    inline int(__stdcall* wsarecv_original)(
        SOCKET s,
        LPWSABUF lp_buffers,
        DWORD dw_buffer_count,
        LPDWORD lp_number_of_bytes_recvd,
        LPDWORD lp_flags,
        LPWSAOVERLAPPED lp_overlapped,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE lp_completion_routine);

    int __stdcall wsarecv_hook(
        SOCKET s,
        LPWSABUF lp_buffers,
        DWORD dw_buffer_count,
        LPDWORD lp_number_of_bytes_recvd,
        LPDWORD lp_flags,
        LPWSAOVERLAPPED lp_overlapped,
        LPWSAOVERLAPPED_COMPLETION_ROUTINE lp_completion_routine);

    int __stdcall recv_hook(SOCKET s, char* buf, int len, int flags);

    inline int(__stdcall* recv_original)(
        SOCKET s, char* buf, int len, int flags);

    int __stdcall send_hook(SOCKET s, const char* buf, int len, int flags);

    inline int(__stdcall* send_original)(
        SOCKET s, const char* buf, int len, int flags);

    inline bool(__stdcall* wgl_swap_buffers_original) (HDC hdc);

    bool __stdcall wgl_swap_buffers_hook(HDC hdc);
}
