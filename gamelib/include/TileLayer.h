#pragma once

#include "Tile.h"

class TileLayer {
  public:
    Tile ***tiles;
    int grid_width, grid_height;


    TileLayer(int g_width, int g_height);
    ~TileLayer();

  protected: 
  private:
};
