#include "pch.h"


dvar_s* Dvar_FindMalleableVar(const char* name)
{
	return ((dvar_s * (__cdecl*)(char* name))0x4373A0)((char*)name);
}
dvar_s* Dvar_RegisterBool(const char* name, int type, int flags)
{
	return ((dvar_s * (__cdecl*)(const char* name, int type, int flags))0x438040)(name, type, flags);
}