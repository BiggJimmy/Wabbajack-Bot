#pragma once
#include <Windows.h>

class Display
{
public:
	bool Begin(const HWND hWnd)
	{
		if (!hWnd)
		{
			return false;
		}

		Wnd = hWnd;

		if (!dc)
		{
			dc = GetDC(NULL);
			Open = true;
		}

		Width = GetSystemMetrics(0);
		Height = GetSystemMetrics(1);

		return true;
	}

	bool IsOpen()
	{
		return Open;
	}

	COLORREF GetColor(const int x, const int y)
	{
		COLORREF Color{};

		if (dc)
		{
			Color = GetPixel(dc, x, y);
		}

		return Color;
	}

	bool FindDownload(const COLORREF Color, const LPPOINT Point, const int X, const int Step)
	{
		for (int Y = Height / 2; Y < Height; Y += Step)
		{
			const COLORREF PixelColor = GetColor(X, Y);

			if (PixelColor == Color)
			{
				Point->x = X;
				Point->y = Y;

				return true;
			}
		}

		return false;
	}

	void End()
	{
		if (dc)
		{
			ReleaseDC(NULL, dc);
			Open = false;
		}
	}
private:
	HWND Wnd{};
	HDC dc{};
	int Width{}, Height{};
	bool Open{};
};