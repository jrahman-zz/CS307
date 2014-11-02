#include "TilemapParser.h"

#include <iostream>

TilemapParser::TilemapParser() {

}

bool TilemapParser::parse(std::string& json_str) {
	// std::ifstream json_str("sample.json", std::ifstream::binary);
	Json::Value root;
	Json::Reader reader;
	bool success = reader.parse(json_str, root);
	if (!success) {
		throw runtime_error("Failed to parse JSON:\n"
			+ reader.getFormattedErrorMessages());
	}

	int map_width = root["width"].asInt();
	int map_height = root["height"].asInt();
	int tile_size = root["tilewidth"].asInt();

	// These will be stored by the game state
	Json::Value layers_elem = root["layers"];
	for (unsigned int i = 0; i < layers_elem.size(); i++) {
 		Json::Value layer_elem = layers_elem[i];
    
		string type = layer_elem["type"].asString();
		int layer_width = layer_elem["width"].asInt();
		int layer_height = layer_elem["height"].asInt();

		if (type == "tilelayer") {
			TileLayer *tile_layer = new TileLayer(layer_width, layer_height);
			Json::Value data = layer_elem["data"];
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
			} else if (group_name == "ActorLayer") {
				auto group_objs = layer["object"];
				for (unsigned int j = 0; j < group_objs.size(); j++) {
					auto group_obj = group_objs[j];
					auto group_obj_name = group_obj["name"].asString();
					auto group_obj_type = group_obj["type"].asString();
					Interactable* actor = new Interactable()
				}				

			} else {
        		fprintf(stderr, "Unrecognized group name: %s\n", group_name.c_str());
			}
		} else {
			fprintf(stderr, "Unrecognized layer type: %s\n", type.c_str());
		} 
	}

	printf("Read %ld tile layers: \n", tileLayers.size());
	for (int i = 0; i < tileLayers.size(); i++) {

		auto layer = tileLayers[i];
		printf("Layer %d: \n", i);
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
	for (int i = 0; i < triggers.size(); i++) {
	auto trigger = triggers[i];
	printf("Trigger %d: {name: %s, type: %d}\n", i, trigger->name.c_str(), trigger->type);
	}
	return true;
}

vector<shared_ptr<TileLayer>> TilemapParser::getTileLayers() {
	return tileLayers;
}

vector<shared_ptr<Trigger>> TilemapParser::getTriggers() {
	return triggers;
}

vector<shared_ptr<Actor>> TilemapParser::getActors() {
	return actors;
}

