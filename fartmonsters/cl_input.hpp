#pragma once

#ifndef clinput
#define clinput

#include "pch.h"

namespace cg
{
	void CL_SetServerAngles(vec3_t dst);
	usercmd_s* CL_GetUserCmd(int cmdNumber);
}

#endif