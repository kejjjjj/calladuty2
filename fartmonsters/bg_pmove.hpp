#pragma once

#ifndef bgpmove
#define bgpmove

namespace cg
{
	inline void(*Pmove_f)(pmove_t* pm);
	void Pmove(pmove_t* pm);

	inline pmove_t* _pm;

}

#endif