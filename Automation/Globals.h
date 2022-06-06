#pragma once
#include <iostream>

#include "Display.h"
#include "Mutex.h"
#include "Process.h"
#include "Input.h"

using std::cout;
using std::endl;

const DWORD CurrentProcessId = GetCurrentProcessId();
const HWND ConsoleWindow = GetConsoleWindow();
const char* ApplicationName = "WABBAJACKAUTO";

DWORD WabbaJackId{};
HWND WabbaJackWnd{};
const char* WabbaJackExe = "Wabbajack.exe"; //Wabbajack.exe