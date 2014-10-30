#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <memory>

#include "Interactable.h"

using namespace std;

/* Game level holds the game state
 *
 *
 * 
 */
class GameLevel {
public:

	GameLevel(TileMap tileMap);
	~GameLevel(TileMap);

	shared_ptr<Interactable>& operator[](Position position) {
		unsigned int index = pos.getX() + pos.getY() * m_width;
		if (index >= m_width * m_height) {
			throw std::exception;
		}
        	return m_actorMap[i];
	}

private:

	shared_ptr<Interactable> *m_actorMap;
	shared_ptr<TileMap> m_tileMap;
	unsigned int m_height;
	unsigned int m_width;

};


#endif // GAME_LEVEL_H
