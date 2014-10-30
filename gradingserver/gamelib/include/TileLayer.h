#pragma once

#include "Tile.h"

class TileLayer {
  public:
    Tile ***tiles;

    TileLayer(int g_width, int g_height);
    ~TileLayer();

  protected: 
    int grid_width, grid_height;

  private:
};
