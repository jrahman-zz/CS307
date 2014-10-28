#include <json/json.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

class Tile {
  public:
    int tile_id;

    Tile() {
      tile_id = 0;
    }

    Tile(int id) {
      tile_id = id;
    }
};

class TileLayer {
  public:
    Tile **tiles;
    int grid_width, grid_height;

    TileLayer(int g_width, int g_height) {
      grid_width = g_width;
      grid_height = g_height;

      tiles = new Tile*[grid_width];
      for (int i = 0; i < grid_width; i++) {
        tiles[i] = new Tile[grid_height];
      }
    }

    ~TileLayer() {
      for (int i = 0; i < grid_width; i++) {
        delete[] tiles[i];
      }
      delete[] tiles;
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

  std::vector<TileLayer *> tile_layers;

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
        printf("j: %d\n", j);
        int tile_id = data[j].asInt();
        Tile tile(tile_id);
        tile_layer->tiles[col][row] = tile;
        col = (col + 1) % layer_height;
        if (col == 0) {
          row++;
        }
        printf("row, col: %d, %d\n", row, col);
      }
      printf("done!\n");

      tile_layers.push_back(tile_layer);
    } else if (type == "objectgroup") {
      
    } else {
      fprintf(stderr, "Unrecognized layer type: %s\n", type.c_str());
    }
  }
  
  return 0;
}
