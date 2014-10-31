#include "GameLevel.h"

GameLevel::GameLevel(shared_ptr<TileLayer> tileMap) 
	: m_height(tileMap->getHeight())
	, m_width(tileMap->getWidth())
	, m_tileMap(tileMap)
	, m_actorMap(nullptr)
{
	unsigned int totalSize = m_height * m_width;
	m_actorMap = new shared_ptr<Interactable>[totalSize];
}


GameLevel::~GameLevel() {
	delete[] m_actorMap;
}
