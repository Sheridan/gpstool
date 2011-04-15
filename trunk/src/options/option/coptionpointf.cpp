#include "coptionpointf.h"
#include "coptions.h"
namespace options
{

void COptionPointF::load() { set(m_parent->getSectionValue(section(), key(), defaultValue()).toPointF()); }
void COptionPointF::save() {     m_parent->setSectionValue(section(), key(), value       ())            ; }

}
