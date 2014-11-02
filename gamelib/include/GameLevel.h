#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <memory>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "Tile.h"
#include "TileLayer.h"
#include "TilemapParser.h"
#include "Interactable.h"
#include "Util.h"

/*
 * Game level holds the game state
 */
class GameLevel {
public:

	GameLevel(string levelJson);
	~GameLevel();

	shared_ptr<Interactable>& operator[](Position position) {
		return m_actors[position];
	}

	Tile* operator[](unsigned int i) {
		return (*m_tileMap)[i];
	}

	shared_ptr<Interactable> getActor(unsigned int i);
private:

	map<unsigned int, shared_ptr<Interactable>> m_actorID;
	map<Position, shared_ptr<Interactable>> m_actors;
	shared_ptr<TileLayer> m_tileMap;
	map<Position, shared_ptr<Trigger>> m_triggers;
	unsigned int m_height;
	unsigned int m_width;

};

#endif // GAME_LEVEL_H
