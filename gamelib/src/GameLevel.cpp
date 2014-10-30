#include "GameLevel.h"

GameLevel::GameLevel(shared_ptr<TileMap> tileMap) 
	: m_height(tileMap->height)
	, m_width(tileMap->width)
	, m_tileMap(tileMap)
	, m_actorMap(nullptr)
{
	unsigned int totalSize = m_height * m_width;
	m_actorMap = new shared_ptr<Interactable>[totalSize];
}

shared_ptr<Interactable>& GameLevel::operator[](Position pos) {
	unsigned int index = pos.getX() + pos.getY() * m_width;
	return m_actorMap[i];
}
