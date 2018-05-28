#include "MusicManager.hpp"

namespace Keiyaku
{
	bool MusicManager::load(sf::Music& resource, std::string const& id) const
	{
		return resource.openFromFile(id);
	}
}