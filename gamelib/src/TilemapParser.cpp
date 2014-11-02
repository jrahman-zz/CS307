#include "TilemapParser.h"

#include <iostream>

TilemapParser::TilemapParser() {

}

bool TilemapParser::parse(std::string& json_str) {
	Json::Value root;
	Json::Reader reader;

	tileLayers.clear();
	triggers.clear();	

	bool success = reader.parse(json_str, root);
	if (!success) {
		throw runtime_error("Failed to parse JSON:\n"
		+ reader.getFormattedErrorMessages());
	}

	if (!root.isMember("width")) {
		throw runtime_error("Missing width");
	}
	
	if (!root.isMember("height")) {
		throw runtime_error("Missing height");
	}
	
	if (!root.isMember("tileheight")) {
		throw runtime_error("Missing tileheight");
	}

	if (!root.isMember("tilewidth")) {
		throw runtime_error("Missing tilewidth");
	}

	int map_width = root["width"].asInt();
	int map_height = root["height"].asInt();
	int tile_size = root["tilewidth"].asInt();
	int tile_hsize = root["tileheight"].asInt();

	if (tile_size != tile_hsize) {
		throw runtime_error("Non-square tile prohibited");
	}

	// These will be stored by the game state
	if (!root.isMember("layers")) {
		throw runtime_error("No layers");
	}

	Json::Value layers_elem = root["layers"];
	for (unsigned int i = 0; i < layers_elem.size(); i++) {
		Json::Value layer_elem = layers_elem[i];
    
		if (!layer_elem.isMember("type")) {
			throw runtime_error("No type for layer");
		}

		if (!layer_elem.isMember("width")) {
			throw runtime_error("No width for layer");
		}

		if (!layer_elem.isMember("height")) {
			throw runtime_error("No height for layer");
		}

		string type = layer_elem["type"].asString();
		int layer_width = layer_elem["width"].asInt();
		int layer_height = layer_elem["height"].asInt();

		if (type == "tilelayer") {
			
			if (!layer_elem.isMember("data")) {
				throw runtime_error("No data in tilelayer");
			}			
	
			Json::Value data = layer_elem["data"];
			if (data.size() != map_width * map_height) {
				throw runtime_error("Data array wrong size");
			}

			TileLayer *tile_layer = new TileLayer(layer_width, layer_height);
			int row = 0, col = 0;
      
			for (unsigned int j = 0; j < data.size(); j++) {
				int tile_id = data[j].asInt();
				(*tile_layer)[row][col] = Tile(tile_id);
				col = (col + 1) % layer_width;
				if (col == 0) {
					row++;
				}
			}

			tileLayers.push_back(shared_ptr<TileLayer>(tile_layer));
		} else if (type == "objectgroup") {
			if (!layer_elem.isMember("name")) {
				throw runtime_error("Unnamed object group layer");
			}

			string group_name = layer_elem["name"].asString();
			
			if (group_name == "TriggerLayer") {
				Json::Value group_objs = layer_elem["objects"];
				for (unsigned int j = 0; j < group_objs.size(); j++) {
					Json::Value group_obj = group_objs[j];
					string group_obj_name = group_obj["name"].asString();
					string group_obj_type_str = group_obj["type"].asString();
          
					TriggerType group_obj_type = Trigger::triggerTypeFromString(group_obj_type_str);
					Trigger *trigger = new Trigger(group_obj_name, group_obj_type);
					triggers.push_back(shared_ptr<Trigger>(trigger));
				}
			}
		}
	}

	printf("Read %ld tile layers: \n", tileLayers.size());
	int i = 0;
	for (auto it = tileLayers.begin(); it != tileLayers.end(); it++) {
		auto layer = *it;
		printf("Layer %d: \n", i++);
		for (unsigned int j = 0; j < layer->getHeight(); j++) {
			for (unsigned int k = 0; k < layer->getWidth(); k++) {
				auto tile = (*layer)[j][k];
				printf("%3d[%d] ", tile.getID(), tile.getType());
			}
			printf("\n");
		}
		printf("--\n");
	}

	printf("Read %ld triggers: \n", triggers.size());
	i = 0;
	for (auto it = triggers.begin(); it != triggers.end(); it++) {
		auto trigger = *it;
		printf("Trigger %d: {name: %s, type: %d}\n", i++, trigger->name.c_str(), trigger->type);
	}
	return true;
}

list<shared_ptr<TileLayer>> TilemapParser::getTileLayers() {
	return tileLayers;
}

list<shared_ptr<Trigger>> TilemapParser::getTriggers() {
	return triggers;
}

list<shared_ptr<Actor>> TilemapParser::getActors() {
	return actors;
}

