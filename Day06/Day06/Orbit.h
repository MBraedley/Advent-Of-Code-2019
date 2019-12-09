#pragma once
#include <map>
#include <memory>
#include <string>

class Orbit : public std::enable_shared_from_this<Orbit>
{
public:
	Orbit(std::string label);
	~Orbit() = default;

	void AddChild(std::shared_ptr<Orbit> child);

	bool HasParent() { return m_Parent != nullptr; }
	std::string GetLabel() { return m_Label; }

	int GetOrbitCount(int level);

	static int GetTransferCount(std::shared_ptr<Orbit> orbit1, std::shared_ptr<Orbit> orbit2);

private:
	std::shared_ptr<Orbit> m_Parent = nullptr;
	std::string m_Label;
	std::map<std::string, std::shared_ptr<Orbit>> m_Children;
};

