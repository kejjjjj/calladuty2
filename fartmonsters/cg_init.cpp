#include "pch.h"

void cg::CG_PatchBytes()
{
	hook* a = nullptr;



}
void cg::CG_Init()
{
	Com_Printf(0, "^2project has been loaded into the game!\n");
	//Com_Printf(1, "^1where is this printed");

	
	CG_PrepareHooks();
	CG_AddHooks();

	Dvar_RegisterBool("kej_strafebot", 0, 1);
	Dvar_RegisterBool("kej_strafebot_ground", 0, 1);
//	Dvar_RegisterBool("kej_strafebot_op", 0, 1);
	Dvar_RegisterBool("kej_supersprint", 0, 1);

	r::R_Init();
}
void cg::CG_PrepareHooks()
{
	Pmove_f						= (void(*)(pmove_t*))		(0x51AF70);
	r::CG_DrawActive_f			= (void(*)())				(0x4CBE50);
	r::R_RecoverLostDevice_f	= (char(__stdcall*)())		(gfx_d3d_mp_x86_s + 0x13960);
}
void cg::CG_AddHooks()
{
	hook* a = nullptr;

	a->install(&(PVOID&)Pmove_f, Pmove);
	a->install(&(PVOID&)r::CG_DrawActive_f, r::CG_DrawActive);
	a->install(&(PVOID&)r::R_RecoverLostDevice_f, r::R_RecoverLostDevice);
}
void cg::CG_RemoveHooks()
{
	hook* a = nullptr;

	a->remove(&(PVOID&)Pmove_f, Pmove);
	a->remove(&(PVOID&)r::CG_DrawActive_f, r::CG_DrawActive);
	a->remove(&(PVOID&)r::R_RecoverLostDevice_f, r::R_RecoverLostDevice);
	//a->remove(&(PVOID&)r::R_CreateWindow_f, r::R_CreateWindow);

}