#pragma once
#include <Windows.h>

class Mutex
{
public:
	bool Begin(const LPCSTR lpName)
	{
		hMutex = OpenMutex(MUTEX_ALL_ACCESS, 0, lpName);
		if (!hMutex)
		{
			hMutex = CreateMutex(0, 0, lpName);
			Open = true;

			return true;
		}
		else
		{
			return false;
		}
	}

	bool IsOpen()
	{
		return Open;
	}

	void End()
	{
		if (hMutex)
		{
			ReleaseMutex(hMutex);
			Open = false;
		}
	}
private:
	HANDLE hMutex{};
	bool Open{};
};