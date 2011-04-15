#ifndef CMODE_H
#define CMODE_H
#include "defines.h"
#include "cvalidatedvalue.h"

namespace data
{
    enum EMode
    {
        emNoset = 0,
        emNoFix = 1,
        em2DFix = 2,
        em3Dfix = 3
    };
    typedef CValidatedVariable<EMode> TValidatedMode;
}
#endif // CMODE_H
