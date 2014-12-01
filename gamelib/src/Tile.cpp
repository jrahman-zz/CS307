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
  // These range checks are awful. Let's think of a better way to do this later.

  // This assumes we are parsing from the standard RPG_tilepack tileset.
  // TODO(josh) make these checks relative to each tileset.
  
  // Just sank an hour tracing a bug down related to this
  // Need to keep these IDs up to date
  // Had to add a hack by increasing the building bound to 500
  //
  // ^ sorry Jason...
  if (id == 0) {
    return TileType::Blank;
  } else if ((1 <= id && id <= 10)
             || (21 <= id && id <= 30)
             || (41 <= id && id <= 48)) {
    return TileType::Terrain;
  } else if ((11 <= id && id <= 15)
             || (31 <= id && id <= 35)
             || (51 <= id && id <= 53)) {
    return TileType::Water;
  } else if ((61 <= id && id <= 178) // exclude empty tiles.
             && ((id - 61) % 20 >= 18)) {
    return TileType::Building;
  } else if ((181 <= id && id <= 186)
             || (201 <= id && id <= 206)
             || (221 <= id && id <= 226)) {
    return TileType::Flora;
  } else if (187 <= id && id <= 188) {
    return TileType::Ladder;
  } else if ((207 <= id && id <= 208)
             || (227 <= id && id <= 228)
             || (247 <= id && id <= 248)) {
    return TileType::Gate;
  } else if (189 <= id && id <= 190) {
    return TileType::Crate;
  } else if ((209 <= id && id <= 210)
             || (229 <= id && id <= 230)
             || (249 <= id && id <= 250)) {
    return TileType::Barrel;
  } else if (id == 195 || id == 200
             || id == 215 || id == 220
             || id == 235 || id == 240
             || id == 255 || id == 260) {
    return TileType::Door;
  } else if ((id <= 128 && id <= 129)
  			 || (id <= 148 && id <= 149)
  			 || (id <= 168 && id <= 169)
  			 || (id <= 137 && id <= 138)
  			 || (id <= 157 && id <= 158)
  			 || (id <= 177 && id <= 178)){
  	return TileType::Staircase;
  } else {
    return TileType::Building; // Gahhh forget it
    // Everything's a building
  }

  // This should not happen. This probably indicates a problem
  // in the above mapping logic.
  throw std::runtime_error("Unable to map tile id to TileType");
  return TileType::None;
}

