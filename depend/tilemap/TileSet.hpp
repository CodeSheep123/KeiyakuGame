#ifndef TILESET_HPP_
#define TILESET_HPP_

#include <SFML/Graphics.hpp>
#include <string>

#include "copy_transformable.hpp"


class TileSet : public sf::Drawable, public sf::Transformable
{
public:
	using size_type = unsigned int;
	using tile_type = unsigned int;

	TileSet();
	TileSet(std::string const& file, sf::Vector2u tile_size, tile_type const* tiles, size_type width, size_type height,
		sf::Color mask = sf::Color::Magenta);

	TileSet(TileSet const& other);
	TileSet(TileSet&& other);

	virtual ~TileSet();

	TileSet& operator=(TileSet const& other);
	TileSet& operator=(TileSet&& other);

	virtual bool load(std::string const& file, sf::Vector2u tile_size, tile_type const* tiles, size_type width, size_type height,
		sf::Color mask = sf::Color::Magenta);

	void setTile(size_type x, size_type y, tile_type tile);
	void setTile(sf::Vector2<size_type> pos, tile_type tile);

	tile_type getTile(size_type x, size_type y) const;
	tile_type getTile(sf::Vector2<size_type> pos) const;

	size_type getWidth() const;
	size_type getHeight() const;
	
	size_type getTileWidth() const;
	size_type getTileHeight() const;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Texture m_tileset;
	sf::VertexArray m_vertices;

	size_type m_width;
	size_type m_height;

	size_type m_tileWidth;
	size_type m_tileHeight;

	std::vector<std::vector<tile_type>> m_tiles {};
};

#endif //#ifndef TILESET_HPP