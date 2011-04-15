#include "coptionbool.h"
#include "coptions.h"
namespace options
{

void COptionBool::load() { set(m_parent->getSectionValue(section(), key(), defaultValue()).toBool()); }
void COptionBool::save() {     m_parent->setSectionValue(section(), key(), value       ())          ; }

}
