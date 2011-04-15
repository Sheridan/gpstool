#include "st.h"
#include "capplication.h"
#include "optionsdefines.h"
#include <QDir>
// --------------------------------------------------------------------------------------------------------------------------------------
CApplication::CApplication(int & argc, char ** argv) : QApplication(argc, argv)
{
    GT_SINGLETON->initialize (this);
    setOrganizationName     ("sheridan"                     );
    setOrganizationDomain   ("http://www.sheridan-home.ru/" );
    setApplicationName      ("gpstool"                      );
    setApplicationVersion   ("0.1"                          );
    m_dayStyleSheet      = GT_OPTIONS_APP->requestOption(GT_OPTION_DAY_STYLESHEET  );
    m_nightStyleSheet    = GT_OPTIONS_APP->requestOption(GT_OPTION_NIGHT_STYLESHEET);
    m_mainStyleSheet     = GT_OPTIONS_APP->requestOption(GT_OPTION_MAIN_STYLESHEET );
    m_homePath           = GT_OPTIONS_APP->requestOption(GT_OPTION_APPLICATION_HOME);
    QDir apphome(m_homePath->value());
    if(!apphome.exists())
    {
        apphome.mkpath(m_homePath->value());
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
CApplication::~CApplication()
{
    delete m_mainWindow;
    CSingleton::destroy();
}
// --------------------------------------------------------------------------------------------------------------------------------------
int CApplication::run()
{
    refreshStyleSheet(GT_DAYNIGHT->current());
    m_mainWindow	= new ui::dialogs::CMainWindow();
    m_mainWindow    ->show();
    GT_DATABASE_GPS ->open();
    connect(GT_DAYNIGHT , SIGNAL(switchTo(CDayNight::EDNType))  , this, SLOT(refreshStyleSheet(CDayNight::EDNType)) );
    connect(this        , SIGNAL(lastWindowClosed())            , this, SLOT(quit())                                );
    return exec();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CApplication::refreshStyleSheet(CDayNight::EDNType dnt)
{
    switch(dnt)
    {
        case CDayNight::dnDay:  setStyleSheet ( m_dayStyleSheet  ->value().text + m_mainStyleSheet->value().text ); break;
        case CDayNight::dnNight:setStyleSheet ( m_nightStyleSheet->value().text + m_mainStyleSheet->value().text ); break;
        case CDayNight::dnUnset:setStyleSheet ( ""                                                               ); break;
    }
}
