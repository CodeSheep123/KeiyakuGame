#ifndef KEIYAKU_TEXTURE_MANAGER_HPP_
#define KEIYAKU_TEXTURE_MANAGER_HPP_

#include "ResourceManager.hpp"
#include <SFML/Graphics/Texture.hpp>

namespace Keiyaku
{
	class ImageManager;

	class TextureManager : public ResourceManager<sf::Texture>
	{
	public:
		TextureManager(ImageManager* imageMan);

		ImageManager* getImageManager() const;
		void setImageManager(ImageManager* imageMan);

	protected:
		bool load(sf::Texture &resource, const std::string &id) const override;

	private:
		ImageManager* m_imageManager;
	};

	using TextureResource = Resource<sf::Texture>;
}

#endif