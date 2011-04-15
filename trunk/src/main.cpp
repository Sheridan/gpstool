#include "st.h"
// --------------------------------------------------------------------------------------------------------------------------------------
Q_DECLARE_METATYPE(    gps::TGpsSourceId);
Q_DECLARE_METATYPE(logging::SLogMessage );
// --------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char ** argv)
{
    qRegisterMetaType<    gps::TGpsSourceId>(    "gps::TGpsSourceId");
    qRegisterMetaType<logging::SLogMessage >("logging::SLogMessage" );

    CApplication *app = new CApplication(argc, argv);
    int r = app->run();
    delete app;
    return r;
}
