#include "pch.h"
cg::range_t cg::AnglesToRange(float start, float end, float yaw, float fov, int projType)
{
	if (fabsf(end - start) > 2 * (float)M_PI)
	{
		range_t const ret = { 0, float(1920.f), false };
		return ret;
	}

	bool split = end > start;
	start = AngleNormalizePI(start - yaw);
	end = AngleNormalizePI(end - yaw);

	if (end > start)
	{
		split = !split;
		float const tmp = start;
		start = end;
		end = tmp;
	}

	range_t const ret = { ProjectionX(start, fov, projType), ProjectionX(end, fov, projType), split };
	return ret;
}
float cg::ProjectionX(float angle, float fov, int projType)
{
	float SCREEN_WIDTH = 1920.f;
	float const half_fov_x = (float)DEG2RAD(fov) / 2;
	if (angle >= half_fov_x)
	{
		return 0;
	}
	if (angle <= -half_fov_x)
	{
		return SCREEN_WIDTH;
	}
	switch (projType) {
	case 0:
		return SCREEN_WIDTH / 2 * (1 - tanf(angle) / tanf(half_fov_x));
		break;
	case 1:
		return SCREEN_WIDTH / 2 * (1 - angle / half_fov_x);
		break;
	case 2:
		return SCREEN_WIDTH / 2 * (1 - tanf(angle / 2) / tanf(half_fov_x / 2));
		break;

	default:
		return 0;
		break;

	}
}
void cg::CG_FillAngleYaw(float start, float end, float yaw, float y, float h, float fov, vec4_t const color, bool isCylindrical)
{

	range_t const range = AnglesToRange(DEG2RAD(start), DEG2RAD(end), DEG2RAD(yaw), fov);

	const float widthOffs = 0;
	const float minX = widthOffs;
	const float maxX = 1920.f - widthOffs;

	float x1 = range.x1 < minX ? minX : range.x1;
	float x2 = range.x2 - range.x1;


	x1 = range.x1 > maxX ? maxX : x1;
	x2 = range.x2 > maxX ? maxX - x1 : x2;


	if (!range.split) {
		//r::R_DrawRect("white", range.x1, y, range.x2 - range.x1, h, color);
		if (!isCylindrical) {
			ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(r::X(x1), r::Y(y)), ImVec2(r::X(ImClamp(range.x2, minX, maxX)), r::Y(y + h)), ImColor(color[0], color[1], color[2], 0.7f));
			return;
		}
		int const heightOffsetX1 = glm::distance((float)range.x1, r::X(960.f));
		int const heightOffsetX2 = glm::distance((float)range.x2, r::X(960.f));

		float midYAW = glm::distance(end, start) / 2;
		midYAW += start;
		range_t const midpoint = AnglesToRange(DEG2RAD(midYAW), DEG2RAD(midYAW), DEG2RAD(yaw), fov);

		int const heightOffsetMiddle = glm::distance((float)midpoint.x1, r::X(960.f));

		const ImVec2 a(range.x1, y + heightOffsetX1 / 2);
		const ImVec2 b(midpoint.x1, y + heightOffsetMiddle / 2);
		const ImVec2 c(range.x2, y + heightOffsetX2 / 2);

		ImGui::GetBackgroundDrawList()->AddBezierQuadratic(a, b, c, ImColor(color[0], color[1], color[2], color[3]), h);
		//ImGui::GetBackgroundDrawList()->AddText(ImVec2(range.x1, y), IM_COL32(255, 255, 255, 255), std::string(std::to_string(start)).c_str());
		//ImGui::GetBackgroundDrawList()->AddText(ImVec2(range.x2, y), IM_COL32(255, 255, 255, 255), std::string(std::to_string(end)).c_str());

		//float const val = midpoint.x1;

		//ImGui::GetBackgroundDrawList()->AddText(ImVec2(val, y), IM_COL32(255, 255, 255, 255), std::string(std::to_string(midYAW)).c_str());

	}
	else {
		if (!isCylindrical) {
			ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(r::X(minX), r::Y(y)), ImVec2(r::X(x1), r::Y(y + h)), ImColor(color[0], color[1], color[2], color[3]));
			ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(r::X(ImClamp(range.x2, minX, maxX)), r::Y(y)), ImVec2(r::X(ImClamp((float)1920, minX, maxX)), r::Y(y + h)), ImColor(color[0], color[1], color[2], color[3]));

		}
	}
}
void cg::setYaw(float ref, float ang)
{
	ref = fmodf(ref, 360);

	ref -= ref * 2 - ang;

	clients->viewangles[1] += ref;

}
void cg::setPitch(float ref, float ang)
{
	ref = fmodf(ref, 360);

	ref -= ref * 2 - ang;

	clients->viewangles[0] += ref;
}
void cg::setRoll(float ref, float ang)
{
	ref = fmodf(ref, 360);

	ref -= ref * 2 - ang;

	clients->viewangles[2] += ref;

}
void cg::CG_SetPlayerAngles(vec3_t source, vec3_t target)
{
	setPitch(source[0], target[0]);
	setYaw(source[1], target[1]);
	setRoll(source[2], target[2]);
}
float cg::R_GetOptAngle(const bool rightmove, float& diff)
{
	if (!_pm)
		return -400.f;

	usercmd_s* cmd = &_pm->oldcmd;

	char forwardmove = cmd->forwardmove;
	//char rightmove = cmd->rightmove;


	float _speed = glm::length(glm::vec2(_pm->ps->velocity[1], _pm->ps->velocity[0]));

	if (_speed < 1)
		return -400;


	float yaw = _pm->ps->viewangles[YAW];
	float g_speed = (float)_pm->ps->speed;
	const float FPS = (float)Dvar_FindMalleableVar("com_maxfps")->current.integer;

	float accel = FPS / g_speed;



	if (_speed < g_speed)
		g_speed = g_speed - (g_speed - _speed);

	const double velocitydirection = atan2(_pm->ps->velocity[1], _pm->ps->velocity[0]) * 180.f / PI;
	const double accelerationAng = atan2(-rightmove, forwardmove) * 180.f / PI;
	diff = acos((g_speed - accel) / _speed) * 180.f / PI;

	float delta = yaw;


	if (rightmove) {
		delta = (velocitydirection - diff - accelerationAng);
		//_opt = delta - yaw;
	}
	else {
		delta = (velocitydirection + diff - accelerationAng);
		//_opt = delta - yaw;
	}
	diff /= 2;
	yaw = delta;

	return yaw;
}
float cg::CG_GetOptAngle(float& _opt, bool all_techs)
{
	if (!_pm)
		return -400.f;

	usercmd_s* cmd = &_pm->cmd;

	char forwardmove = cmd->forwardmove;
	char rightmove = cmd->rightmove;


	float _speed = glm::length(glm::vec2(_pm->ps->velocity[1], _pm->ps->velocity[0]));

	if (_speed < 1 || !all_techs && forwardmove != 127 && rightmove != 0)
		return -400;

	if (all_techs)
		forwardmove = cmd->forwardmove;
	else forwardmove = 127;

	float yaw = _pm->ps->viewangles[YAW];
	float g_speed = (float)_pm->ps->speed;
	const float FPS = (float)Dvar_FindMalleableVar("com_maxfps")->current.integer;

	float accel = FPS / g_speed;

	if (FPS == 125) {
		accel = g_speed / FPS;
	}
	static float testspeed = 190.f;

	if (GetAsyncKeyState(VK_UP) & 1) {
		testspeed+=1;
		Com_Printf(CON_CHANNEL_OBITUARY, "^2%.1f", testspeed);
	}
	else if (GetAsyncKeyState(VK_DOWN) & 1) {
		testspeed -= 1;
		Com_Printf(CON_CHANNEL_OBITUARY, "^2%.1f", testspeed);
	}
	if (_pm->ps->groundEntityNum == 1022)
		g_speed = 186.f;
	//else if (_pm->ps->groundEntityNum == 1022)
	//	g_speed = 224.f;

	const double velocitydirection = atan2(_pm->ps->velocity[1], _pm->ps->velocity[0]) * 180.f / PI;
	const double accelerationAng = atan2(-rightmove, forwardmove) * 180.f / PI;
	double diff = acos((g_speed - accel) / _speed) * 180.f / PI;

	float delta = yaw;


	if (rightmove > 0 || WE && all_techs || SE && all_techs) {
		delta = (velocitydirection - diff - accelerationAng);
		_opt = delta - yaw;
	}
	else if (rightmove < 0 || WQ && all_techs || SQ && all_techs) {
		delta = (velocitydirection + diff - accelerationAng);
		_opt = delta - yaw;
	}
	yaw = delta;



	return yaw;
}