#pragma once

#include <vector>
#include "TileLayer.h"
#include "Trigger.h"

/**
 * Parses JSON files exported from Tiled Map Editor.
 */
class TilemapParser {
  public:
    TilemapParser();

    bool parse(std::string& json_str);

    std::vector<TileLayer *> getTileLayers();
    std::vector<Trigger *> getTriggers();

  protected:
  private:
    std::vector<TileLayer *> tileLayers;
    std::vector<Trigger *> triggers;
};
