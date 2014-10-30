#include "TileLayer.h"

TileLayer::TileLayer(int g_width, int g_height) {
    grid_width = g_width;
    grid_height = g_height;

    tiles = new Tile**[grid_width];
    for (int i = 0; i < grid_width; i++) {
      tiles[i] = new Tile*[grid_height];
    }
}

TileLayer::~TileLayer() {
  for (int i = 0; i < grid_width; i++) {
    for (int j = 0; j < grid_height; j++) {
      delete tiles[i][j];
    }
    delete[] tiles[i];
  }
  delete[] tiles;
}

