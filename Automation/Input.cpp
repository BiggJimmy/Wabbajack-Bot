#include "Input.h"

bool IsKeyDown(const int vKey)
{
	if (GetAsyncKeyState(vKey) & 0x8000)
	{
		return true;
	}
	
	return false;
}