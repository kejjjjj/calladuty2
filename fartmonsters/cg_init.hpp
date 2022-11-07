#pragma once

#ifndef cginit
#define cginit

#include "pch.h"

namespace cg
{
	void CG_PatchBytes();
	void CG_Init();
	void CG_PrepareHooks();
	void CG_AddHooks();
	void CG_RemoveHooks();
}

#endif