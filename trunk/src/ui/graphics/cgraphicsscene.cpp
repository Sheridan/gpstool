#include "cgraphicsscene.h"
#include "cgraphicsitem.h"
#include "cgpsinfotext.h"
#include "infotextitems.h"
#include "st.h"
namespace ui
{
namespace graphics
{
// --------------------------------------------------------------------------------------------------------------------------------------
CGraphicsScene::CGraphicsScene(const QString &sceneName) : QGraphicsScene()
{
    setObjectName   (sceneName);
    loadGpsInfoItems();
}
// --------------------------------------------------------------------------------------------------------------------------------------
CGraphicsScene::~CGraphicsScene()
{
    saveGpsInfoItems  ();
    removeGpsInfoItems();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGraphicsScene::saveGpsInfoItems()
{
    QString section;
    foreach(CGpsInfoItem *i, m_gpsInfoItems)
    {
        section = QString("%1").arg(i->id());
        GT_OPTIONS_WINDOWS_ITEMS->setSectionValue(section, "scene", objectName());
        i->save(section);

    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
#define GT_INFOTEXTITEM_CASE_LOAD(_key,_class) \
case _key: { \
             gps::TGpsSourceId gpsid = GT_OPTIONS_WINDOWS_ITEMS->getSectionValue(section, "gps", 0).toUInt(); \
             if(GT_GPS_MANAGER->exists(gpsid)) \
             { \
               _class *c = new _class(GT_GPS_MANAGER->source(gpsid), section.toUInt()); \
               c->load(section); \
               addGpsInfoItem(c); \
             } \
             else \
             { \
               GT_LOGGER->append(QString("GPS source %1 not exists, item not loaded").arg(gpsid), mtError); \
             } \
           } break;

void CGraphicsScene::loadGpsInfoItems()
{
    foreach(QString section, GT_OPTIONS_WINDOWS_ITEMS->sections())
    {
        if(GT_OPTIONS_WINDOWS_ITEMS->getSectionValue(section, "scene", "-").toString() == objectName())
        {
            switch(static_cast<EGpsInfoItemType>(GT_OPTIONS_WINDOWS_ITEMS->getSectionValue(section, "type", giitUnknown).toInt()))
            {
            case giitText:
                {
                    switch(static_cast<EGpsInfoTextItemType>(GT_OPTIONS_WINDOWS_ITEMS->getSectionValue(section, "texttype", gititUnknown).toInt()))
                    {
                        GT_INFOTEXTITEM_CASE_LOAD(gititSpeedOverGround          , CGpsInfoTextItemSpeeOverGround            );
                        GT_INFOTEXTITEM_CASE_LOAD(gititCourseFromNorth          , CGpsInfoTextItemCourseFromNorth           );
                        GT_INFOTEXTITEM_CASE_LOAD(gititAltitude                 , CGpsInfoTextItemAltitude                  );
                        GT_INFOTEXTITEM_CASE_LOAD(gititLatitude                 , CGpsInfoTextItemLatitude                  );
                        GT_INFOTEXTITEM_CASE_LOAD(gititLongitude                , CGpsInfoTextItemLongitude                 );
                        GT_INFOTEXTITEM_CASE_LOAD(gititMode                     , CGpsInfoTextItemMode                      );
                        GT_INFOTEXTITEM_CASE_LOAD(gititStatus                   , CGpsInfoTextItemStatus                    );
                        GT_INFOTEXTITEM_CASE_LOAD(gititPositionQualityTotal     , CGpsInfoTextItemPositionQualityTotal      );
                        GT_INFOTEXTITEM_CASE_LOAD(gititPositionQualityHorizontal, CGpsInfoTextItemPositionQualityHorizontal );
                        GT_INFOTEXTITEM_CASE_LOAD(gititPositionQualityVertical  , CGpsInfoTextItemPositionQualityVertical   );
                        GT_INFOTEXTITEM_CASE_LOAD(gititSattelitesInLastFix      , CGpsInfoTextItemSattelitesInLastFix       );
                        GT_INFOTEXTITEM_CASE_LOAD(gititRateOfClimb              , CGpsInfoTextItemRateOfClimb               );
                        GT_INFOTEXTITEM_CASE_LOAD(gititSentence                 , CGpsInfoTextItemSentence                  );
                        case gititUnknown: break;
                    }
                }
                break;
                case giitUnknown: break;
            }
        }
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGraphicsScene::removeGpsInfoItems()
{
    foreach(CGpsInfoItem *i, m_gpsInfoItems)
    {
        removeGpsInfoItem(i, false);
    }
}
// --------------------------------------------------------------------------------------------------------------------------------------

void CGraphicsScene::addGpsInfoItem(CGpsInfoItem *value)
{
    m_gpsInfoItems.append(value);
    ui::graphics::primitive::window::CWindow *window = new ui::graphics::primitive::window::CWindow(value->windowClient(), this);
    QString section = QString("%1").arg(value->id());
    window->setPos (GT_OPTIONS_WINDOWS_ITEMS->getSectionValue(section, "pos" , QPointF(0  , 0 )).toPointF());
    window->setSize(GT_OPTIONS_WINDOWS_ITEMS->getSectionValue(section, "size", QSizeF (150, 50)).toSizeF ());
    m_windows[value->id()] = window;
    connect(window, SIGNAL(closeRequest(ui::graphics::primitive::window::CWindow*)), this, SLOT(windowCloseRequest(ui::graphics::primitive::window::CWindow*)));
}
// --------------------------------------------------------------------------------------------------------------------------------------
#define GT_INFOTEXTITEM_CASE_DELETE(_key,_class) case _key: { delete static_cast<_class *>(textItem); } break;

void CGraphicsScene::removeGpsInfoItem(CGpsInfoItem *value, bool removeFromConfig)
{
    QString section = QString("%1").arg(value->id());
    if(removeFromConfig)
    {
        GT_OPTIONS_WINDOWS_ITEMS->removeSection(section);
    }
    else
    {
        GT_OPTIONS_WINDOWS_ITEMS->setSectionValue(section, "pos" , m_windows[value->id()]->pos ());
        GT_OPTIONS_WINDOWS_ITEMS->setSectionValue(section, "size", m_windows[value->id()]->size());
    }
    m_gpsInfoItems.removeOne(value);
    delete m_windows[value->id()];
    m_windows.remove(value->id());
    delete value;
//    switch(value->infoType())
//    {
//    case giitText:
//        {
//            CGpsInfoText *textItem = static_cast<CGpsInfoText *>(value);
//            switch(textItem->textType())
//            {
//                GT_INFOTEXTITEM_CASE_DELETE(gititSpeedOverGround            , CGpsInfoTextItemSpeeOverGround            );
//                GT_INFOTEXTITEM_CASE_DELETE(gititCourseFromNorth            , CGpsInfoTextItemCourseFromNorth           );
//                GT_INFOTEXTITEM_CASE_DELETE(gititAltitude                   , CGpsInfoTextItemAltitude                  );
//                GT_INFOTEXTITEM_CASE_DELETE(gititLatitude                   , CGpsInfoTextItemLatitude                  );
//                GT_INFOTEXTITEM_CASE_DELETE(gititLongitude                  , CGpsInfoTextItemLongitude                 );
//                GT_INFOTEXTITEM_CASE_DELETE(gititMode                       , CGpsInfoTextItemMode                      );
//                GT_INFOTEXTITEM_CASE_DELETE(gititStatus                     , CGpsInfoTextItemStatus                    );
//                GT_INFOTEXTITEM_CASE_DELETE(gititPositionQualityTotal       , CGpsInfoTextItemPositionQualityTotal      );
//                GT_INFOTEXTITEM_CASE_DELETE(gititPositionQualityHorizontal  , CGpsInfoTextItemPositionQualityHorizontal );
//                GT_INFOTEXTITEM_CASE_DELETE(gititPositionQualityVertical    , CGpsInfoTextItemPositionQualityVertical   );
//                GT_INFOTEXTITEM_CASE_DELETE(gititSattelitesInLastFix        , CGpsInfoTextItemSattelitesInLastFix       );
//                GT_INFOTEXTITEM_CASE_DELETE(gititRateOfClimb                , CGpsInfoTextItemRateOfClimb               );
//                GT_INFOTEXTITEM_CASE_DELETE(gititSentence                   , CGpsInfoTextItemSentence                  );
//                case gititUnknown: break;
//            }
//        }
//        break;
//        case giitUnknown: break;
//    }
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CGraphicsScene::windowCloseRequest(ui::graphics::primitive::window::CWindow *wnd)
{
    tools::TId id = m_windows.key(wnd);
    foreach(CGpsInfoItem *i, m_gpsInfoItems)
    {
        if(i->id() == id)
        {
            removeGpsInfoItem(i, true);
            return;
        }
    }

}


}
}
