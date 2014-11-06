#pragma once

#include <memory>

#include "Tile.h"

using namespace std;

class TileLayer {
public:
    TileLayer(unsigned int g_width, unsigned int g_height);
    TileLayer(TileLayer& rhs);
    TileLayer(TileLayer&& rhs);

    ~TileLayer();
    
    Tile* operator[](unsigned int i) {
        if (i >= m_gridHeight) {
            throw runtime_error("Invalid index");
        }
        return &m_tiles[i * m_gridWidth];
    }

    /*
     * Warning, this is NOT commutative!
     */
    shared_ptr<TileLayer> merge(shared_ptr<TileLayer> rhs);

    unsigned int getWidth();
    unsigned int getHeight();
protected:
    Tile *m_tiles;
    unsigned int m_gridWidth, m_gridHeight;
};
