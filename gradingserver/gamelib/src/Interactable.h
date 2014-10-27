#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include "Position.h"
#include "Util.h"

class Interactable {

public:
	Interactable();
	~Interactable();

	template<class T>
	bool 

	enum class State { ALIVE, DEAD, INACTIVE };

protected:
	unsigned int ID;
	struct Position position;
	State currentState;
	
	template<class T>
	void interact(std::shared_ptr<T> target);

private:
	

}


#endif // INTERACTABLE_H
