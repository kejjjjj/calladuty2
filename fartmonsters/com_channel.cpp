#include "pch.h"

void Com_Printf(int channel, const char* msg, ...)
{
	char Buffer[4096]; // [esp+0h] [ebp-1000h] BYREF
	va_list ArgList; // [esp+1008h] [ebp+8h] BYREF

	va_start(ArgList, msg);
	_vsnprintf_s(Buffer, 0x1000u, msg, ArgList);
	Buffer[4095] = 0;

	return ((void(__cdecl*)(int channel, char* buffer))0x431D10)(channel, Buffer);
}