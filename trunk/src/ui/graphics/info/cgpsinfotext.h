#ifndef CGPSINFOTEXT_H
#define CGPSINFOTEXT_H
#include "cgpsinfoitem.h"
#include "cclienttext.h"
namespace ui
{
namespace graphics
{

enum EGpsInfoTextItemType
{
    gititUnknown,
    gititCourseFromNorth,
    gititSpeedOverGround,
    gititAltitude,
    gititLatitude,
    gititLongitude,
    gititMode,
    gititStatus,
    gititPositionQualityTotal,
    gititPositionQualityHorizontal,
    gititPositionQualityVertical,
    gititSattelitesInLastFix,
    gititSentence,
    gititRateOfClimb
};

class CGpsInfoText : public CGpsInfoItem, public ui::graphics::primitive::window::CClientText
{
public: // ####################################################
    CGpsInfoText(gps::CGpsSource *gpssrc, const QString & caption, tools::TId iid = 0);
    ~CGpsInfoText();
    EGpsInfoItemType infoType() { return giitText; }
    virtual EGpsInfoTextItemType textType() = 0;
    ui::graphics::primitive::window::CClient *windowClient() { return this; }

private: // ####################################################
    void loadFromConfig(const QString & section);
    void saveToConfig  (const QString & section);
};

}
}
#endif // CGPSINFOTEXT_H
