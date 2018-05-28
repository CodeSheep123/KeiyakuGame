#include "TextureManager.hpp"
#include "ImageManager.hpp"

namespace Keiyaku
{
	TextureManager::TextureManager(ImageManager* imageMan) : ResourceManager(), m_imageManager(imageMan)
	{
		ErrorHandler::assert(imageMan != nullptr, "TextureManager::TextureManager(): Image manager was nullptr");
	}

	ImageManager* TextureManager::getImageManager() const
	{
		return m_imageManager;
	}

	void TextureManager::setImageManager(ImageManager* imageMan)
	{
		ErrorHandler::assert(imageMan != nullptr, "TextureManager::setImageManager(): Image manager was nullptr");
	}

	bool TextureManager::load(sf::Texture &resource, const std::string &id) const
	{
		return resource.loadFromImage(*m_imageManager->get(id));
	}
}