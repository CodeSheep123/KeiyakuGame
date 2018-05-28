#ifndef KEIYAKU_KEYBIND_MANAGER_HPP_
#define KEIYAKU_KEYBIND_MANAGER_HPP_

#include <string>
#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>

#include "Actions.hpp"

namespace Keiyaku
{

	class KeybindManager
	{
	public:
		KeybindManager() = default;

		/*Loads keybinds from file. Keybinds must be in format:
		 *
		 *Action_Str	KeyCode
		 *
		 *example:
		 *Move_up       76
		 *Move_down     78
		 *
		 *...etc
		*/
		KeybindManager(std::string const& file);
		KeybindManager(KeybindManager const& other);
		KeybindManager(KeybindManager&& other);

		KeybindManager& operator=(KeybindManager const& other);
		KeybindManager& operator=(KeybindManager&& other);

		~KeybindManager() = default;

		void load(std::string const& file);
		void save(std::string const& file) const;

		sf::Keyboard::Key getKey(Action action) const;
		sf::Keyboard::Key getKey(const char* action) const;

		void setKey(Action action, sf::Keyboard::Key key);
		void setKey(const char* action, sf::Keyboard::Key key);
	private:
		std::unordered_map<Action, sf::Keyboard::Key> m_keys;
	};

}

#endif //#ifndef KEIYAKU_KEYBIND_MANAGER_HPP_