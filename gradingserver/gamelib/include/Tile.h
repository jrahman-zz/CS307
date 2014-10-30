#pragma once

typedef enum {
  TileTypeNone,
  TileTypeBlank,
  TileTypeTerrain,
  TileTypeWater,
  TileTypeBuilding
} TileType;

class Tile {
  public:
    Tile(int id);

    static TileType tileTypeFromId(int id);

  protected:
    int tile_id;
    TileType type;

  private:
};
