#ifndef ACTION_H
#define ACTION_H

#include <memory>
#include "Interactable.h"

/*
 * Base class for logged action to be reported back to the user
 *
 */
class Action {
public:
	Action(std::shared_ptr<Interactable> actor) : actionActor(actor);
	virtual ~Action();
	virtual void toJson();
protected:

private:
	std::shared_ptr<Interactable> actionActor;
};

#endif // ACTION_H
