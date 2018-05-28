#ifndef SF_UTIL_COPY_TRANSFORMABLE_HPP_
#define SF_UTIL_COPY_TRANSFORMABLE_HPP_

#include <SFML/Graphics/Transformable.hpp>

namespace sfml_util
{
	void copy_transformable(sf::Transformable const* src, sf::Transformable* dest);
	void move_transformable(sf::Transformable* src, sf::Transformable* dest);

};

#endif