#ifndef CGRAPHICSVIEW_H
#define CGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QResizeEvent>
#include <QMenu>

namespace ui
{
namespace graphics
{

class CGraphicsView : public QGraphicsView
{
Q_OBJECT
public: // ####################################################
    CGraphicsView(QWidget * parent);
    ~CGraphicsView();

private: // ####################################################
    QMenu *m_menu;
    void contextMenuEvent(QContextMenuEvent * event);

private slots: // ####################################################
    void addTextItemShowDialog();
};

}
}
#endif
