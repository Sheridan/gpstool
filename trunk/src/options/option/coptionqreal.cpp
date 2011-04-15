#include "coptionqreal.h"
#include "coptions.h"
namespace options
{

void COptionQreal::load() { set(m_parent->getSectionValue(section(), key(), defaultValue()).toReal()); }
void COptionQreal::save() {     m_parent->setSectionValue(section(), key(), value       ())          ; }

}
