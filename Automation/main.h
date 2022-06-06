#pragma once
#include "Globals.h"

enum class AlCode : int
{
	Success = 0,
	Failure = 1,
	Unknown = 2
};

#define AL_SUCCESS(alCode) alCode != AlCode::Success

Mutex mutex{};
Display display{};

const COLORREF RectCol = RGB(221, 221, 221);
const int RectPosX = 1026;
const int RectPosY = 0;
const int RectHeight = 40;
const int RectStep = RectHeight / 2;