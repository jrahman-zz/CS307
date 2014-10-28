#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <memory>

#include "Util.h"

class Interactable {

public:
	Interactable(unsigned int x, unsigned int y, unsigned int actorID, State startState);
	virtual ~Interactable();

protected:
	unsigned int ID;
	unsigned int x, y;
	State currentState;
	
	template<class T>
	void interact(std::shared_ptr<T> source);

private:
	

};


#endif // INTERACTABLE_H
