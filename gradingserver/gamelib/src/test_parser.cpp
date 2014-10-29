#include <json/json.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

typedef enum {
  TileTypeNone,
  TileTypeBlank,
  TileTypeTerrain,
  TileTypeWater,
  TileTypeBuilding
} TileType;

class Tile {
  public:
    int tile_id;
    TileType type;

    Tile(int id) {
      tile_id = id;
      type = tileTypeFromId(id);
    }

    static TileType tileTypeFromId(int i) {
      // These range checks are prone to error, but I'd hate to have a switch
      // statement with 100+ values...
      if (i == 0) {
        return TileTypeNone;
      } else if ((1 <= i && i <= 10)
                 || (21 <= i && i <= 30)
                 || (41 <= i && i <= 48)) {
        return TileTypeTerrain;
      } else if ((11 <= i && i <= 15)
                 || (31 <= i && i <= 35)
                 || (51 <= i && i <= 53)) {
        return TileTypeWater;
      } else if ((61 <= i && i <= 78)
                 || (81 <= i && i <= 98)
                 || (101 <= i && i <= 118)) {
        return TileTypeBuilding;
      }
      // Not mapped - must be blank.
      return TileTypeBlank;
    }
};

class TileLayer {
  public:
    Tile ***tiles;
    int grid_width, grid_height;

    TileLayer(int g_width, int g_height) {
      grid_width = g_width;
      grid_height = g_height;

      tiles = new Tile**[grid_width];
      for (int i = 0; i < grid_width; i++) {
        tiles[i] = new Tile*[grid_height];
      }
    }

    ~TileLayer() {
      for (int i = 0; i < grid_width; i++) {
        for (int j = 0; j < grid_height; j++) {
          delete tiles[i][j];
        }
        delete[] tiles[i];
      }
      delete[] tiles;
    }
};

typedef enum {
  TriggerTypeUnknown,
  TriggerTypeNavigation
} TriggerType;

class Trigger {
  public:
    std::string name;
    TriggerType type;

    Trigger(std::string& tName, TriggerType tType) {
      name = tName;
      type = tType;
    }

    static TriggerType triggerTypeFromString(std::string& str) {
      if (str == "navigation") {
        return TriggerTypeNavigation;
      }
      return TriggerTypeUnknown;
    }
};

int main(int argc, char **argv) {
  std::ifstream json_str("sample.json", std::ifstream::binary);

  Json::Value root;
  Json::Reader reader;
  bool success = reader.parse(json_str, root);
  if (!success) {
    std::cout << "Failed to parse JSON:\n"
      << reader.getFormattedErrorMessages();
    return 1;
  }

  int map_width = root["width"].asInt();
  int map_height = root["height"].asInt();
  int tile_size = root["tilewidth"].asInt();

  // These will be stored by the game state
  std::vector<TileLayer *> tile_layers;
  std::vector<Trigger *> triggers;

  Json::Value layers_elem = root["layers"];
  for (int i = 0; i < layers_elem.size(); i++) {
    Json::Value layer_elem = layers_elem[i];
    std::string type = layer_elem["type"].asString();
    int layer_width = layer_elem["width"].asInt();
    int layer_height = layer_elem["height"].asInt();

    if (type == "tilelayer") {
      TileLayer *tile_layer = new TileLayer(layer_width, layer_height);
      Json::Value data = layer_elem["data"];
      int row = 0, col = 0;
      for (int j = 0; j < data.size(); j++) {
        int tile_id = data[j].asInt();
        tile_layer->tiles[col][row] = new Tile(tile_id);
        col = (col + 1) % layer_width;
        if (col == 0) {
          row++;
        }
      }

      tile_layers.push_back(tile_layer);
    } else if (type == "objectgroup") {
      std::string group_name = layer_elem["name"].asString();
      if (group_name == "TriggerLayer") {
        Json::Value group_objs = layer_elem["objects"];
        for (int j = 0; j < group_objs.size(); j++) {
          Json::Value group_obj = group_objs[j];
          std::string group_obj_name = group_obj["name"].asString();
          std::string group_obj_type_str = group_obj["type"].asString();
          TriggerType group_obj_type = Trigger::triggerTypeFromString(group_obj_type_str);
          Trigger *trigger = new Trigger(group_obj_name, group_obj_type);
          triggers.push_back(trigger);
        }
      } else {
        fprintf(stderr, "Unrecognized group name: %s\n", group_name.c_str());
      }
    } else {
      fprintf(stderr, "Unrecognized layer type: %s\n", type.c_str());
    } 
  }

  printf("Read %ld tile layers: \n", tile_layers.size());
  for (int i = 0; i < tile_layers.size(); i++) {
    TileLayer *layer = tile_layers[i];
    printf("Layer %d: \n", i);
    for (int j = 0; j < layer->grid_height; j++) {
      for (int k = 0; k < layer->grid_width; k++) {
        Tile *tile = layer->tiles[k][j];
        printf("%3d[%d] ", tile->tile_id, tile->type);
      }
      printf("\n");
    }
    printf("--\n");
  }

  printf("Read %ld triggers: \n", triggers.size());
  for (int i = 0; i < triggers.size(); i++) {
    Trigger *trigger = triggers[i];
    printf("Trigger %d: {name: %s, type: %d}\n", i, trigger->name.c_str(), trigger->type);
  }
  return 0;
}
