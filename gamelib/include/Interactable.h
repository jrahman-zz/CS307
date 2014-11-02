#ifndef INTERACTABLE_H
#define INTERACTABLE_H

#include <memory>
#include <string>

#include "json/json.h"
#include "Position.h"
#include "Util.h"

using namespace std;

enum class InteractableType { HERO };

class Interactable {
public:
	virtual ~Interactable();

	unsigned int getID();
	InteractableType getType();

	static InteractableType getInteractableType(string type);
	static shared_ptr<Interactable> createFromJson(InteractableType type, Json::Value val);

protected:

	Interactable(Json::Value value);

	unsigned int m_ID;
	State m_state;
	
	template<class T>
	void interact(std::shared_ptr<T> source);

	InteractableType m_type;

};


#endif // INTERACTABLE_H
