#pragma once

#include <memory>

#include "Tile.h"

using namespace std;

class TileLayer {
public:
	TileLayer(unsigned int g_width, unsigned int g_height);
	~TileLayer();
	
	Tile* operator[](unsigned int i) {
		if (i >= grid_width) {
			throw std::exception();
		}
		return tiles[i];
	}

	shared_ptr<TileLayer> merge(TileLayer& rhs);

	unsigned int getWidth();
	unsigned int getHeight();
protected:
	Tile **tiles;
	unsigned int grid_width, grid_height;
};
