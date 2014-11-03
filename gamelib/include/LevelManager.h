#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <memory>

#include "ActorObserver.h"
#include "Interactable.h"
#include "Moveable.h"
#include "TileLayer.h"
#include "Trigger.h"

using namespace std;

class LevelManager : public ActorObserver {
public:

    explicit LevelManager(TileLayer tilemap);
    explicit LevelManager(TileLayer&& tilemap);
    virtual ~LevelManager();

    /*
     * Hooks for observer pattern
     */
    virtual bool onPreStateChange(Interactable& obj, State current, State next);
    virtual void onPostStateChange(Interactable& obj, State current);

    virtual bool onPreMove(Moveable& obj, Position current, Position next);
    virtual void onPostMove(Moveable& obj, Position current);

    virtual bool onPreInteract(Interactable& src, Interactable& target);
    virtual void onPostInteract(Interactable& src, Interactable& target);

protected:
    shared_ptr<TileLayer> m_tilemap;

private:

};

#endif
