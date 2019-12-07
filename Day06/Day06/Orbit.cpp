#include "Orbit.h"

void Orbit::AddChild(std::shared_ptr<Orbit> child)
{
	child->m_Parent = shared_from_this();
	m_Children.insert(child);
}
