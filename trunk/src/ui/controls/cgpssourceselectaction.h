#ifndef CGPSSOURCESELECTACTION_H
#define CGPSSOURCESELECTACTION_H

#include <QAction>
#include "cgpssource.h"
#include "cgpsinterface.h"
namespace ui
{
namespace controls
{

class CGpsSourceSelectAction : public QAction, public gps::CGpsInterface
{
    Q_OBJECT
public: // ####################################################
    CGpsSourceSelectAction(gps::CGpsSource *src, QObject *parent);
    ~CGpsSourceSelectAction();

private slots: // ####################################################
    void emitSelected();

signals: // ####################################################
    void selected(const gps::TGpsSourceId & id);
};

}
}
#endif // CGPSSOURCESELECTACTION_H
