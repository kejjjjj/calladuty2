#include "pch.h"

cg::Font_s* r::R_RegisterFont(const char* _name, int _length)
{
	static const DWORD R_RegisterFont_F = (gfx_d3d_mp_x86_s + 0xBD00);
	cg::Font_s* returnval = nullptr;
	_length = sizeof(_name);
	__asm
	{
		push _length;
		push _name;
		call R_RegisterFont_F;
		add esp, 0x8;
		mov returnval, eax;
	}
	return returnval;
}
void r::R_AddCmdDrawText(char* text, int maxChars, void* font, float x, float y, float xScale, float yScale, float* color, int style)
{
	static const DWORD R_AddCmdDrawText_F = (gfx_d3d_mp_x86_s + 0xC030);
	__asm
	{
		//add esp, 1Ch;
		push style;
		lea ecx, color;
		push ecx;
		mov edx, yScale;
		push edx;
		mov eax, xScale;
		push eax;
		mov ecx, y;
		push ecx;
		mov edx, x;
		push edx;
		mov esi, font;
		push esi;		
		mov eax, maxChars;
		push eax;
		mov ecx, text;
		push ecx;
		call R_AddCmdDrawText_F;
		add esp, 32;
	}
	return;
	//return ((void(*)(char* text, int maxChars, void* font, float x, float y, float xScale, float yScale, float* color, int style))R_AddCmdDrawText_F)(text, maxChars, font, x, y, xScale, yScale, (float*)0x59D038, style);

	//0x0068A2E0 
}
float r::X(float pos)
{
	const float x = (float)1920;
	return pos <= 1920 ? pos / (1920.f / x) : pos * (x / 1920);

}
float r::Y(float pos)
{
	const float y = (float)1080;
	return pos <= 1080 ? pos / (1080.f / y) : pos * (y / 1080);
}