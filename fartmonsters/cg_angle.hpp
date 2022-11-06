#pragma once

#ifndef cgang
#define cgang

#include "pch.h"

namespace cg
{
	
	struct range_t
	{
		float x1;
		float x2;
		bool split;
	};
	float ProjectionX(float angle, float fov, int projType = 1);
	range_t AnglesToRange(float start, float end, float yaw, float fov, int projType = 1);
	//screencoordinates_t CG_RangeAnglesToSC(range_t range);
	void CG_FillAngleYaw(float start, float end, float yaw, float y, float h, float fov, const vec4_t color, bool isCylindrical = false);

	void setYaw(float ref, float ang);
	void setPitch(float ref, float ang);
	void setRoll(float ref, float ang);
	void CG_SetPlayerAngles(vec3_t source, vec3_t target);
	float CG_GetOptAngle(float& delta, bool all_techs = false);
	float R_GetOptAngle(const bool rightmove, float& delta);

}

#endif