#ifndef CMAPVIEW_H
#define CMAPVIEW_H

#include "cgraphicsview.h"
#include "cmapscene.h"
namespace ui
{
namespace graphics
{

class CMapView : public CGraphicsView
{
public: // ####################################################
    CMapView(QWidget * parent = NULL);
    virtual ~CMapView();
private: // ####################################################
    CMapScene * m_scene;
};

}
}
#endif
