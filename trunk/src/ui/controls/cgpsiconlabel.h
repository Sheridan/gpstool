#ifndef CGPSICONLABEL_H
#define CGPSICONLABEL_H
#include "ciconlabel.h"
#include "cgpssource.h"
#include "coptionicon.h"
#include "cgpsinterface.h"
namespace ui
{
namespace controls
{

    class CGpsIconLabel : public CIconLabel, public gps::CGpsInterface
{
    Q_OBJECT
public: // ####################################################
    CGpsIconLabel(gps::CGpsSource * src, QWidget * parent);
    CGpsIconLabel(QWidget * parent);
    void connectGps(gps::CGpsSource * src);
private slots: // ####################################################
    void setConnected();
    void setDisconnected();
    void setUsable();
    void setUnusable();
    void setError();
    void setStatusChanging();
    void setBeginUpdate();
    void setEndUpdate();
    void iconUpdated();
private: // ####################################################
    void connectGps();
    options::COptionIcon *m_icon;
};

}
}
#endif // CGPSICONLABEL_H
