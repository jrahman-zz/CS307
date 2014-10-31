#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <memory>

using namespace std;

#include "Tile.h"
#include "TileLayer.h"
#include "Interactable.h"
#include "Util.h"


/* Game level holds the game state
 *
 *
 * 
 */
class GameLevel {
public:

	GameLevel(shared_ptr<TileLayer> tileMap);
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
	unsigned int m_height;
	unsigned int m_width;

};


#endif // GAME_LEVEL_H
