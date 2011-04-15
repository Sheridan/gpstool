#ifndef GPSDEFINES_H
#define GPSDEFINES_H
#include <QtGlobal>
#include "cid.h"

namespace gps
{

typedef tools::TId TGpsSourceId;

}

//#define GT_GPS_SRC_ID_TO_VARIANT(_srcid)      QVariant(static_cast<uint>(_srcid))
//#define GT_GPS_SRC_ID_FROM_VARIANT(_srcidvar) _srcidvar.value<uint>();

#endif // GPSDEFINES_H
