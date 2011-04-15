#ifndef CGPSINFOITEM_H
#define CGPSINFOITEM_H
#include <QObject>
#include <QGraphicsScene>
#include <QList>
#include "cclient.h"
#include "cgpsdata.h"
#include "cgpssource.h"
#include "coptionint.h"
#include "cid.h"
#include "cgpsdataupdateinterface.h"

namespace ui
{
namespace graphics
{

enum EGpsInfoItemType
{
    giitUnknown,
    giitText
};

class CGpsInfoItem : public tools::CId, public gps::CGpsDataUpdateInterface
{

public: // ####################################################
    CGpsInfoItem(gps::CGpsSource *gpssrc, tools::TId iid = 0);
    virtual ~CGpsInfoItem();
    virtual EGpsInfoItemType infoType() = 0;
    void load(const QString & section);
    void save(const QString & section);
    virtual ui::graphics::primitive::window::CClient *windowClient() = 0;

protected: // ####################################################
    virtual void loadFromConfig(const QString & section) = 0;
    virtual void saveToConfig  (const QString & section) = 0;

};

typedef QList<CGpsInfoItem *> TGpsInfoItems;

}
}
#endif // CGPSINFOITEM_H
