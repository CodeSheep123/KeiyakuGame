#include "FontManager.hpp"

namespace Keiyaku
{
	bool FontManager::load(sf::Font &resource, const std::string &path) const
	{
		return resource.loadFromFile(path);
	}
}