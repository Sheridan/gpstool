#ifndef CTEXTVIEW_H
#define CTEXTVIEW_H
#include "cgraphicsview.h"
#include "ctextscene.h"
#include <QMenu>
#include <QHash>

namespace ui
{
namespace graphics
{

class CTextView : public CGraphicsView
{
Q_OBJECT
public: // ####################################################
    CTextView(QWidget * parent = NULL);
    ~CTextView();
private: // ####################################################
    CTextScene * m_scene;
    void resizeEvent(QResizeEvent * event);
};

}
}
#endif // CTEXTVIEW_H
