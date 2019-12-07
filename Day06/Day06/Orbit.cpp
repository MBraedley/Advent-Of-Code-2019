#include "Orbit.h"

Orbit::Orbit(std::string label) :
	m_Label(label)
{
}

void Orbit::AddChild(std::shared_ptr<Orbit> child)
{
	child->m_Parent = shared_from_this();
	m_Children.insert({ child->m_Label, child });
}
