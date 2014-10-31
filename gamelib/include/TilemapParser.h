#pragma once

#include <memory>
#include <list>
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

    list<shared_ptr<TileLayer>> getTileLayers();
    list<shared_ptr<Trigger>> getTriggers();

  protected:
  private:
    list<shared_ptr<TileLayer>> tileLayers;
    list<shared_ptr<Trigger>> triggers;
};
