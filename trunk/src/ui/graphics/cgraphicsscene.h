#ifndef CGRAPHICSSCENE_H
#define CGRAPHICSSCENE_H

#include <QGraphicsScene>
#include "cgpsinfoitem.h"
#include "cwindow.h"

namespace ui
{
namespace graphics
{

class CGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public: // ####################################################
    CGraphicsScene(const QString &sceneName);
    virtual ~CGraphicsScene();
    void addGpsInfoItem(CGpsInfoItem *value);
    void removeGpsInfoItem(CGpsInfoItem *value, bool removeFromConfig);

private: // ####################################################
    void saveGpsInfoItems  ();
    void loadGpsInfoItems  ();
    void removeGpsInfoItems();
    TGpsInfoItems m_gpsInfoItems;
    ui::graphics::primitive::window::TWindowsMap m_windows;

private slots: // ####################################################
    void windowCloseRequest(ui::graphics::primitive::window::CWindow *wnd);
};

}
}
#endif
