#ifndef CCOORDINATES_H
#define CCOORDINATES_H
#include <QtGlobal>
#include "cvalidatedvalue.h"

namespace data
{

template <typename T> class CCoordinates
{
public: // ####################################################
    CCoordinates(const T & a, const T & b) { m_alpha = a; m_beta = b; }
    bool isValid() const { return m_alpha.isValid() && m_beta.isValid(); }
    virtual void setCoordintes(const T &a, const T &b) = 0;

protected: // ####################################################
    CValidatedVariable<T> m_alpha;
    CValidatedVariable<T> m_beta;
};

}
#endif
