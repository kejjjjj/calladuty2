#pragma once

#ifndef rinit
#define rinit

#include "pch.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace r
{
	bool R_Init();
	inline void(__cdecl* CG_DrawActive_f)();
	void __cdecl CG_DrawActive();



}

#endif