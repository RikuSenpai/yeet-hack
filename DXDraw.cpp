#include "DXDraw.h"

struct D3DVertex
{
	D3DVertex(float _x, float _y, float _z, DWORD _color)
		: x(_x), y(_y), z(_z), color(_color)
	{
	}

	float x;
	float y;
	float z;
	float rhw = 0;
	DWORD color;
};

void DXDraw::Line(LPDIRECT3DDEVICE9 pDevice, int x1, int y1, int x2, int y2, DWORD color)
{
	D3DVertex vertices[2] = {
		D3DVertex(x1, y1, 1.0f, color),
		D3DVertex(x2, y2, 1.0f, color)
	};
	pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, vertices, sizeof(D3DVertex));
}

void DXDraw::Rect(IDirect3DDevice9* pDevice, int x, int y, int w, int h, DWORD color)
{
	D3DVertex vertices[5] = {
		D3DVertex(x, y, 1.0f, color),
		D3DVertex(x + w, y, 1.0f, color),
		D3DVertex(x + w, y + h, 1.0f, color),
		D3DVertex(x, y + h, 1.0f, color),
		D3DVertex(x, y, 1.0f, color)
	};
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, vertices, sizeof(D3DVertex));
}

void DXDraw::Circle(IDirect3DDevice9* pDevice, int x, int y, int r, DWORD color, int resolution)
{
	const double PI = 3.14159265358979323846264;
	float curPointX;
	float curPointY;
	float oldPointX;
	float oldPointY;

	for (int i = 0; i <= resolution; ++i) {
		curPointX = x + r * cos(2 * PI * i / resolution);
		curPointY = y - r * sin(2 * PI * i / resolution);
		if (i > 0) {
			Line(pDevice, curPointX, curPointY, oldPointX, oldPointY, color);
		}
		oldPointX = curPointX;
		oldPointY = curPointY;
	}
}

int GetTextWidth(const char *szText, ID3DXFont* pFont)
{
	RECT rcRect = { 0,0,0,0 };
	if (pFont)
	{
		// calculate required rect
		pFont->DrawTextA(NULL, szText, strlen(szText), &rcRect, DT_CALCRECT,
			D3DCOLOR_XRGB(0, 0, 0));
	}

	// return width
	return rcRect.right - rcRect.left;
}


void DXDraw::Text(IDirect3DDevice9* pDevice, ID3DXFont* pFont, int x, int y, bool centered, DWORD color, const char* fmt, ...)
{
	char buffer[512];
	va_list args;
	va_start(args, fmt);
	vsprintf(buffer, fmt, args);
	va_end(args);

	auto drawShadow = [&](RECT rect) {
		rect.left++;
		pFont->DrawTextA(NULL, buffer, -1, &rect, DT_NOCLIP, 0xFF000000);
		rect.top++;
		pFont->DrawTextA(NULL, buffer, -1, &rect, DT_NOCLIP, 0xFF000000);
	};

	if (centered) {
		int w = GetTextWidth(fmt, pFont);
		RECT rec = { x - w / 2, y, 0, 0 };

		drawShadow(rec);
		pFont->DrawTextA(NULL, buffer, -1, &rec, DT_NOCLIP, color);

	}
	else {
		RECT rec = { x,y,1000,100 };

		drawShadow(rec);
		pFont->DrawTextA(NULL, buffer, -1, &rec, DT_NOCLIP, color);
	}
}

void DXDraw::FillRect(IDirect3DDevice9* pDevice, int x, int y, int w, int h, DWORD color)
{
	D3DRECT rec = { (long)x, (long)y, (long)x + w, (long)x + h };
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}