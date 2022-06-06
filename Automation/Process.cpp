#include "Process.h"

BOOL EnumWindowsCallback(HWND hWnd, LPARAM lParam)
{
	auto& Data = *reinterpret_cast<HandleData*>(lParam);

	DWORD ProcessId = 0;
	GetWindowThreadProcessId(hWnd, &ProcessId);

	if (Data.ProcessId != ProcessId)
	{
		return TRUE;
	}

	Data.hWnd = hWnd;
	return FALSE;
}

HWND FindMainWindow(const DWORD ProcessId)
{
	HandleData Data{};

	Data.ProcessId = ProcessId;
	Data.hWnd = nullptr;

	EnumWindows(EnumWindowsCallback, reinterpret_cast<LPARAM>(&Data));

	return Data.hWnd;
}

DWORD GetProcessID(const char* ProcessName)
{
	PROCESSENTRY32 ProcessEntry{};
	ProcessEntry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE SnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (!SnapshotHandle)
	{
		return NULL;
	}

	DWORD ProcessId = NULL;
	while (Process32Next(SnapshotHandle, &ProcessEntry) == TRUE)
	{
		if (strcmp(ProcessEntry.szExeFile, ProcessName) == 0)
		{
			ProcessId = ProcessEntry.th32ProcessID;
			break;
		}
	}

	CloseHandle(SnapshotHandle);
	return ProcessId;
}

void SendClick(const int X, const int Y)
{
	auto LeftClick = [](const int X, const int Y)
	{
		POINT CursorPos{};
		GetCursorPos(&CursorPos);
		SetCursorPos(X, Y);

		INPUT Inputs[2];
		ZeroMemory(Inputs, sizeof(INPUT) * 2);
		Inputs[0].type = INPUT_MOUSE;
		Inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
		Inputs[1] = Inputs[0];
		Inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
		SendInput(2, Inputs, sizeof(INPUT));

		SetCursorPos(CursorPos.x, CursorPos.y);
	};

	auto RightClick = [](const int X, const int Y)
	{
		POINT CursorPos{};
		GetCursorPos(&CursorPos);
		SetCursorPos(X, Y);

		INPUT Inputs[2];
		ZeroMemory(Inputs, sizeof(INPUT) * 2);
		Inputs[0].type = INPUT_MOUSE;
		Inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		Inputs[1] = Inputs[0];
		Inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		SendInput(2, Inputs, sizeof(INPUT));

		SetCursorPos(CursorPos.x, CursorPos.y);
	};

	LeftClick(X, Y);
}

void SendClick(const HWND hWnd, const int X, const int Y)
{
	POINT Pos{X, Y};
	ScreenToClient(hWnd, &Pos);

	SendMessage(hWnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(Pos.x, Pos.y));
	SendMessage(hWnd, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(Pos.x, Pos.y));
}