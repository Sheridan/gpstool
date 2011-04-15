#ifndef CSAtellITESVIEW_H
#define CSAtellITESVIEW_H

#include "cgraphicsview.h"
#include "csatellitesscene.h"
namespace ui
{
namespace graphics
{

class CSatellitesView : public CGraphicsView
{
    Q_OBJECT
private: // ####################################################
    CSatellitesScene * m_scene;
    void resizeEvent(QResizeEvent * event);
public: // ####################################################
    CSatellitesView(QWidget * parent = NULL);
    virtual ~CSatellitesView();
    CSatellitesScene * scene() { return m_scene; };
};

}
}
#endif
