#include "copy_transformable.hpp"

#include <SFML/Graphics/Transformable.hpp>

namespace sfml_util
{
	void copy_transformable(sf::Transformable const* src, sf::Transformable* dest)
	{
		dest->setPosition(src->getPosition());
		dest->setScale(src->getScale());
		dest->setOrigin(src->getOrigin());
		dest->setRotation(src->getRotation());
	}

	void move_transformable(sf::Transformable* src, sf::Transformable* dest)
	{
		copy_transformable(src, dest);
		src->setPosition({ 0, 0 });
		src->setScale({ 1, 1 });
		src->setOrigin({ 0, 0 });
		src->setRotation(0);
	}
}