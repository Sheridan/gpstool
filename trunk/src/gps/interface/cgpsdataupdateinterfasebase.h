#ifndef CGPSDATAUPDATEINTERFASEBASE_H
#define CGPSDATAUPDATEINTERFASEBASE_H
#include "coptionint.h"
#include "cgpsinterface.h"
#include "cgpsdata.h"
namespace gps
{

class CGpsDataUpdateInterfaseBase : public CGpsInterface
{
public: // ####################################################
    CGpsDataUpdateInterfaseBase (                      );
    CGpsDataUpdateInterfaseBase (CGpsSource *gps       );
    CGpsDataUpdateInterfaseBase (const TGpsSourceId &id);
    virtual ~CGpsDataUpdateInterfaseBase(              );

protected: // ####################################################
    virtual void connectGpsData   () = 0;
    virtual void disconnectGpsData() = 0;
    virtual void newGpsDataAvialable  (const data::CGpsData *segment) = 0; // data updating
    virtual bool gpsDataSegmentIsValid(const data::CGpsData *segment) = 0; // check segment for valid data
    virtual bool canGpsDataUpdating   (                             ) = 0; // return true, if object can be updated
    virtual void gpsDataSegmentInvalid(                             ) = 0; // if segment data invalid some time - this function calling for reset object
    bool                  m_gpsDataUpdateConnected;
    void gpsDataIncomingBase(const data::CGpsData *segment);

private: // ####################################################
    void initialize();
    int                   m_unavialableDataCount;
    options::COptionInt * m_goodDataWait;
};

#define GT_GPSUPDATEINTERFACE_CONNECTION \
public: \
  void connectGpsData() { m_gpsDataUpdateConnected = gps()->connectNewData(this, SLOT(gpsDataIncoming(const data::CGpsData *))); } \
  void disconnectGpsData() { if(m_gpsDataUpdateConnected) { gps()->disconnectNewData(this); m_gpsDataUpdateConnected = false; } }

 /*private slots: \
  void gpsDataIncoming(const data::CGpsData *segment) { gpsDataIncomingBase(segment); }*/

}
#endif // CGPSDATAUPDATEINTERFASEBASE_H
