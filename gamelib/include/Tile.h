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
    int tile_id;
    TileType type;

    Tile(int id);

    static TileType tileTypeFromId(int id);

  protected:
  private:
};
