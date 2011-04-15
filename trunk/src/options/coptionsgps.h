#ifndef COPTIONSGPS_H
#define COPTIONSGPS_H
#include "coptions.h"
#include "coptionsapplication.h"

namespace options
{

class COptionsGps : public COptions
{
public: // ####################################################
    COptionsGps(COptionsApplication *appOptions);
    ~COptionsGps();
};

}
#endif // COPTIONSGPS_H
