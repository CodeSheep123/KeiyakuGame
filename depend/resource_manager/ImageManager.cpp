#include "ImageManager.hpp"

namespace Keiyaku
{
	bool ImageManager::load(sf::Image& resource, std::string const& path) const
	{
		return resource.loadFromFile(path);
	}
	
}