#include "Draw.h"

void PTDraw::String(int x, int y, Color clrColor, bool bCenter, const char* szText, ...)
{
	if (!szText)
		return;

	va_list va_alist = nullptr;
	char szBuffer[256] = { '\0' };
	wchar_t szString[128] = { '\0' };

	va_start(va_alist, szText);
	vsprintf_s(szBuffer, szText, va_alist);
	va_end(va_alist);

	MultiByteToWideChar(CP_UTF8, 0, szBuffer, -1, szString, 128);

	if (bCenter)
	{
		int Wide = 0, Tall = 0;

		Interface.Surface->GetTextSize(GetFont(), szString, Wide, Tall);

		x -= Wide / 2;
	}

	Interface.Surface->DrawSetTextPos(x, y);
	Interface.Surface->DrawSetTextFont(GetFont());
	Interface.Surface->DrawSetTextColor(clrColor);
	Interface.Surface->DrawPrintText(szString, strlen(szBuffer));
}

void PTDraw::Rect(int x, int y, int w, int h, Color clrColor)
{
	Interface.Surface->DrawSetColor(clrColor);
	Interface.Surface->DrawFilledRect(x, y, x + w, y + h);
}

void PTDraw::OutlineRect(int x, int y, int w, int h, Color clrColor)
{
	Interface.Surface->DrawSetColor(clrColor);
	Interface.Surface->DrawOutlinedRect(x, y, x + w, y + h);
}

void PTDraw::Line(int x0, int y0, int x1, int y1, Color clrColor)
{
	Interface.Surface->DrawSetColor(clrColor);
	Interface.Surface->DrawLine(x0, y0, x1, y1);
}

unsigned int PTDraw::GetFont()
{
	static unsigned long font = 0;

	if (!font)
	{
		font = Interface.Surface->CreateFnt();
		Interface.Surface->SetFontGlyphSet(font, "gill sans ultra bold", 15, 500, 0, 0, FONTFLAG_OUTLINE);
	}

	return font;
}
