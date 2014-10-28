#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "Position.h"
#include "Util.h"

class Interactable {

public:
	Interactable(unsigned int x, unsigned int y, unsigned int actorID, State startState);
	virtual ~Interactable();

protected:
	unsigned int ID;
	State currentState;
	
	template<class T>
	virtual void interact(std::shared_ptr<T> source) = 0;

private:
	

}


#endif // INTERACTABLE_H
