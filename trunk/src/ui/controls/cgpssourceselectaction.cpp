#include "cgpssourceselectaction.h"
#include "st.h"
namespace ui
{
namespace controls
{
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsSourceSelectAction::CGpsSourceSelectAction(gps::CGpsSource *src, QObject *parent) : QAction(src->name(), parent), gps::CGpsInterface(src)
{
    connect(gps(), SIGNAL(connected(bool)), this, SLOT(setEnabled(bool)));
    connect(this , SIGNAL(triggered())    , this, SLOT(emitSelected())  );
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGpsSourceSelectAction::~CGpsSourceSelectAction()
{
    disconnect(this);
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGpsSourceSelectAction::emitSelected()
{
    emit selected(gps()->id());
}

}
}
