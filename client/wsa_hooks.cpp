#include "hooks.hpp"
#include <vector>
#include <iostream>
#include <chrono>

int __stdcall hooks::wsasend_hook(
    SOCKET s,
    LPWSABUF lpBuffers,
    DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesSent,
    DWORD dwFlags,
    LPWSAOVERLAPPED lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {

	return hooks::wsasend_original(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine);
}

int __stdcall hooks::wsarecv_hook(
	SOCKET s,
	LPWSABUF lpBuffers,
	DWORD dwBufferCount,
	LPDWORD lpNumberOfBytesRecvd,
	LPDWORD lpFlags,
	LPWSAOVERLAPPED lpOverlapped,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) {

	return hooks::wsarecv_original(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpOverlapped, lpCompletionRoutine);
}

int __stdcall hooks::recv_hook(SOCKET s, char* buf, int len, int flags) {
	//printf("recv called\n");

	return hooks::recv_original(s, buf, len, flags);
}

int __stdcall hooks::send_hook(SOCKET s, const char* buf, int len, int flags) {
	//printf("send called\n");

	return hooks::send_original(s, buf, len, flags);
}