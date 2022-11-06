
#include "pch.h"
using namespace cg;
HRESULT __stdcall r::draw_func(IDirect3DDevice9* pDevice)
{

	if (!R_ImGui(pDevice)) {
		fs::Log_Write(LOG_FATAL, "Unable to initialize imgui\n");
	}
	if (R_OpenMenu(pDevice) && cg::_pm) {

		if (cg::_pm->ps) {

			//Mod_DrawAngleHelper();
			Mod_DrawVelocity();
		}
		R_EndRender();


	}

	return pEndScene(pDevice);
}
void clientActive(clientActive_t* _clients)
{
	if (!_clients)
		return;

	usercmd_s* cmd = _clients->GetUserCmd(_clients->cmdNumber-1);

	if (!cmd)
		return;

	if (GetAsyncKeyState(VK_HOME) & 1) {
		Com_Printf(CON_CHANNEL_OBITUARY, "cmd[%i]: (0x%p)\n", 0, &_clients->cmds[0]);
		Com_Printf(CON_CHANNEL_OBITUARY, "cmd->serverTime: %i\n", 0, cmd->serverTime);

		Com_Printf(CON_CHANNEL_OBITUARY, "cmds stop at (0x%p)\n", (&_clients->cmdNumber));
	}
}
void __cdecl r::CG_DrawActive()
{

	//cg::Font_s* font = R_RegisterFont("fonts/bigDevFont", 3);


	//if (font) {
	//	if (GetAsyncKeyState(VK_HOME) & 1) 
	//		Com_Printf(1, "^2Epic font (0x%p) success\n", font);
	//	R_AddCmdDrawText((char*)"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 0x7FFFFFFF, font, 960, 700, 3, 3, vec4_t{ 1,1,1,1 }, 0);

	//}
	clientActive(clients);
	cg::Mod_Strafebot();
	return CG_DrawActive_f();
}