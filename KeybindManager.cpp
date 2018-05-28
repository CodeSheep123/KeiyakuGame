#include "KeyBindManager.hpp"
#include "ErrorHandler.hpp"

#include <fstream>

namespace Keiyaku
{

	KeybindManager::KeybindManager(std::string const& file)
	{
		load(file);
	}

	KeybindManager::KeybindManager(KeybindManager const& other) : m_keys(other.m_keys)
	{

	}

	KeybindManager::KeybindManager(KeybindManager&& other) : m_keys(std::move(other.m_keys))
	{

	}

	KeybindManager& KeybindManager::operator=(KeybindManager const& other)
	{
		if (this != &other) //check for self-assignment
		{
			m_keys = other.m_keys;
		}

		return *this;
	}

	KeybindManager& KeybindManager::operator=(KeybindManager&& other)
	{
		if (this != &other)
		{
			m_keys = std::move(other.m_keys);
		}

		return *this;
	}

	void KeybindManager::load(std::string const& file)
	{
		std::ifstream in { file };

		if (!in.good())
		{
			ErrorHandler::reportError("KeybindManager::load(): Failed to open file");
			return;
		}

		std::string name;
		sf::Keyboard::Key keycode;

		while (in >> name >> keycode)
		{
			ErrorHandler::assert(keycode >= 0 && keycode < sf::Keyboard::KeyCount, 
				"KeybindManager::load(): Invalid keycode: " + std::to_string(keycode));

			Action action = stringToAction(name);
			ErrorHandler::assert(action != Action::Unknown,
				"KeybindManager::load(): Invalid action: " + name);

			m_keys.emplace(action, keycode);
		}
	}

	void KeybindManager::save(std::string const& file) const
	{
		std::ofstream out { file, std::ofstream::out | std::ofstream::trunc};

		for (auto const& [action, key] : m_keys)
		{
			out << actionToString(action) << ' ' << key << '\n';
		}
	}

	sf::Keyboard::Key KeybindManager::getKey(Action action) const
	{
		return m_keys.at(action);
	}

	sf::Keyboard::Key KeybindManager::getKey(const char* str) const
	{
		return getKey(stringToAction(str));
	}

	void KeybindManager::setKey(Action action, sf::Keyboard::Key key)
	{
		m_keys[action] = key;
	}

	void KeybindManager::setKey(const char* action, sf::Keyboard::Key key)
	{
		setKey(stringToAction(action), key);
	}
}