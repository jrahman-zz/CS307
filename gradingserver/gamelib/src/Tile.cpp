#include "Tile.h"

Tile::Tile(int id) {
  tile_id = id;
  type = tileTypeFromId(id);
}

TileType Tile::tileTypeFromId(int id) {
  // These range checks are prone to error, but id'd hate to have a switch
  // statement with 100+ values...
  if (id == 0) {
    return TileTypeNone;
  } else if ((1 <= id && id <= 10)
             || (21 <= id && id <= 30)
             || (41 <= id && id <= 48)) {
    return TileTypeTerrain;
  } else if ((11 <= id && id <= 15)
             || (31 <= id && id <= 35)
             || (51 <= id && id <= 53)) {
    return TileTypeWater;
  } else if ((61 <= id && id <= 78)
             || (81 <= id && id <= 98)
             || (101 <= id && id <= 118)) {
    return TileTypeBuilding;
  }
  // Not mapped - must be blank.
  return TileTypeBlank;
}

