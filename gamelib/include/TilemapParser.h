#pragma once

#include <memory>
#include <vector>
#include "TileLayer.h"
#include "Trigger.h"

using namespace std;

/**
 * Parses JSON files exported from Tiled Map Editor.
 */
class TilemapParser {
  public:
    TilemapParser();

    bool parse(string& json_str);

    vector<shared_ptr<TileLayer>> getTileLayers();
    vector<shared_ptr<Trigger>> getTriggers();

  protected:
  private:
    vector<shared_ptr<TileLayer>> tileLayers;
    vector<shared_ptr<Trigger>> triggers;
};
