#include "ciconselect.h"
#include <QFileDialog>

namespace ui
{
namespace controls
{
// --------------------------------------------------------------------------------------------------------------------------------------
CIconSelect::CIconSelect(QWidget *parent) : QToolButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(selectIcon()));
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CIconSelect::selectIcon()
{
    QFileDialog dlg;
    dlg.setWindowTitle(tr("Open database file"));
    dlg.setDirectory(QDir::homePath());
    dlg.setFilter(tr("Images (*.png *.xpm *.jpg *.bmp)"));

    if(dlg.exec() == QDialog::Accepted && dlg.selectedFiles().count() > 0)
    {
        setIcon(QIcon(dlg.selectedFiles()[0]));
    }
}

}
}
