#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <memory>

#include "Position.h"
#include "Util.h"


class Engine;

class Interactable {

public:
	Interactable(
		unsigned int actorID,
		Engine* engineRef,
		State startState = State::ALIVE);
	virtual ~Interactable();

protected:
	unsigned int m_ID;
	State m_currentState;
	Engine* m_engine;
	
	template<class T>
	void interact(std::shared_ptr<T> source);
};


#endif // INTERACTABLE_H
