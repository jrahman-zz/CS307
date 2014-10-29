#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <memory>

#include "Position.h"
#include "Util.h"


class Engine;

class Interactable {

public:
	Interactable(
		Position position,
		unsigned int actorID,
		std::weak_ptr<Engine> engineRef,
		State startState = State::ALIVE);
	virtual ~Interactable();

protected:
	unsigned int ID;
	Position position;
	State currentState;
	std::weak_ptr<Engine> engine;
	
	template<class T>
	void interact(std::shared_ptr<T> source);

private:
	

};


#endif // INTERACTABLE_H
