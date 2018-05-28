#include "Map.hpp"
#include "../../ErrorHandler.hpp"

#include <fstream>

Map::Map() : m_tilemap {}
{

}

Map::Map(std::string const& file)
{
	loadFromFile(file);
}

Map::Map(Map const& other) : m_tilemap(other.m_tilemap)
{

}

Map::Map(Map&& other) : m_tilemap(std::move(other.m_tilemap))
{

}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(m_tilemap, states);
}

Map& Map::operator=(Map const& other)
{
	m_tilemap = other.m_tilemap;

	return *this;
}

Map& Map::operator=(Map&& other)
{
	m_tilemap = std::move(other.m_tilemap);

	return *this;
}

void Map::skipToNextWithoutComment(std::istream& stream, char commentToken)
{
	static const int MAX_IGNORE = 32767;

	char next = stream.peek();

	while (next == ' ' || next == '\n' || next == '\t') //first, skip all delimiters
	{
		stream.ignore();
		next = stream.peek();
	}

	while (next != EOF && next == commentToken) //then check if there is a comment
	{	
		stream.ignore(MAX_IGNORE, '\n'); //ignore the rest of the line if a comment was detected
		next = stream.peek(); //check next line for comment
	}

}

bool Map::loadFromFile(std::string const& file, char commentToken)
{
	std::ifstream in { file };

	return loadFromStream(in);

}

#pragma warning(push)
#pragma warning(disable: 4018) //C4018: Signed/unsigned mismatch

bool Map::loadFromStream(std::istream& stream, char commentToken)
{
	using Keiyaku::ErrorHandler;

	try 
	{

		size_type width, height;
		size_type tileWidth, tileHeight;
		std::string imagePath;
		std::vector<TileSet::tile_type> tiles;

		skipToNextWithoutComment(stream, commentToken);

		if (stream.eof())
		{
			ErrorHandler::reportError("Map::loadFromStream(): Unexpected token found: EOF");
			return false;
		}

		//Because of the call to skipToNextWithoutComment(), we know that there has to be data in the next read
		//If we alternate data reading with calls to skipToNextWitoutComment(), we make sure that we ignore comments

		stream >> width >> height;
		skipToNextWithoutComment(stream, commentToken);

		if (stream.eof())
		{
			ErrorHandler::reportError("Map::loadFromStream(): Unexpected token found: EOF");
			return false;
		}

		//create the vector with the correct size
		tiles = std::vector<TileSet::tile_type>(width * height, TileSet::tile_type {});

		stream >> tileWidth >> tileHeight;
		skipToNextWithoutComment(stream, commentToken);

		if (stream.eof())
		{
			ErrorHandler::reportError("Map::loadFromStream(): Unexpected token found: EOF");
			return false;
		}

		stream >> imagePath;
		skipToNextWithoutComment(stream, commentToken);

		if (stream.eof())
		{
			ErrorHandler::reportError("Map::loadFromStream(): Unexpected token found: EOF");
			return false;
		}

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				int id;
				stream >> id;
				tiles[i + j * width] = id;
			}

			skipToNextWithoutComment(stream, commentToken);
			if (stream.eof())
			{
				ErrorHandler::reportError("Map::loadFromStream(): Unexpected token found: EOF");
				return false;
			}
		}

		sf::Color mask;

		int r, g, b, a;
		stream >> r >> g >> b >> a;

		//again, saves a lot of typing
#define STCU(x, y, z, w) static_cast<sf::Uint8>(x), static_cast<sf::Uint8>(y), static_cast<sf::Uint8>(z), static_cast<sf::Uint8>(w)
#define CAST_UINT8(x, y, z, w) STCU(x%256, y%256, z%256, w%256)

		if (r == -1 || g == -1 || b == -1 || a == -1)
		{
			mask = sf::Color::Magenta;
		}
		else if (r >= 0 && g >= 0 && b >= 0 && a >= 0)
		{
			mask = sf::Color { CAST_UINT8(r, g, b, a) };
		}
		else
		{
			ErrorHandler::reportError("Map::loadFromStream(): Mask color may not be negative");
			return false;
		}

		if (!m_tilemap.load(imagePath, { tileWidth, tileHeight }, tiles.data(), width, height, mask))
		{
			ErrorHandler::reportError("Map::loadFromStream(): Failed to load map");
			return false;
		}
		return true;
	}
	catch (...)
	{
		ErrorHandler::reportError("Map::loadFromStream(): An unknown error occurred");
		return false;
	}

#undef CAST_UINT8
#undef STCU
}


TileSet& Map::getMap()
{
	return m_tilemap;
}

TileSet const& Map::getMap() const
{
	return m_tilemap;
}



void Map::setTile(unsigned x, unsigned y, TileSet::tile_type tile)
{
	using Keiyaku::ErrorHandler;

	ErrorHandler::assert(x >= 0 && y >= 0 && x < getWidth() && y < getHeight(), "Map::setTile(): coordinates out of range");

	m_tilemap.setTile(x, y, tile);
}

typename TileSet::tile_type Map::getTile(unsigned x, unsigned y)
{
	using Keiyaku::ErrorHandler;

	ErrorHandler::assert(x >= 0 && y >= 0 && x < getWidth() && y < getHeight(), "Map::getTile(): coordinates out of range");

	return m_tilemap.getTile(x, y);
}

typename TileSet::size_type Map::getWidth()
{
	return m_tilemap.getWidth();
}

typename TileSet::size_type Map::getHeight()
{
	return m_tilemap.getHeight();
}

#pragma warning(pop)