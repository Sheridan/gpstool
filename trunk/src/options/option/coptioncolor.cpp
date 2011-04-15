#include "coptioncolor.h"
#include "coptions.h"
namespace options
{

void COptionColor::load() { set(m_parent->getSectionValue(section(), key(), defaultValue()).toUInt()); }
void COptionColor::save() {     m_parent->setSectionValue(section(), key(), value       ())          ; }

}
