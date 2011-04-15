#ifndef CDBICONLABEL_H
#define CDBICONLABEL_H

#include "ciconlabel.h"
#include "cdatabase.h"

namespace ui
{
namespace controls
{

class CDbIconLabel : public CIconLabel
{
    Q_OBJECT
public: // ####################################################
    CDbIconLabel(data::db::CDatabase *db, QWidget *parent);
private slots: // ####################################################
    void setDbRead();
    void setDbWrite();
    void setDisconnected();
    void setConnected();
};

}
}
#endif // CDBICONLABEL_H
