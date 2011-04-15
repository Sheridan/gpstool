#ifndef CGPSSOURCESELECT_H
#define CGPSSOURCESELECT_H

#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <QMap>
#include "cgpssourceselectaction.h"

namespace ui
{
namespace controls
{

class CGpsSourceSelect : public QToolButton
{
    Q_OBJECT
public: // ####################################################
    CGpsSourceSelect(QWidget *parent = 0);
    ~CGpsSourceSelect();
    bool isEmpty();
    const gps::TGpsSourceId &selectedId() const { return m_selectedId; }

private: // ####################################################
    QMenu                                             * m_menu      ;
    QMap<gps::TGpsSourceId, CGpsSourceSelectAction *>   m_gpsActions;
    gps::TGpsSourceId                                   m_selectedId;

private slots: // ####################################################
    void appendGpsSource(const gps::TGpsSourceId &id);
    void removeGpsSource(const gps::TGpsSourceId &id);
    void updateSelected (const gps::TGpsSourceId &id);
    void setSelected    (const gps::TGpsSourceId &id);

signals: // ####################################################
    void selected       (const gps::TGpsSourceId & id);
};

}
}
#endif // CGPSSOURCESELECT_H
