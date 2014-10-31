#include "GameLevel.h"

GameLevel::GameLevel(string levelJson) 
	: m_actorMap(nullptr)
{
	TilemapParser parser;
	if (!parser.parse(levelJson)) {
		throw std::exception();	
	}

	auto layers = parser.getTileLayers();	
	if (layers.size() == 0) {
		throw std::runtime_error("No layers parsed");
	}

	auto it = layers.begin();
	auto layerOne = *it;
	while (it++ != layers.end()) {
		layerOne = layerOne->merge(**it);
	}
	m_tileMap = layerOne;

	m_triggers = parser.getTriggers();

	unsigned int totalSize = m_height * m_width;
	m_actorMap = new shared_ptr<Interactable>[totalSize];
}


GameLevel::~GameLevel() {
	delete[] m_actorMap;
}
