#include "pch.h"

bool r::R_Init()
{
	if (!cg::dx->device) {
		fs::Log_Write(LOG_FATAL, "cg::dx->device is a nullpointer!\n");
		return false;
	}

	PVOID* vTable = *reinterpret_cast<PVOID**>(cg::dx->device);

	if (!vTable)
		return false;

	hook a;

	pEndScene = (endScene)vTable[42];

	if (!pEndScene)
		return false;

	if (a.install(&(PVOID&)pEndScene, draw_func) != S_OK) {
		Com_Printf(CON_CHANNEL_CONSOLEONLY, "failed to hook endscene\n");
		return false;
	}
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "renderer successfully hooked\n");

	return true;
}
bool r::R_ImGui(IDirect3DDevice9* pDevice)
{
	if (ImGui::GetCurrentContext())
		return true;

	std::cout << "creating new imgui context!\n";
	Com_Printf(CON_CHANNEL_CONSOLEONLY, "creating new imgui context!\n");

	ImGui::CreateContext();

	const char* window_name = "Call Of Duty 2 Multiplayer";

	if (!ImGui_ImplWin32_Init(FindWindowA(NULL, window_name))) {
		fs::Log_Write(LOG_FATAL, "ImGui_ImplWin32_Init(%s) return false\n", window_name);
		return false;
	}

	if (!ImGui_ImplDX9_Init(pDevice)) {
		fs::Log_Write(LOG_FATAL, "ImGui_ImplDX9_Init() return false.. possibly null directx device\n");
		return false;
	}

}
char r::R_RecoverLostDevice()
{
	if (ImGui::GetCurrentContext()) {
		ImGui_ImplDX9_InvalidateDeviceObjects();
		fs::Log_Write(LOG_NONE, "resetting imgui context");
	}
	return R_RecoverLostDevice_f();
}