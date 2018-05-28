#ifndef KEIYAKU_ACTIONS_HPP_
#define KEIYAKU_ACTIONS_HPP_

#include <iostream>
#include <string>

#include <SFML/Window/Keyboard.hpp>

namespace Keiyaku
{

	enum class Action
	{
		Unknown,
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Screenshot,
		Exit
	}; // #ModifyThis: When adding a new action, add it to this list

	/*This cannot be constexpr, because the implementation is in a different translation unit, and in other translation units,
	 *the function cannot be evaluated at compile time, and giving a linker error*/

	/*constexpr */ const char* actionToString(Action a);
	Action stringToAction(std::string const& str);

	std::istream& operator>>(std::istream& in, sf::Keyboard::Key& key);
	std::ostream& operator<<(std::ostream& out, sf::Keyboard::Key& key);

} //namespace Keiyaku

#endif //#ifndef KEIYAKU_ACTIONS_HPP_