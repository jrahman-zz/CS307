#include "LevelManager.h"

#include <cmath>

LevelManager::LevelManager(TileLayer tilemap)
    : m_tilemap(new TileLayer(tilemap)) 
{}

LevelManager::LevelManager(TileLayer&& tilemap) 
    : m_tilemap(new TileLayer(std::forward<TileLayer>(tilemap)))
{}

bool LevelManager::addActor(Position pos, unsigned int actorID) {
    if (m_actorsID.find(actorID) == m_actorsID.end()) {
        m_actorsID.emplace(actorID, pos);
        m_actors.emplace(pos, actorID);
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
        m_triggers.emplace(trigger->getPosition(), trigger);
        m_triggersID.emplace(trigger->getID(), trigger);
        return true;
    } else {
        return false;
    }
}

bool LevelManager::removeTrigger(unsigned int triggerID) {
    if (m_triggersID.find(triggerID) == m_triggersID.end()) {
        auto pos = m_triggersID[triggerID]->getPosition();
        m_triggers.erase(pos);
        m_triggersID.erase(triggerID);
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

#include <iostream> // DEBUG

/*
 * Validate if the move is possible
 */
bool LevelManager::onPreMove(Moveable& obj, const Position& current, const Position& next) {
    
    if (obj.getID() != m_actors[current]) {
        return false; // Mismatch
    }
    
    // Check if the square is occupied
    if (m_actors.find(next) != m_actors.end()) {
        return false;
    }

    // Check if the square is passable terrain
    // Consult the tilemap
    auto row = next.getY();
    auto col = next.getX();
    bool ret = true;

    switch ((*m_tilemap)[row][col].getType()) {
        case TileType::None:
        case TileType::Blank:
        case TileType::Water:
        case TileType::Building:
            ret = false;
            break;
        case TileType::Terrain:
            ret = true;
            break;
        default:
            ret = false;
    }

    // Check the move distance
    auto deltaX = current.getX() - next.getX();
    auto deltaY = current.getY() - next.getY();
    auto absdiff = abs(deltaX) + abs(deltaY);
    if (absdiff != 1) {
        ret = false;
    }

    // Check for on/off the map
    if (next.getX() < 0 || next.getX() >= m_tilemap->getWidth()) {
        ret = false;
    }

    if (next.getY() < 0 || next.getY() >= m_tilemap->getHeight()) {
        ret = false;
    }

    return ret;
}

/*
 * Actually commit the operation against our data structures
 */
void LevelManager::onPostMove(Moveable& obj, const Position& current) {
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
