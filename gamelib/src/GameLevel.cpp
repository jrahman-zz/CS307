#include "GameLevel.h"

GameLevel::GameLevel(string levelJson)
{
	TilemapParser parser;
	if (!parser.parse(levelJson)) {
		throw runtime_error("Failed to parse");	
	}

	auto layers = parser.getTileLayers();	
	if (layers.size() == 0) {
		throw runtime_error("No layers parsed");
	}

	// Load and merge layers
	auto layer_it = layers.begin();
	auto layerOne = *layer_it;
	layer_it++;

	while (layer_it != layers.end()) {
		layerOne = layerOne->merge(*layer_it);
		layer_it++;
	}
	m_tileMap = layerOne;

	// Load triggers into map
	auto triggers = parser.getTriggers();
	auto trigger_it = triggers.begin();
	while (trigger_it != triggers.end()) {
		m_triggers[get<0>(*trigger_it)] = get<1>(*trigger_it);
		trigger_it++;
	}

	// Load actors into map
	auto actors = parser.getActors();
	auto actor_it = actors.begin();
	while (actor_it != actors.end()) {
		m_actors[get<0>(*actor_it)] = get<1>(*actor_it);
		actor_it++;
	}
}


GameLevel::~GameLevel() {
}
