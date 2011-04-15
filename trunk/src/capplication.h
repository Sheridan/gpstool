#ifndef CAPPLLICATION_H
#define CAPPLLICATION_H

#include <QApplication>
#include "cdaynight.h"
#include "coptiontext.h"
#include "coptionstring.h"
#include "cmainwindow.h"

class CApplication : public QApplication
{
Q_OBJECT
public: // ####################################################
    int run();
    CApplication(int & argc, char ** argv);
    virtual ~CApplication();

private: // ####################################################
    options::COptionText        * m_dayStyleSheet;
    options::COptionText        * m_nightStyleSheet;
    options::COptionText        * m_mainStyleSheet;
    options::COptionString      * m_homePath;
    ui::dialogs::CMainWindow    * m_mainWindow;

public slots: // ####################################################
    void refreshStyleSheet(CDayNight::EDNType dnt);

};
#endif
