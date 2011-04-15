#ifndef COPTIONSWINDOWITEMS_H
#define COPTIONSWINDOWITEMS_H
#include "coptions.h"
#include "coptionsapplication.h"
namespace options
{

class COptionsWindowItems : public COptions
{
public: // ####################################################
    COptionsWindowItems(COptionsApplication *appOptions);
    ~COptionsWindowItems();
};

}
#endif // COPTIONSWINDOWITEMS_H
