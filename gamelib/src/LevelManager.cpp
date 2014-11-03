#include "LevelManager.h"

LevelManager::LevelManager(TileLayer tilemap)
    : m_tilemap(new TileLayer(tilemap)) 
{}



LevelManager::LevelManager(TileLayer&& tilemap) 
    : m_tilemap(new TileLayer(std::forward<TileLayer>(tilemap)))
{}

bool LevelManager::addActor(Position pos, unsigned int actorID) {
    if (m_actorsID.find(actorID) == m_actorsID.end()) {
        m_actorsID[actorID] = pos;
        m_actors[pos] = actorID;
        return true;
    } else {
        return false;
    }   
}

bool LevelManager::removeActor(unsigned int actorID) {
    if (m_actorsID.find(actorID) != m_actorsID.end()) {
        auto pos = m_actorsID[actorID];
        m_actors.erase(pos);
        m_actorsID.erase(actorID);
        return true;
    } else {
        return false;
    }
}

bool LevelManager::addTrigger(shared_ptr<Trigger> trigger) {
    if (m_triggersID.find(trigger->getID()) == m_triggersID.end()) {
        m_triggers[trigger->getPosition()] = trigger;
        m_triggersID[trigger->getID()] = trigger;
        return true;
    } else {
        return false;
    }
}

bool LevelManager::removeTrigger(unsigned int triggerID) {
    if (m_triggersID.find(triggerID) == m_triggersID.end()) {
        auto pos = m_triggersID[triggerID]->getPosition();

        return true;
    } else {
        return false;
    }
}

LevelManager::~LevelManager() {
}


/*
 * Validate if the state change is allowed
 */
bool LevelManager::onPreStateChange(Interactable& obj, State current, State next) {
    // TODO
    return true;
}

/*
 * Commit the state change
 */
void LevelManager::onPostStateChange(Interactable& obj, State current) {
    // TODO
}

/*
 * Validate if the move is possible
 */
bool LevelManager::onPreMove(Moveable& obj, Position current, Position next) {
    if (obj.getID() != m_actors[current]) {
        return false; // Mismatch
    }
    
    // Check if the square is occupied
    if (m_actors.find(next) != m_actors.end()) {
        return false;
    }

    // Check if the square is passable terrain
    // Consult the tilemap
    
    return true;
}

/*
 * Actually commit the operation against our data structures
 */
void LevelManager::onPostMove(Moveable& obj, Position current) {
    removeActor(obj.getID());
    addActor(current, obj.getID());
}

/*
 * Validate if the interaction is possible
 */
bool LevelManager::onPreInteract(Interactable& src, Interactable& target) {
    // TODO
    return true;
}

/*
 * Actually commit the operation against our data structures
 */
void LevelManager::onPostInteract(Interactable& src, Interactable& target) {
    // TODO
}
