TEMPLATE = app
QT = core \
    gui \
    network \
    sql
CONFIG += qt \
    warn_on \
    console \
    resources \
    thread
QMAKE_CXXFLAGS += -O \
    -Wextra \
    -Wuninitialized
BUILDDIR = /tmp/development/gpstool
DESTDIR = $$BUILDDIR/bin
OBJECTS_DIR = $$BUILDDIR/obj
MOC_DIR = $$BUILDDIR/moc
UI_DIR = $$BUILDDIR/ui
RCC_DIR = $$BUILDDIR/rcc
SOURCES = src/main.cpp \
    src/capplication.cpp \
    src/csingleton.cpp \
    src/logging/clogger.cpp \
    src/logging/ui/clogview.cpp \
    src/logging/ui/clogviewitem.cpp \
    src/options/coptions.cpp \
    src/gps/cgpssource.cpp \
    src/gps/cgpsgpsdsource.cpp \
    src/gps/cgpssourcemanager.cpp \
    src/tools/math/cpolarcoordinates.cpp \
    src/ui/graphics/cgraphicsview.cpp \
    src/ui/graphics/cgraphicsscene.cpp \
    src/ui/graphics/cgraphicsitem.cpp \
    src/ui/graphics/satellites/csatellitesview.cpp \
    src/ui/graphics/satellites/csatellitesbackground.cpp \
    src/ui/graphics/satellites/csatelliteitem.cpp \
    src/ui/graphics/satellites/csatellitesscene.cpp \
    src/ui/graphics/map/cmapview.cpp \
    src/data/ccoordinates.cpp \
    src/ui/graphics/ccachedgraphicsitem.cpp \
    src/ui/graphics/text/ctextview.cpp \
    src/ui/graphics/text/ctextscene.cpp \
    src/ui/dialogs/cmainwindow.cpp \
    src/ui/dialogs/cgpssourcenewdialog.cpp \
    src/ui/dialogs/cgpsgpsdsourcedialog.cpp \
    src/ui/controls/cmapsourcestablewidget.cpp \
    src/tools/cdaynight.cpp \
    src/data/db/cdatabase.cpp \
    src/logging/ui/clogmessageshowdialog.cpp \
    src/ui/dialogs/ctextitemadddialog.cpp \
    src/ui/controls/cstatuswidget.cpp \
    src/ui/controls/ciconlabel.cpp \
    src/ui/controls/cgpsiconlabel.cpp \
    src/ui/controls/cdbiconlabel.cpp \
    src/options/option/coptionstring.cpp \
    src/options/option/coptionint.cpp \
    src/options/option/coptionbool.cpp \
    src/options/option/coptioncolor.cpp \
    src/ui/controls/cgpsgpsdwidget.cpp \
    src/ui/controls/ccolorselect.cpp \
    src/ui/controls/cgpssourceslistwidget.cpp \
    src/ui/controls/cgpssourceselect.cpp \
    src/ui/controls/cgpssourceselectaction.cpp \
    src/data/cgpsdata.cpp \
    src/data/ccoordinatesposition.cpp \
    src/data/ccoordinatessatellite.cpp \
    src/data/csatellitedata.cpp \
    src/options/option/coptiontext.cpp \
    src/tools/icons.cpp \
    src/options/option/coptionicon.cpp \
    src/tools/resources.cpp \
    src/options/option/coptiontime.cpp \
    src/ui/controls/ciconselect.cpp \
    src/tools/gtdebug.cpp \
    src/data/cvalidatedvalue.cpp \
    src/data/db/cgpsdatabase.cpp \
    src/options/coptionsapplication.cpp \
    src/options/coptionsgps.cpp \
    src/options/coptionspool.cpp \
    src/options/coptionswindowitems.cpp \
    src/options/option/coptionqreal.cpp \
    src/options/option/coptionpointf.cpp \
    src/ui/graphics/primitives/window/cwindow.cpp \
    src/ui/graphics/map/cmapscene.cpp \
    src/ui/graphics/primitives/ctoolbutton.cpp \
    src/ui/graphics/primitives/window/ccaption.cpp \
    src/ui/graphics/primitives/window/csizegrip.cpp \
    src/ui/graphics/primitives/window/cclient.cpp \
    src/ui/graphics/primitives/window/cwindowchild.cpp \
    src/ui/graphics/primitives/window/cclienttext.cpp \
    src/ui/dialogs/graphic/ctextwindowoptions.cpp \
    src/ui/controls/cfontselect.cpp \
    src/ui/graphics/info/cgpsinfoitem.cpp \
    src/ui/graphics/info/cgpsinfotext.cpp \
    src/ui/graphics/info/infotextitems.cpp \
    src/tools/cid.cpp \
    src/gps/interface/cgpsinterface.cpp \
    src/gps/interface/cgpsdataupdateinterface.cpp \
    src/gps/interface/cgpsdataupdateinterfasebase.cpp
RESOURCES += res/resources.qrc
HEADERS += src/capplication.h \
    src/csingleton.h \
    src/st.h \
    src/logging/clogger.h \
    src/logging/ui/clogview.h \
    src/logging/ui/clogviewitem.h \
    src/options/coptions.h \
    src/options/sdialogstate.h \
    src/gps/cgpssource.h \
    src/gps/cgpsgpsdsource.h \
    src/gps/cgpssourcemanager.h \
    src/tools/math/cpolarcoordinates.h \
    src/ui/graphics/cgraphicsview.h \
    src/ui/graphics/cgraphicsscene.h \
    src/ui/graphics/cgraphicsitem.h \
    src/ui/graphics/satellites/csatellitesview.h \
    src/ui/graphics/satellites/csatellitesbackground.h \
    src/ui/graphics/satellites/csatelliteitem.h \
    src/ui/graphics/satellites/csatellitesscene.h \
    src/ui/graphics/map/cmapview.h \
    src/data/ccoordinates.h \
    src/defines.h \
    src/ui/uidefines.h \
    src/options/optionsdefines.h \
    src/ui/graphics/ccachedgraphicsitem.h \
    src/ui/graphics/text/ctextview.h \
    src/ui/graphics/text/ctextscene.h \
    src/ui/dialogs/cmainwindow.h \
    src/ui/dialogs/cgpssourcenewdialog.h \
    src/ui/dialogs/cgpsgpsdsourcedialog.h \
    src/ui/controls/cmapsourcestablewidget.h \
    src/tools/cdaynight.h \
    src/data/db/cdatabase.h \
    src/data/cmode.h \
    src/data/cstatus.h \
    src/logging/ui/clogmessageshowdialog.h \
    src/ui/dialogs/ctextitemadddialog.h \
    src/ui/controls/cstatuswidget.h \
    src/ui/controls/ciconlabel.h \
    src/ui/controls/cgpsiconlabel.h \
    src/ui/controls/cdbiconlabel.h \
    src/options/option/coption.h \
    src/options/option/coptionstring.h \
    src/options/option/coptionint.h \
    src/options/option/coptionbool.h \
    src/options/option/coptioncolor.h \
    src/ui/controls/cgpsgpsdwidget.h \
    src/ui/controls/ccolorselect.h \
    src/ui/controls/cgpssourceslistwidget.h \
    src/ui/controls/cgpssourceselect.h \
    src/ui/controls/cgpssourceselectaction.h \
    src/data/cgpsdata.h \
    src/data/ccoordinatesposition.h \
    src/data/ccoordinatessatellite.h \
    src/data/csatellitedata.h \
    src/options/option/coptiontext.h \
    src/logging/loggingdata.h \
    src/tools/icons.h \
    src/options/option/coptionicon.h \
    src/tools/resources.h \
    src/options/option/coptiontime.h \
    src/ui/controls/ciconselect.h \
    src/tools/gtdebug.h \
    src/data/cvalidatedvalue.h \
    src/data/db/cgpsdatabase.h \
    src/options/coptionsapplication.h \
    src/options/coptionsgps.h \
    src/options/coptionspool.h \
    src/options/coptionswindowitems.h \
    src/options/option/coptionqreal.h \
    src/options/option/coptionpointf.h \
    src/options/option/coption.h \
    src/ui/graphics/primitives/window/cwindow.h \
    src/ui/graphics/map/cmapscene.h \
    src/ui/graphics/primitives/ctoolbutton.h \
    src/ui/graphics/primitives/window/ccaption.h \
    src/ui/graphics/primitives/primitivesdefines.h \
    src/ui/graphics/primitives/window/csizegrip.h \
    src/ui/graphics/graphicsdefines.h \
    src/gps/gpsdefines.h \
    src/ui/graphics/primitives/window/cclient.h \
    src/ui/graphics/primitives/window/cwindowchild.h \
    src/ui/graphics/primitives/window/cclienttext.h \
    src/ui/dialogs/graphic/ctextwindowoptions.h \
    src/ui/controls/cfontselect.h \
    src/ui/graphics/info/cgpsinfoitem.h \
    src/ui/graphics/info/cgpsinfotext.h \
    src/ui/graphics/info/infotextitems.h \
    src/tools/cid.h \
    src/gps/interface/cgpsinterface.h \
    src/gps/interface/cgpsdataupdateinterface.h \
    src/gps/interface/cgpsdataupdateinterfasebase.h
TRANSLATIONS += res/translations/gpstool_ru.ts
INCLUDEPATH += $$UI_DIR \
    src \
    src/ui \
    src/ui/controls \
    src/ui/graphics \
    src/ui/graphics/primitives \
    src/ui/graphics/primitives/window \
    src/ui/graphics/text \
    src/ui/graphics/info \
    src/ui/graphics/map \
    src/ui/graphics/satellites \
    src/ui/dialogs \
    src/ui/dialogs/graphic \
    src/tools/math \
    src/data \
    src/data/db \
    src/options \
    src/options/option \
    src/gps \
    src/gps/interface \
    src/logging \
    src/logging/ui \
    src/tools \
    src/storage
FORMS += src/ui/dialogs/cmainwindow.ui \
    src/ui/dialogs/cgpssourcenewdialog.ui \
    src/ui/dialogs/cgpsgpsdsourcedialog.ui \
    src/ui/controls/cmapsourcestablewidget.ui \
    src/logging/ui/clogmessageshowdialog.ui \
    src/ui/dialogs/ctextitemadddialog.ui \
    src/ui/controls/cstatuswidget.ui \
    src/ui/controls/cgpsgpsdwidget.ui \
    src/ui/controls/ccolorselect.ui \
    src/ui/controls/cgpssourceslistwidget.ui \
    src/ui/dialogs/graphic/ctextwindowoptions.ui \
    src/ui/controls/cfontselect.ui
OTHER_FILES += res/sql/db.sql
