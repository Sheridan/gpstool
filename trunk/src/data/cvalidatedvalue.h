#ifndef CVALIDATEDVALUE_H
#define CVALIDATEDVALUE_H
#include <QString>

namespace data
{


template <typename T> class CValidatedVariable
{

public: // ####################################################
    CValidatedVariable          ()                  { m_valid = false;                 }
    ~CValidatedVariable         ()                  {                                  }
    const bool    & isValid     () const            { return m_valid;                  }
    const T       & value       () const            { return m_value;                  }
    void            set         (const T &value)    { m_value = value; m_valid = true; }
    void            operator=   (const T &value)    { m_value = value;                 }

private: // ####################################################
    T       m_value;
    bool    m_valid;

};

typedef CValidatedVariable<int>     TValidatedInt;
typedef CValidatedVariable<qint8>   TValidatedInt8;
typedef CValidatedVariable<quint8>  TValidatedUInt8;
typedef CValidatedVariable<qint16>  TValidatedInt16;
typedef CValidatedVariable<QString> TValidatedString;
typedef CValidatedVariable<float>   TValidatedFloat;
typedef CValidatedVariable<double>  TValidatedDouble;
typedef CValidatedVariable<bool>    TValidatedBool;

}
#endif // CVALIDATEDVALUE_H
