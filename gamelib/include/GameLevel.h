#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <memory>
#include <string>
#include <vector>

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
		unsigned int index = position.getX() + position.getY() * m_width;
		if (index >= m_width * m_height) {
			throw std::exception();
		}
        	return m_actorMap[index];
	}

	Tile* operator[](unsigned int i) {
		return (*m_tileMap)[i];
	}

private:

	shared_ptr<Interactable> *m_actorMap;
	shared_ptr<TileLayer> m_tileMap;
	vector<shared_ptr<Trigger>> m_triggers;
	unsigned int m_height;
	unsigned int m_width;

};


#endif // GAME_LEVEL_H
