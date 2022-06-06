#include "main.h"

void ExitHandler()
{
	if (display.IsOpen())
	{
		display.End();
	}

	if (mutex.IsOpen())
	{
		mutex.End();
	}

	return;
}

AlCode Init()
{
	SetConsoleTitle(ApplicationName);
	atexit(ExitHandler);

	if (!mutex.Begin(ApplicationName))
	{
		cout << "this application is already running." << endl;
		return AlCode::Failure;
	}

	if ((WabbaJackId = GetProcessID(WabbaJackExe)))
	{
		if ((WabbaJackWnd = FindMainWindow(WabbaJackId)))
		{
			cout << "success." << endl;
			SetWindowPos(ConsoleWindow, HWND_BOTTOM, NULL, NULL, NULL, NULL, SWP_NOSIZE | SWP_NOMOVE);

			if (!display.Begin(WabbaJackWnd))
			{
				cout << "could not get current display." << endl;
				return AlCode::Failure;
			}

			return AlCode::Success;
		}
		else
		{
			cout << "could not find the main window of Wabbjack." << endl;
			return AlCode::Failure;
		}
	}
	else
	{
		cout << "please make sure that Wabbajack is running." << endl;
		return AlCode::Failure;
	}
}

void Cleanup()
{
	if (display.IsOpen())
	{
		display.End();
	}

	if (mutex.IsOpen())
	{
		mutex.End();
	}
}

int main()
{
	if (AL_SUCCESS(Init()))
	{
		cout << endl << "the program will now exit..." << endl;
		Sleep(5000);

		return 1;
	}

	while (!IsKeyDown(VK_ESCAPE))
	{
		POINT Pos{};

		if (display.FindDownload(RectCol, &Pos, RectPosX, RectStep))
		{
			SendClick(Pos.x, Pos.y);
		}

		Sleep(9);
	}

	Cleanup();
	return 0;
}