#pragma once

#include <json/json.h>

typedef enum {
  TileTypeNone,
  TileTypeBlank,
  TileTypeTerrain,
  TileTypeWater,
  TileTypeBuilding
} TileType;

class Tile {
  public:
    int tile_id;
    TileType type;

    Tile(int id);

    static TileType tileTypeFromId(int id);

  protected:
  private:
};
