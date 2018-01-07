#pragma once

#include <windows.h>

#include <memory>
#include <string>
#include <vector>

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

namespace DXDraw
{
	void Line(IDirect3DDevice9* pDevice, int x1, int y1, int x2, int y2, DWORD color);
	void Rect(IDirect3DDevice9* pDevice, int x, int y, int w, int h, DWORD color);
	void Circle(IDirect3DDevice9* pDevice, int x, int y, int r, DWORD color, int resolution = 64);
	void Text(IDirect3DDevice9* pDevice, LPD3DXFONT pFont, int x, int y, bool centered, DWORD color, const char* fmt, ...);
	void FillRect(IDirect3DDevice9* pDevice, int x, int y, int w, int h, DWORD color);
};