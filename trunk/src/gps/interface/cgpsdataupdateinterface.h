#ifndef CGPSDATAUPDATEINTERFACE_H
#define CGPSDATAUPDATEINTERFACE_H

#include "cgpsdataupdateinterfasebase.h"

namespace gps
{

class CGpsDataUpdateInterface : public QObject, public CGpsDataUpdateInterfaseBase
{
    Q_OBJECT
    GT_GPSUPDATEINTERFACE_CONNECTION;
public: // ####################################################
    CGpsDataUpdateInterface (                      );
    CGpsDataUpdateInterface (CGpsSource *gps       );
    CGpsDataUpdateInterface (const TGpsSourceId &id);
    virtual ~CGpsDataUpdateInterface(              );
private slots: // ####################################################
  void gpsDataIncoming(const data::CGpsData *segment) { gpsDataIncomingBase(segment); }
};

}
#endif // CGPSDATAUPDATEINTERFACE_H
