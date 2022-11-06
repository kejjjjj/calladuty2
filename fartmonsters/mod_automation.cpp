#include "pch.h"

void cg::Mod_Strafebot()
{
	if (!_pm)
		return;
	if (!_pm->ps)
		return;
	if ((DWORD)_pm->ps < 0x1000)
		return;
	if (_pm->ps->pm_type == PM_UFO)
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

	const usercmd_s* cmd = &_pm->cmd;

	if (_pm->ps->groundEntityNum == 1022 && cmd->forwardmove < 0 || _pm->ps->groundEntityNum == 1022 && cmd->rightmove == 0)
		return;

	if (cmd->forwardmove != 0 || cmd->rightmove != 0) {
		setYaw(_pm->ps->viewangles[YAW], optYaw);

	}
	
}