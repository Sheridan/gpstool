#include "coptiontime.h"
#include "coptions.h"
namespace options
{

void COptionTime::load() { set(m_parent->getSectionValue(section(), key(), defaultValue()).toTime()); }
void COptionTime::save() {     m_parent->setSectionValue(section(), key(), value       ())          ; }

}
