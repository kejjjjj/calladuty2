
#include "pch.h"


void __cdecl r::CG_DrawActive()
{
	if (GetAsyncKeyState(VK_HOME) & 1) {
		dvar_s* r_fullscreen = Dvar_FindMalleableVar("r_fullscreen");

		if (r_fullscreen) {
			r_fullscreen->flags = (dvar_flags)0;
			Com_Printf(0, "^2Epic dvar success\n");

		}
		else
			Com_Printf(0, "^1Epic dvar failure\n");
	}

	return CG_DrawActive_f();
}