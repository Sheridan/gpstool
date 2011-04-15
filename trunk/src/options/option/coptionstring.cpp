#include "coptionstring.h"
#include "coptions.h"
namespace options
{

void COptionString::load() { set(m_parent->getSectionValue(section(), key(), defaultValue()).toString()); }
void COptionString::save() {     m_parent->setSectionValue(section(), key(), value       ())            ; }

}
