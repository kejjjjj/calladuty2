#pragma once

#ifndef rinit
#define rinit

#include "pch.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace r
{
	inline DWORD WndProcAddr;

	bool R_Init();
	bool R_ImGui(IDirect3DDevice9* pDevice);
	typedef HRESULT(__stdcall* endScene)(IDirect3DDevice9* pDevice);
	inline endScene pEndScene;

	HRESULT __stdcall draw_func(IDirect3DDevice9* pDevice);


	inline void(__cdecl* CG_DrawActive_f)();
	void __cdecl CG_DrawActive();


	LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	inline LRESULT(__stdcall* oWndProc)(HWND, UINT, WPARAM, LPARAM);

	inline void (*R_CreateWindow_f)();
	void R_CreateWindow();

	inline char(__stdcall* R_RecoverLostDevice_f)();
	char R_RecoverLostDevice();



}

#endif