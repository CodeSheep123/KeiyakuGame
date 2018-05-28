#pragma once

#include <istream>
#include <string>

#include "TileSet.hpp"

/*Map File format:
 *
 *The first line should contain Map width and height, in tiles
 *The second line should contain the tile width and height, in pixels
 *Line 3 should contain the path to the tile set image to use
 *Lines 4 - height+4 should contain the tile numbers
 *The last line should contain 4 values, which is the RGBA code for the color mask to use
 *If any of these values are -1, the default mask will be used, which is Magenta
 *
 *From the moment the parser encounters a #, it will skip the rest of the line (useful for comments)
 *Note that comments may not appear in the middle of the tiles grid, only after a line (see example)
 *
 *A sample map file looks like this
 *10 10 # The map is 10x10
 *32 32 # Every tile is 32x32 pixels
 *media/graphics/tileset.bmp # This is the the path to the tile set
 *
 *0 0 0 1 1 1 1 1 1 1
 *2 2 2 2 2 2 2 2 2 2
 *0 0 0 0 0 0 0 0 0 0
 *3 3 3 3 3 3 3 3 3 3 # The actual tiles
 *5 5 5 5 5 5 5 5 5 5 # are here
 *0 0 0 0 0 0 0 0 0 0 # Note that the space after the # is not required
 *7 7 7 7 7 7 7 7 7 7 # But in my Visual Studio I have Visual Assist installed
 *0 0 0 0 0 0 0 0 0 0 # which uses # + text as a bookmark mechanism
 *9 9 9 9 9 9 9 9 9 9
 *0 0 1 1 2 2 3 3 4 4
 *
 *100 128 76 255 # RGBA for the mask
 **/


class Map : public sf::Drawable
{
public:
	using size_type = TileSet::size_type;

	Map();
	explicit Map(std::string const& file);

	Map(Map const& other);
	Map(Map&& other);

	Map& operator=(Map const& other);
	Map& operator=(Map&& other);

	bool loadFromFile(std::string const& file, char commentToken = '#'); //reads map file and calls TileSet::load() with the data it has read
	bool loadFromStream(std::istream& stream, char commentToken = '#');

	TileSet& getMap();
	TileSet const& getMap() const;

	void setTile(unsigned x, unsigned y, TileSet::tile_type tile);
	TileSet::tile_type getTile(unsigned x, unsigned y);

	TileSet::size_type getWidth();
	TileSet::size_type getHeight();

private:
	TileSet m_tilemap;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void skipToNextWithoutComment(std::istream& stream, char commentToken);
};