#ifndef ACTOR_OBSERVER_H
#define ACTOR_OBSERVER_H

#include "Position.h"
#include "Util.h"

/* Forward declarations */
class Interactable;
class Moveable;

class ActorObserver {
public:

	ActorObserver() {}
	virtual ~ActorObserver() {}

	virtual bool onPreStateChange(Interactable& obj, State current, State next) = 0;
	virtual void onPostStateChange(Interactable& obj, State current) = 0;

	virtual bool onPreMove(Moveable& obj, Position current, Position next) = 0;
	virtual void onPostMove(Moveable& obj, Position current) = 0;

	virtual bool onPreInteract(Interactable& src, Interactable& target) = 0;
	virtual void onPostInteract(Interactable& src, Interactable& target) = 0;
};

#endif
