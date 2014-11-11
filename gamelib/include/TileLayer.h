#pragma once

#include <memory>

#include "json/json.h"
#include "Tile.h"

using namespace std;

class TileLayer {
public:
    explicit TileLayer(Json::Value value);
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

    unsigned int getWidth() const;

    unsigned int getHeight() const;

    string getName() const;
protected:

    /*
     * Ban default constructor
     */
    TileLayer() = delete;

    Tile *m_tiles;

    unsigned int m_gridWidth;
    
    unsigned int m_gridHeight;

    string m_name;
};
