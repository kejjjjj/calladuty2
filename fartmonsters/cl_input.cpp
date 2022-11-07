#include "pch.h"

void cg::CL_SetServerAngles(vec3_t dst)
{
	usercmd_s* cmd = CL_GetUserCmd(clients->cmdNumber - 1);

	if (!cmd)
		return;

	cmd->serverTime = cgs->oldTime + 1;

	float pitch = ANGLE2SHORT(cg->viewangles[PITCH]);
	float yaw = ANGLE2SHORT(cg->viewangles[YAW]);
	float roll = ANGLE2SHORT(cg->viewangles[ROLL]);

	yaw -= yaw * 2 - ANGLE2SHORT(dst[YAW]);
	pitch -= pitch * 2 - ANGLE2SHORT(dst[PITCH]);
	roll -= roll * 2 - ANGLE2SHORT(dst[ROLL]);

	cmd->angles[PITCH] += pitch;
	cmd->angles[YAW] += yaw;
	cmd->angles[ROLL] += roll;

}
cg::usercmd_s* cg::CL_GetUserCmd(int cmdNumber)
{
	return (usercmd_s*)(0x9CFE2C + 28 * ((cmdNumber) & 0x7F));
}