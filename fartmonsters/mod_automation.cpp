#include "pch.h"

void cg::Mod_Strafebot()
{
	const dvar_s* strafebot = Dvar_FindMalleableVar("kej_strafebot");
	if (cg->pm_type == PM_UFO || !strafebot)
		return;

	if (!strafebot->current.enabled)
		return;

	float optYaw, test;

	//static DWORD old_ms = Sys_Milliseconds();
	//DWORD ms = Sys_Milliseconds();

	if (std::isnan(clients->viewangles[YAW]))
		clients->viewangles[YAW] = 0;
	else if (clients->viewangles[YAW] > 3000 || clients->viewangles[YAW] < -3000)
		clients->viewangles[YAW] = fmodf(clients->viewangles[YAW], 360);

	optYaw = CG_GetOptAngle(test, false);
	if (optYaw == -400.f || std::isnan(optYaw))
		return;

	//const usercmd_s* cmd = &_pm->cmd;
	const usercmd_s* cmd = CL_GetUserCmd(clients->cmdNumber - 1);
	if (!cmd)
		return;

	if (cg->groundEntityNum == 1022 && cmd->forwardmove < 0 || cg->groundEntityNum == 1022 && cmd->rightmove == 0)
		return;

	if (cmd->forwardmove != 0 || cmd->rightmove != 0) {
		setYaw(cg->viewangles[YAW], optYaw);

		//if (cg->groundEntityNum == 1023) {
		//	//cg::CL_SetServerAngles(vec3_t{ cg->viewangles[PITCH] ,cg->viewangles[YAW], cmd->rightmove > 0 ? -45.f : 45.f});
		//	setRoll(cg->viewangles[ROLL], cmd->rightmove > 0 ? 45.f : -45.f);
		//}
		

	}
	
}