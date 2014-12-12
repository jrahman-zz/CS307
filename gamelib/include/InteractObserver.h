#ifndef INTERACT_OBSERVER_H
#define INTERACT_OBSERVER_H

class Interactable;

class InteractObserver {
public:
    virtual bool onPreInteract(Interactable& src, Interactable& target) = 0;
    virtual void onPostInteract(Interactable& src, Interactable& target) = 0;
};

#endif
