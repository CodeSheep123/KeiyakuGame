#ifndef KEIYAKU_MUSIC_MANAGER_HPP_
#define KEIYAKU_MUSIC_MANAGER_HPP_

#include "ResourceManager.hpp"
#include <SFML\Audio\Music.hpp>

namespace Keiyaku
{
	class MusicManager : public ResourceManager<sf::Music>
	{
	protected:
		virtual bool load(sf::Music& resource, std::string const& id) const override;
	};

	using MusicResource = Resource<sf::Music>;
}

#endif