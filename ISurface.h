#pragma once
#include "Includes.h"
#include "Color.h"

typedef unsigned long HFont;

class ISurface
{
public:

	///<summary>Sets draw color</summary>
	void DrawSetColor(Color clr)
	{
		typedef void(__thiscall* DrawSetColorFn)(void*, Color);
		return CallVFunc<DrawSetColorFn>(this, 15)(this, clr);
	}

	///<summary>Draws filled rect
	void DrawFilledRect(int x, int y, int w, int h)
	{
		typedef void(__thiscall* DrawFilledRectFn)(void*, int, int, int, int);
		return CallVFunc<DrawFilledRectFn>(this, 16)(this, x, y, w, h);
	}

	///<summary>Draws outlined rect
	void DrawOutlinedRect(int x, int y, int w, int h)
	{
		typedef void(__thiscall* DrawOutlinedRectFn)(void*, int, int, int, int);
		return CallVFunc<DrawOutlinedRectFn>(this, 18)(this, x, y, w, h);
	}

	///<summary>Draws line
	void DrawLine(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* DrawOutlinedRectFn)(void*, int, int, int, int);
		return CallVFunc<DrawOutlinedRectFn>(this, 19)(this, x0, y0, x1, y1);
	}

	///<summary>Sets font of text</summary>
	void DrawSetTextFont(unsigned long index)
	{
		typedef void(__thiscall* DrawSetTextFontFn)(void*, unsigned long);
		return CallVFunc<DrawSetTextFontFn>(this, 23)(this, index);
	}

	///<summary>Sets color of text</summary>
	void DrawSetTextColor(Color clr)
	{
		typedef void(__thiscall* DrawSetTextColorFn)(void*, Color);
		return CallVFunc<DrawSetTextColorFn>(this, 25)(this, clr);
	}

	///<summary>Sets text draw pos</summary>
	void DrawSetTextPos(int x, int y)
	{
		typedef void(__thiscall* DrawSetTextPosFn)(void*, int, int);
		return CallVFunc<DrawSetTextPosFn>(this, 26)(this, x, y);
	}

	///<summary>Draws special prinr text</summary>
	void DrawPrintText(wchar_t* text, int length, FontDrawType_t drawtype = FontDrawType_t::FONT_DRAW_DEFAULT)
	{
		typedef void(__thiscall* DrawPrintTextFn)(void*, wchar_t*, int, FontDrawType_t);
		return CallVFunc<DrawPrintTextFn>(this, 28)(this, text, length, drawtype);
	}

	///<summary>Creates new font</summary>
	HFont CreateFnt()
	{
		typedef HFont(__thiscall* CreateFntFn)(void*);
		return CallVFunc<CreateFntFn>(this, 71)(this);
	}

	///<summary>Sets font glyph and returns true if func was completed</summary>
	bool SetFontGlyphSet(unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0)
	{
		typedef bool(__thiscall* SetFontGlyphSetFn)(void*, unsigned long, const char*, int, int, int, int, int, int, int);
		return CallVFunc<SetFontGlyphSetFn>(this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
	}

	///<summary>Adds custon font file, return true if func was completed</summary>
	bool AddCustomFontFile(const char* fontFileName)
	{
		typedef bool(__thiscall* AddCustomFontFileFn)(void*, const char*);
		return CallVFunc<AddCustomFontFileFn>(this, 73)(this, fontFileName);
	}

	///<summary>Rutrns text size</summary>
	bool GetTextSize(unsigned long font, const wchar_t* text, int& wide, int& tall)
	{
		typedef bool(__thiscall* GetTextSizeFn)(void*, unsigned long, const wchar_t*, int&, int&);
		return CallVFunc<GetTextSizeFn>(this, 79)(this, font, text, wide, tall);
	}

	///<summary>Plays sound</summary>
	void PlaySnd(const char* fileName)
	{
		typedef void(__thiscall* PlaySndFn)(void*, const char*);
		return CallVFunc<PlaySndFn>(this, 82)(this, fileName);
	}
};