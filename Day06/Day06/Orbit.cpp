#include "Orbit.h"
#include <set>

Orbit::Orbit(std::string label) :
	m_Label(label)
{
}

void Orbit::AddChild(std::shared_ptr<Orbit> child)
{
	child->m_Parent = shared_from_this();
	m_Children.insert({ child->m_Label, child });
}

int Orbit::GetOrbitCount(int level)
{
	int count = level;
	for (auto& child : m_Children)
	{
		count += child.second->GetOrbitCount(level + 1);
	}
	return count;
}

int Orbit::GetTransferCount(std::shared_ptr<Orbit> orbit1, std::shared_ptr<Orbit> orbit2)
{
	std::map<std::string, int> o1Parents;
	int inCount = 0;

	auto o1Track = orbit1;
	while (o1Track->HasParent())
	{
		o1Track = o1Track->m_Parent;
		o1Parents.insert({ o1Track->m_Label, inCount++ });
	}

	auto o2Track = orbit2;
	int outCount = 0;
	while (o2Track->HasParent())
	{
		o2Track = o2Track->m_Parent;
		if (auto iter = o1Parents.find(o2Track->m_Label); iter != o1Parents.end())
		{
			return outCount + iter->second;
		}
		outCount++;
	}
	return -1;
}
