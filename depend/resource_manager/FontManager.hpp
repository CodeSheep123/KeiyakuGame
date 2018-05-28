#ifndef KEIYAKU_FONT_MANAGER_HPP_
#define KEIYAKU_FONT_MANAGER_HPP_

#include <SFML\Graphics\Font.hpp>
#include "ResourceManager.hpp"

namespace Keiyaku
{
	class FontManager : public ResourceManager<sf::Font>
	{
	protected:
		bool load(sf::Font &resource, const std::string &path) const override;
	};

	using FontResource = Resource<sf::Font>;
}

#endif