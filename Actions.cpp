#include "Actions.hpp"

namespace Keiyaku
{

	/*constexpr */ const char* actionToString(Action a)
	{
		// #ModifyThis: When adding a new action, modify this

		switch (a)
		{
		case Action::MoveLeft:
			return "Move_left";
			break;
		case Action::MoveRight:
			return "Move_right";
			break;
		case Action::MoveUp:
			return "Move_up";
			break;
		case Action::MoveDown:
			return "Move_down";
			break;
		case Action::Exit:
			return "Exit";
			break;
		case Action::Screenshot:
			return "Screenshot";
		}

		return "ACTION_UNKNOWN";
	}

	Action stringToAction(std::string const& str)
	{
		// #ModifyThis: When adding a new action, modify this

		if (str == "Move_left") return Action::MoveLeft;
		if (str == "Move_right") return Action::MoveRight;
		if (str == "Move_up") return Action::MoveUp;
		if (str == "Move_down") return Action::MoveDown;
		if (str == "Exit") return Action::Exit;
		if (str == "Screenshot") return Action::Screenshot;

		return Action::Unknown;
	}

	std::istream& operator>>(std::istream& in, sf::Keyboard::Key& key)
	{
		int code;
		in >> code;
		key = static_cast<sf::Keyboard::Key>(code);

		return in;
	}

	std::ostream& operator<<(std::ostream& out, sf::Keyboard::Key& key)
	{
		out << static_cast<int>(key);

		return out;
	}

} //namespace Keiyaku