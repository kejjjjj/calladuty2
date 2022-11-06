#pragma once

#ifndef drawtools
#define drawtools

#include "pch.h"
namespace r
{
	cg::Font_s* R_RegisterFont(const char* name, int length);
	void R_AddCmdDrawText(char* text, int maxChars, void* font, float x, float y, float xScale, float yScale, float* color, int style);

	float X(float pos);
	float Y(float pos);
}

#endif