#include "pch.h"

void cg::FPS_CalculateSingleBeatDirection(bool& rightmove, const usercmd_s* cmd)
{
	static uint16_t frames = NULL;
	static vec_t oldYaw = NULL;
	static bool _rightmove;
	vec_t newYaw = _pm->ps->viewangles[YAW];

	if (newYaw < 0) {
		newYaw += 180;
		newYaw = (newYaw + 180 % 360);
	}

	frames += 1;

	if (frames >= 4) {
		frames = 0;

		if (oldYaw < newYaw && cmd->forwardmove != 0 && cmd->rightmove == 0 && rightmove)
			_rightmove = false;
		else if (oldYaw > newYaw && cmd->forwardmove != 0 && cmd->rightmove == 0 && !rightmove)
			_rightmove = true;
		oldYaw = newYaw;
	}
	if (cmd->rightmove == 0)
		rightmove = _rightmove;
}
void cg::Mod_GetAccelerationAngles(const bool rightmove, vec2_t out)
{
	static float delta;
	const float yaw = _pm->ps->viewangles[YAW];
	float opt = R_GetOptAngle(rightmove, delta);

	if (rightmove)
		out[0] = opt;
	else out[1] = opt;

	//delta = (delta > 0) ? delta : -delta;

	const float maxAngle = 45.f - (delta);



	if (rightmove) {
		out[1] = out[0] - maxAngle;
	}
	else {
		out[0] = out[1] + maxAngle;

	}



}
void cg::Mod_DrawAngleHelper()
{

	float yaw = _pm->ps->viewangles[YAW];
	const dvar_s* cg_fov = Dvar_FindMalleableVar("cg_fov");
	const dvar_s* cg_fovscale = Dvar_FindMalleableVar("cg_fovscale");
	vec2_t accel_angles;

	static bool rightmove;

	const usercmd_s* cmd = &_pm->cmd;

	if (cmd->rightmove > 0)
		rightmove = true;
	else if (cmd->rightmove < 0)
		rightmove = false;

	FPS_CalculateSingleBeatDirection(rightmove, cmd);

	if (!cg_fov || !cg_fovscale)
		return;

	Mod_GetAccelerationAngles(rightmove, accel_angles);
	const float fov = (cg_fov->current.value * cg_fovscale->current.value);

	CG_FillAngleYaw(accel_angles[0], accel_angles[1], yaw, 500, 20, fov, vec4_t{ 255,0,0,0.7 }, false);


}
void cg::Mod_DrawVelocity()
{
	const float _speed = glm::length(glm::vec2(_pm->ps->velocity[1], _pm->ps->velocity[0]));
	char buff[14];
	sprintf_s(buff, "%i", (int)_speed);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(945, 500), IM_COL32(0, 255, 0, 255), buff);

}