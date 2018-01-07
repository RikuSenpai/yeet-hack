#pragma once
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_internal.h"
#include "ImGUI/DX9/imgui_impl_dx9.h"

int screenWidth, screenHeight;
ImDrawData			_drawData;
ImDrawList*         _drawList;
IDirect3DTexture9*  _texture;
ImFontAtlas         _fonts;

extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#include "CVisuals.h"
#include "CMenu.h"

namespace CRender
{
	void __stdcall CreateObjects(IDirect3DDevice9* pDevice)
	{
		_drawList = new ImDrawList();

		auto font_path = std::string{};

		uint8_t* pixel_data;

		int width,
			height,
			bytes_per_pixel;

		if (!get_system_font_path(/*"Verdana (TrueType)"*//*"Segoe UI (TrueType)"*//*"Calibri"*/"Tahoma", font_path)) return;

		auto font = _fonts.AddFontFromFileTTF(font_path.data(), 14.0f, 0, _fonts.GetGlyphRangesDefault());

		_fonts.GetTexDataAsRGBA32(&pixel_data, &width, &height, &bytes_per_pixel);
		//printf("bytes_per_pixel: %d\n", bytes_per_pixel);

		auto hr = pDevice->CreateTexture(
			width, height,
			1,
			D3DUSAGE_DYNAMIC,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&_texture,
			NULL);

		if (FAILED(hr)) return;

		D3DLOCKED_RECT tex_locked_rect;
		if (_texture->LockRect(0, &tex_locked_rect, NULL, 0) != D3D_OK)
			return;
		for (int y = 0; y < height; y++)
			memcpy((uint8_t*)tex_locked_rect.pBits + tex_locked_rect.Pitch * y, pixel_data + (width * bytes_per_pixel) * y, (width * bytes_per_pixel));
		_texture->UnlockRect(0);

		_fonts.TexID = _texture;
	}

	void __stdcall InvalidateObjects()
	{
		if (_texture) _texture->Release();
		_texture = nullptr;

		_fonts.Clear();

		if (_drawList)
			delete _drawList;
		_drawList = nullptr;
	}

	void __stdcall GUI_Init(IDirect3DDevice9* pDevice)
	{
		ImGui_ImplDX9_Init(g_hWnd, pDevice);

		/*std::string font_path;
		if (get_system_font_path("Tahoma", font_path))
		{
		ImFontConfig config;
		//strcpy(config.Name, "Cyrillic");
		auto font = ImGui::GetIO().Fonts->AddFontFromFileTTF(font_path.data(), 15.0f, &config, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
		}*/

		//ImGui::GetIO().FontGlobalScale = 0.7f;
		//ImGui::GetCurrentContext()->FontSize = 14.f;

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowPadding = ImVec2(15, 15);
		style.WindowRounding = 8.0f;
		style.FramePadding = ImVec2(8, 8);
		style.FrameRounding = 4.0f;
		style.ItemSpacing = ImVec2(12, 8);
		style.ItemInnerSpacing = ImVec2(8, 6);
		style.IndentSpacing = 25.0f;
		style.ScrollbarSize = 15.0f;
		style.ScrollbarRounding = 9.0f;
		style.GrabMinSize = 5.0f;
		style.GrabRounding = 3.0f;
		style.CurveTessellationTol = 1.25f;
		style.Colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.15f, 0.15f, 0.80f); //main quarter
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.15f, 0.15f, 0.15f, 0.80f); //main quarter
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.15f, 0.15f, 0.15f, 0.80f); //main quarter
		style.Colors[ImGuiCol_TabSelected] = ImVec4(1.00f, 0.30f, 0.10f, 0.40f); //main colored
		style.Colors[ImGuiCol_TabText] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f); //white
		style.Colors[ImGuiCol_TabTextActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f); //white
		style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f); //white
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.85f, 0.85f, 0.85f, 0.85f); //main quarter
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.70f); //main quarter
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.07f, 0.60f); //main bg
		style.Colors[ImGuiCol_Border] = ImVec4(0.14f, 0.16f, 0.19f, 0.60f); //main border
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f); //dark
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f); //main bg
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(1.00f, 0.30f, 0.10f, 0.50f); //main colored
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(1.00f, 0.30f, 0.10f, 1.00f); //main colored
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f); //main bg
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.20f, 0.24f, 0.28f, 0.75f); //collapsed
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f); //main bg
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.11f, 0.11f, 0.11f, 0.70f); //main bg
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f); //main bg
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f); //main half
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.50f, 0.50f, 0.50f, 0.70f); //main half
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.00f, 0.30f, 0.10f, 1.00f); //main colored
		style.Colors[ImGuiCol_ComboBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f); //main bg
		style.Colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.30f, 0.10f, 1.00f); //main colored
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f); //main half
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.30f, 0.10f, 1.00f); //main colored
		style.Colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f); //main
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f); //main
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(1.00f, 0.30f, 0.10f, 1.00f); //main colored
		style.Colors[ImGuiCol_Header] = ImVec4(1.00f, 0.30f, 0.10f, 1.00f); //main colored
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f); //main
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f); //main
		style.Colors[ImGuiCol_Column] = ImVec4(0.14f, 0.16f, 0.19f, 1.00f); //main border
		style.Colors[ImGuiCol_ColumnHovered] = ImVec4(1.00f, 0.30f, 0.10f, 0.50f); //main colored
		style.Colors[ImGuiCol_ColumnActive] = ImVec4(1.00f, 0.30f, 0.10f, 1.00f); //main colored
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.90f, 0.90f, 0.90f, 0.75f); //main white
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f); //main white
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f); //main white
		style.Colors[ImGuiCol_CloseButton] = ImVec4(0.86f, 0.93f, 0.89f, 0.00f); //dark
		style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.86f, 0.93f, 0.89f, 0.40f); //close button
		style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.86f, 0.93f, 0.89f, 0.90f); //close button
		style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.30f, 0.10f, 1.00f); //main colored
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.30f, 0.10f, 0.50f); //main colored
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.30f, 0.10f, 1.00f); //main colored
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.30f, 0.10f, 0.50f); //main colored
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 0.30f, 0.10f, 1.00f); //main colored
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.07f, 0.70f); //main bg
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.24f, 0.28f, 0.60f); //c
		style.Colors[ImGuiCol_Tab] = ImVec4(1.0f, 0.20f, 0.30f, 1.00f);//цвет таба
		style.Colors[ImGuiCol_TabActive] = ImVec4(1.0f, 0.60f, 0.50f, 1.0f); // цвет при нажатии
		style.Colors[ImGuiCol_TabHovered] = ImVec4(1.0f, 0.50f, 0.40f, 1.0f);//цвет при наведении
		style.Colors[ImGuiCol_TabSelected] = ImVec4(1.0f, 0.20f, 0.40f, 1.0f);//цвет актив
		style.Colors[ImGuiCol_TabText] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		style.Colors[ImGuiCol_TabTextActive] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		CreateObjects(pDevice);

		G::Inited = true;
	}

	void __stdcall PreRender(IDirect3DDevice9* device)
	{
		if (!G::Inited)
			GUI_Init(device);

		ImGui_ImplDX9_NewFrame();
		_drawData.Valid = false;
		_drawList->Clear();
		_drawList->PushClipRectFullScreen();
	}

	void __stdcall PostRender(IDirect3DDevice9* deivce)
	{
		if (!_drawList->VtxBuffer.empty()) {
			_drawData.Valid = true;
			_drawData.CmdLists = &_drawList;
			_drawData.CmdListsCount = 1;
			_drawData.TotalVtxCount = _drawList->VtxBuffer.Size;
			_drawData.TotalIdxCount = _drawList->IdxBuffer.Size;
		}

		ImGui_ImplDX9_RenderDrawLists(&_drawData);
		ImGui::Render();
	}

	long __stdcall Present(IDirect3DDevice9* device, const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion)
	{
		PreRender(device);

		// Rendering

		Interface.Engine->GetScreenSize(screenWidth, screenHeight);
		CMenu::Render();
		CVisuals::Render();

		// End rendering

		PostRender(device);

		return O::Present(device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	}

	long __stdcall Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
	{
		if (!G::Inited || H::isEjecting)
			return O::Reset(pDevice, pPresentationParameters);

		ImGui_ImplDX9_InvalidateDeviceObjects();
		InvalidateObjects();

		auto hr = O::Reset(pDevice, pPresentationParameters);

		CreateObjects(pDevice);
		ImGui_ImplDX9_CreateDeviceObjects();

		return hr;
	}
};