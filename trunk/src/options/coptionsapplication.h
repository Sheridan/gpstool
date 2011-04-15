#ifndef COPTIONSAPPLICATION_H
#define COPTIONSAPPLICATION_H
#include "coptions.h"
#include "sdialogstate.h"
namespace options
{

class COptionsApplication : public COptions
{
public: // ####################################################
    COptionsApplication();
    ~COptionsApplication();

    SDialogState getDialogState(const QString & name);
    void setDialogState(const QString & name, const SDialogState state);
};

}
#endif // COPTIONSAPPLICATION_H
