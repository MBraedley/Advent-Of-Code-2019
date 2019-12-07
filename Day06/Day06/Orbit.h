#pragma once
#include <set>
#include <memory>
#include <string>

class Orbit : public std::enable_shared_from_this<Orbit>
{
public:
	Orbit(std::string label);
	~Orbit() = default;

	void AddChild(std::shared_ptr<Orbit> child);

private:
	std::shared_ptr<Orbit> m_Parent;
	std::string m_Label;
	std::set<std::shared_ptr<Orbit>> m_Children;
};

