#pragma once

#ifndef modvis
#define modvis

#include "pch.h"

namespace cg
{
	void FPS_CalculateSingleBeatDirection(bool& rightmove, const usercmd_s* cmd);
	void Mod_GetAccelerationAngles(const bool rightmove, vec2_t accel_angles);
	void Mod_DrawAngleHelper();
	void Mod_DrawVelocity();

}

#endif