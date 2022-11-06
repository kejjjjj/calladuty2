#include "pch.h"


dvar_s* Dvar_FindMalleableVar(const char* name)
{
	return ((dvar_s * (__cdecl*)(char* name))0x4373A0)((char*)name);
}