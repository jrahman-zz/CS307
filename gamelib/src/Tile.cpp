#include "Tile.h"

Tile::Tile() 
    : m_type(TileType::None)
    , m_ID(-1)
{}

Tile::Tile(int id) 
    : m_ID(id)
    , m_type(tileTypeFromId(m_ID))
{}

TileType Tile::getType() {
    return m_type;
}

int Tile::getID() {
    return m_ID;
}

TileType Tile::tileTypeFromId(int id) {
  // These range checks are prone to error, but id'd hate to have a switch
  // statement with 100+ values...
  if (id == 0) {
    return TileType::None;
  } else if ((1 <= id && id <= 10)
             || (21 <= id && id <= 30)
             || (41 <= id && id <= 48)) {
    return TileType::Terrain;
  } else if ((11 <= id && id <= 15)
             || (31 <= id && id <= 35)
             || (51 <= id && id <= 53)) {
    return TileType::Water;
  } else if ((61 <= id && id <= 78)
             || (81 <= id && id <= 98)
             || (101 <= id && id <= 500)) {
    return TileType::Building;
  }
  // Not mapped - must be blank.
  return TileType::Blank;
}

