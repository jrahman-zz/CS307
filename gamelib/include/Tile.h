#pragma once

#include <json/json.h>

enum class TileType {
	None,
	Blank,
	Terrain,
	Water,
	Building
};

class Tile {
public:
	Tile();
	Tile(int id);
	
	TileType getType();
	int getID();

	static TileType tileTypeFromId(int id);

protected:
private:
	int m_ID;
	TileType m_type;
};
