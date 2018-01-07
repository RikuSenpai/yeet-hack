#include "SDK.h"

namespace PTDraw
{
	void String(int x, int y, Color color, bool bCenter, const char* szText, ...);

	void Rect(int x, int y, int w, int h, Color color);
	void OutlineRect(int x, int y, int w, int h, Color clrColor);
	void Line(int x0, int y0, int x1, int y1, Color clrColor);

	unsigned int GetFont();
}