
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
	if (GetAsyncKeyState(VK_HOME) & 1) {

		//usercmd_s* cmd = _clients->GetUserCmd(_clients->cmdNumber-1);

		//usercmd_s* cmd = (usercmd_s*)(0x9CFE2C + 28 * ((_clients->cmdNumber - 1) & 0x7F));


		//if (!cmd) {
		//	Com_Printf(CON_CHANNEL_OBITUARY, "^1epic cmd failure\n");

		//	return;
		//}

		//Com_Printf(CON_CHANNEL_OBITUARY, "^1&cmdNumber: (0x%p)\n", &_clients->cmdNumber);


		//Com_Printf(CON_CHANNEL_OBITUARY, "cmd[%i]: (0x%p)\n", (_clients->cmdNumber - 1) & 0x7F, cmd);
		//Com_Printf(CON_CHANNEL_OBITUARY, "cmd->serverTime: %i\n", cmd->serverTime);

		//Com_Printf(CON_CHANNEL_OBITUARY, "cmd->forwardmove: %i\n", cmd->forwardmove);
	}
	//setRoll(cg::cg->viewangles[ROLL], cg::cg->viewangles[ROLL] == NULL ? 90 : 0);

	usercmd_s* cmd = CL_GetUserCmd(clients->cmdNumber - 1);
	dvar_s* kej_supersprint = Dvar_FindMalleableVar("kej_supersprint");
	if (!cmd || !kej_supersprint)
		return;
	
	if(cg::cg->groundEntityNum == 1022 && kej_supersprint->current.enabled && (cmd->forwardmove > 0 && cmd->rightmove != 0))
		cg::CL_SetServerAngles(vec3_t{ 85,cg::cg->viewangles[YAW], cmd->rightmove > 0 ? -90.f : 90.f});
}
void __cdecl r::CG_DrawActive()
{

	//cg::Font_s* font = R_RegisterFont("fonts/bigDevFont", 3);


	//if (font) {
	//	if (GetAsyncKeyState(VK_HOME) & 1) 
	//		Com_Printf(1, "^2Epic font (0x%p) success\n", font);
	//	R_AddCmdDrawText((char*)"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 0x7FFFFFFF, font, 960, 700, 3, 3, vec4_t{ 1,1,1,1 }, 0);

	//}
	//if (GetAsyncKeyState(VK_HOME) & 1) {
	//	DWORD weap = cg::WeaponNames[cg::cg->weapon];
	//	if (weap) {
	//		DWORD _speedScale = (weap + 0x264);
	//		Com_Printf(CON_CHANNEL_OBITUARY, "^2_speedScale: (0x%p)\n", _speedScale);

	//		float moveSpeedScale = *(float*)(_speedScale);
	//		Com_Printf(CON_CHANNEL_OBITUARY, "^2moveSpeedScale: %.1f\n", moveSpeedScale);
	//	}
	//	else
	//		Com_Printf(CON_CHANNEL_OBITUARY, "^1epic weap failure\n");
	//}
	clientActive(clients);
	cg::Mod_Strafebot();
	return CG_DrawActive_f();
}