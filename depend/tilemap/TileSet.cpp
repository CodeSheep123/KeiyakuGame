#include "TileSet.hpp"

#include "../../ErrorHandler.hpp"


TileSet::TileSet() : sf::Drawable{}, sf::Transformable {}, m_width {0}, m_height {0}, m_tileWidth {0}, m_tileHeight {0}
{
	
}

TileSet::TileSet(std::string const& file, sf::Vector2u tile_size, tile_type const* tiles, size_type width, size_type height,
	sf::Color mask)
	: sf::Drawable {}, sf::Transformable {}
{
	if (!load(file, tile_size, tiles, width, height, mask))
	{
		Keiyaku::ErrorHandler::reportError("TileSet::TileSet(): Failed to load TileSet");
	}
}

TileSet::TileSet(TileSet const& other) : m_tileset { other.m_tileset }, m_vertices { other.m_vertices },
	sf::Drawable {},
	m_width {other.m_width},
	m_height {other.m_height},
	m_tileWidth {other.m_tileWidth},
	m_tileHeight {other.m_tileHeight}
{
	/*Initialize transformable part*/
	sfml_util::copy_transformable(dynamic_cast<Transformable const*>(&other), this);

}

TileSet::TileSet(TileSet&& other) : m_tileset { std::move(other.m_tileset) }, m_vertices { std::move(other.m_vertices) },
	m_width { other.m_width },
	m_height { other.m_height },
	m_tileWidth { other.m_tileWidth },
	m_tileHeight { other.m_tileHeight }
{
	other.m_width = 0;
	other.m_height = 0;
	other.m_tileWidth = 0;
	other.m_tileHeight = 0;

	/*Initialize transformable part*/
	sfml_util::move_transformable(dynamic_cast<Transformable*>(&other), this);
}

TileSet& TileSet::operator =(TileSet const& other)
{
	m_tileset = other.m_tileset;
	m_vertices = other.m_vertices;

	m_width = other.m_width;
	m_height = other.m_height;
	m_tileWidth = other.m_tileWidth;
	m_tileHeight = other.m_tileHeight;

	sfml_util::copy_transformable(dynamic_cast<Transformable const*>(&other), this);

	return *this;
}

TileSet& TileSet::operator =(TileSet&& other)
{
	m_tileset = other.m_tileset;
	m_vertices = other.m_vertices;
	m_width = other.m_width;
	m_height = other.m_height;
	m_tileWidth = other.m_tileWidth;
	m_tileHeight = other.m_tileHeight;

	other.m_width = 0;
	other.m_height = 0;
	other.m_tileWidth = 0;
	other.m_tileHeight = 0;
	other.m_tileset = sf::Texture {};
	other.m_vertices = sf::VertexArray {};


	sfml_util::move_transformable(dynamic_cast<Transformable*>(&other), this);

	return *this;
}

TileSet::~TileSet()
{

}


void TileSet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform(); //apply transform

	states.texture = &m_tileset; //set texture

	target.draw(m_vertices, states); //draw
}

bool TileSet::load(std::string const& file, sf::Vector2u tile_size, tile_type const* tiles, size_type width, size_type height,
	sf::Color mask)
{
	m_width = width;
	m_height = height;
	m_tileWidth = tile_size.x;
	m_tileHeight = tile_size.y;

	m_tiles = std::vector<std::vector<tile_type>> { m_height, std::vector<tile_type>(m_width) };

	static const int QUAD_SIZE = 4;

	sf::Image tileset;
	if (!tileset.loadFromFile(file))
	{
		Keiyaku::ErrorHandler::reportError("TileSet::load(): Failed to load Image at path: " + file);
		return false;
	}

	tileset.createMaskFromColor(mask);

	if (!m_tileset.loadFromImage(tileset))
	{
		Keiyaku::ErrorHandler::reportError("TileSet::load(): Failed to create Texture from Image");
		return false;
	}
	
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(width * height * QUAD_SIZE);

	for (unsigned int i = 0; i < width; ++i)
	{
		for (unsigned int j = 0; j < height; ++j)
		{
			// get the current tile number
			tile_type tileNumber = tiles[i + j * width];

			if (tileNumber == (tile_type)-1)
			{
				tileNumber = width * height - 1;
			}

			//Store the current tile number
			m_tiles[i][j] = tileNumber;

			// find its position in the tile set texture
			size_type tu = tileNumber % (m_tileset.getSize().x / tile_size.x);
			size_type tv = tileNumber / (m_tileset.getSize().x / tile_size.x);

			// get a pointer to the current tile's quad
			sf::Vertex* quad = &m_vertices[(i + j * width) * QUAD_SIZE];


#define STCF(x, y) static_cast<float>(x), static_cast<float>(y) //saves typing and gets rid of conversion warnings

			// define its 4 corners
			quad[0].position = sf::Vector2f(STCF(i * tile_size.x, j * tile_size.y));
			quad[1].position = sf::Vector2f(STCF((i + 1) * tile_size.x, j * tile_size.y));
			quad[2].position = sf::Vector2f(STCF((i + 1) * tile_size.x, (j + 1) * tile_size.y));
			quad[3].position = sf::Vector2f(STCF(i * tile_size.x, (j + 1) * tile_size.y));

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(STCF(tu * tile_size.x, tv * tile_size.y));
			quad[1].texCoords = sf::Vector2f(STCF((tu + 1) * tile_size.x, tv * tile_size.y));
			quad[2].texCoords = sf::Vector2f(STCF((tu + 1) * tile_size.x, (tv + 1) * tile_size.y));
			quad[3].texCoords = sf::Vector2f(STCF(tu * tile_size.x, (tv + 1) * tile_size.y));

#undef STCF
		}
	}
	return true;
}

TileSet::tile_type TileSet::getTile(size_type x, size_type y) const
{
	if (x < 0 || x >= m_width
		|| y < 0 || y >= m_height)
	{
		Keiyaku::ErrorHandler::reportError("TileSet::getTile(): Coordinates out of range");
		return 0;
	}

	return m_tiles[y][x];
}

TileSet::tile_type TileSet::getTile(sf::Vector2<size_type> pos) const
{
	return getTile(pos.x, pos.y);
}

void TileSet::setTile(size_type x, size_type y, tile_type tile)
{
	static const int QUAD_SIZE = 4;

	if (x < (unsigned int)0 || x >= m_width
		|| y < (unsigned int)0 || y >= m_height)
	{
		Keiyaku::ErrorHandler::reportError("TileSet::setTile): Coordinates out of range");
		return;
	}

#define STCF(x, y) static_cast<float>(x), static_cast<float>(y) //see load()

	if (tile == (tile_type)-1)
	{
		tile = m_tileset.getSize().x * m_tileset.getSize().y - 1; //set tile to be the last tile
	}

	m_tiles[y][x] = tile;

	sf::Vertex* quad = &m_vertices[(x + y * m_width) * QUAD_SIZE];

	size_type tu = tile % (m_tileset.getSize().x / m_tileWidth);
	size_type tv = tile / (m_tileset.getSize().x / m_tileWidth);

	quad[0].texCoords = sf::Vector2f(STCF(tu * m_tileWidth, tv * m_tileHeight));
	quad[1].texCoords = sf::Vector2f(STCF((tu + 1) * m_tileWidth, tv * m_tileHeight));
	quad[2].texCoords = sf::Vector2f(STCF((tu + 1) * m_tileWidth, (tv + 1) * m_tileHeight));
	quad[3].texCoords = sf::Vector2f(STCF(tu * m_tileWidth, (tv + 1) * m_tileHeight));

#undef STCF
}

void TileSet::setTile(sf::Vector2<size_type> pos, tile_type tile)
{
	setTile(pos.x, pos.y, tile);
}

TileSet::size_type TileSet::getWidth() const
{
	return m_width;
}

TileSet::size_type TileSet::getHeight() const
{
	return m_height;
}

TileSet::size_type TileSet::getTileWidth() const
{
	return m_tileWidth;
}

TileSet::size_type TileSet::getTileHeight() const
{
	return m_tileHeight;
}