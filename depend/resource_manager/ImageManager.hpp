#ifndef KEIYAKU_IMAGE_MANAGER_HPP_
#define KEIYAKU_IMAGE_MANAGER_HPP_

#include "ResourceManager.hpp"
#include <SFML/Graphics/Image.hpp>

namespace Keiyaku
{

	class ImageManager : public ResourceManager<sf::Image>
	{
	protected:
		bool load(sf::Image& resource, std::string const& path) const override;
	};

	using ImageResource = Resource<sf::Image>;

}

#endif