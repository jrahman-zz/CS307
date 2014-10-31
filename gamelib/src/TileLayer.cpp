#include "TileLayer.h"

TileLayer::TileLayer(int g_width, int g_height) {
    grid_width = g_width;
    grid_height = g_height;

    tiles = new Tile*[grid_width];
    for (int i = 0; i < grid_width; i++) {
      tiles[i] = new Tile[grid_height];
    }
}

TileLayer::~TileLayer() {
  for (int i = 0; i < grid_width; i++) {
    delete[] tiles[i];
  }
  delete[] tiles;
}

shared_ptr<TileLayer> TileLayer::merge(TileLayer rhs) {
	if (rhs.grid_width != grid_width || rhs.grid_height != grid_height) {
  		return nullptr;
	}
	shared_ptr<TileLayer> ptr(new TileLayer(grid_width, grid_height));
	for (unsigned int i = 0; i < grid_height; i++) {
		for (unsigned int j = 0; j < grid_width; j++) {
			switch(tiles[i][j].type) {
				case TileType::None:
				case TileType::Blank:
					ptr->[i][j] = rhs[i][j];
					break;
				default:
					ptr->[i][j] = tiles[i][j];
			}
		}
	}
}

unsigned int TileLayer::getHeight() {
	return grid_height;
}

unsigned int TileLayer::getWidth() {
	return grid_width;
}
