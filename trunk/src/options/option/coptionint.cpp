#include "coptionint.h"
#include "coptions.h"
namespace options
{

void COptionInt::load() { set(m_parent->getSectionValue(section(), key(), defaultValue()).toInt()); }
void COptionInt::save() {     m_parent->setSectionValue(section(), key(), value       ())         ; }

}
