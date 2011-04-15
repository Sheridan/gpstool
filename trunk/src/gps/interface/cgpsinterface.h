#ifndef CGPSINTERFACE_H
#define CGPSINTERFACE_H
#include "cgpssource.h"
namespace gps
{

class CGpsInterface
{
public: // ####################################################
    virtual ~CGpsInterface(                );
    CGpsInterface(                         );
    CGpsInterface(CGpsSource *gps          );
    CGpsInterface(const TGpsSourceId &id   );
    void setGps  (CGpsSource *value        );
    void setGps  (const TGpsSourceId &value);
    CGpsSource * gps();

private: // ####################################################
    CGpsSource * m_gps;
};

}
#endif // CGPSINTERFACE_H
