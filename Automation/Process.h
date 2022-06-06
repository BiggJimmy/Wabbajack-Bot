#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>

struct HandleData
{
	DWORD ProcessId;
	HWND hWnd;
};

HWND FindMainWindow(const DWORD ProcessId);
DWORD GetProcessID(const char* ProcessName);
void SendClick(const int X, const int Y);
void SendClick(const HWND hWnd, const int X, const int Y);