#pragma once

#include <json/json.h>

enum class TileType {
    None, // No mapped value - possibly indicates error.
    Blank,
    Terrain,
    Water,
    Building,
    Flora,
    Ladder,
    Gate,
    Crate,
    Barrel,
    Door,
    Staircase
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
