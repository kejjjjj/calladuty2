#pragma once

#ifndef cgoffsets
#define cgoffsets

#include "pch.h"
inline DWORD gfx_d3d_mp_x86_s = (DWORD)GetModuleHandleA("gfx_d3d_mp_x86_s.dll");
namespace cg
{
	inline DxGlobals* dx = reinterpret_cast<DxGlobals*>(gfx_d3d_mp_x86_s + 0x1D1BF4);
	inline playerState_s* ps_loc = reinterpret_cast<playerState_s*>(0x01513C44);
	inline clientActive_t* clients = reinterpret_cast<clientActive_t*>(0x98FDD4);
	inline playerState_s* cg = reinterpret_cast<playerState_s*>(0x1513C44);
	inline DWORD* WeaponNames = reinterpret_cast<DWORD*>(0x1728200);
	inline cgs_t* cgs = reinterpret_cast<cgs_t*>(0x1513C34);
}


#endif // !cgoffsets
