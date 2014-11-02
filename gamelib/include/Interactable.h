#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <memory>
#include <string>

#include "json/json.h"
#include "Position.h"
#include "Util.h"

using namespace std;

class Engine;

enum class InteractableType { HERO };

class Interactable {

public:
	Interactable(
		unsigned int actorID,
		State startState = State::ALIVE);
	virtual ~Interactable();

	static InteractableType getInteractableType(string type);
	static shared_ptr<Interactable> createFromJson(InteractableType type, Json::Value val);

protected:
	unsigned int m_ID;
	State m_currentState;
	
	template<class T>
	void interact(std::shared_ptr<T> source);
};


#endif // INTERACTABLE_H
