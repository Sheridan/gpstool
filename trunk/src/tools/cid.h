#ifndef CID_H
#define CID_H

#include<QtGlobal>

namespace tools
{

typedef uint TId;

class CId
{
public: // ####################################################
    CId(const TId &val = 0);
    virtual ~CId() {}
    const TId & id() const { return m_value; }

private: // ####################################################
    TId m_value;
};

}
#endif // CID_H
