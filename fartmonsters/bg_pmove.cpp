#include "pch.h"


void cg::Pmove(pmove_t* pm)
{
    pmove_t* _pm; // edi
    playerState_s* ps; // ebp //0x01513c44
    int _finalTime; // ebx
    int result; // eax
    int msec; // eax

    _pm = pm;
    ps = pm->ps;
    _finalTime = pm->cmd.serverTime;
    result = pm->ps->commandTime;
    if (_finalTime >= result)
    {
        result += 1000;
        if (_finalTime > result)
        {
            result = _finalTime - 1000;
            ps->commandTime = _finalTime - 1000;
        }
        pm->numtouch = 0;
        if (ps->commandTime != _finalTime)
        {
            while (1)
            {
                msec = _finalTime - ps->commandTime;
                if (msec > 66)
                    msec = 66;
                _pm->cmd.serverTime = msec + ps->commandTime;
                ((void(*)(pmove_t*))0x51A7A0)(_pm); //PmoveSingle
                memcpy(&_pm->oldcmd, &_pm->cmd, sizeof(_pm->oldcmd));
                result = ps->commandTime;
                if (ps->commandTime == _finalTime)
                    break;
                _pm = pm;
                cg::_pm = pm;
            }
        }
    }
    return;
}
