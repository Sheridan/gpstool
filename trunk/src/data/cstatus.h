#ifndef CSTATUS_H
#define CSTATUS_H
#include "defines.h"
#include "cvalidatedvalue.h"

namespace data
{
    enum EStatus
    {
        esNoFix             = 0,
        esFix               = 1,
        esDGPSCorrectedFix  = 2
    };
    typedef CValidatedVariable<EStatus> TValidatedStatus;
}
#endif // CSTATUS_H
