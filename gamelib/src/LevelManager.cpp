#include "LevelManager.h"

#include <cmath>

LevelManager::LevelManager(shared_ptr<TileLayer> tilemap, shared_ptr<GameState> gameState)
    : m_tilemap(tilemap)
    , m_gameState(gameState)
{}

bool LevelManager::addActor(shared_ptr<Interactable> actor) {
    auto actorID = actor->getID();
    auto pos = actor->getPosition();

    if (m_actorsID.find(actorID) == m_actorsID.end()) {
        m_actorsID.emplace(actorID, actor);
        m_actors.emplace(pos, actor);
        return true;
    } else {
        return false;
    }   
}

bool LevelManager::removeActor(unsigned int actorID) {
    if (m_actorsID.find(actorID) != m_actorsID.end()) {
        auto pos = m_actorsID[actorID]->getPosition();
        return m_actorsID.erase(actorID) && m_actors.erase(pos);
    } else {
        return false;
    }
}

bool LevelManager::removeActor(Position pos) {
    if (m_actors.find(pos) != m_actors.end()) {
        auto id = m_actors[pos]->getID();
        return m_actors.erase(pos) && m_actorsID.erase(id);
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
        return m_triggersID.erase(triggerID) && m_triggers.erase(pos);
    } else {
        return false;
    }
}

LevelManager::~LevelManager() {
}


/*
 * Validate if the state change is allowed
 */
bool LevelManager::onPreStateChange(Interactable& obj, State next) {
    // TODO
    return true;
}

/*
 * Commit the state change
 */
void LevelManager::onPostStateChange(Interactable& obj, State old) {
    // TODO
}

/*
 * Validate if the move is possible
 */
bool LevelManager::onPreMove(Moveable& obj, Position next) {
    
    auto current = obj.getPosition();
    if (m_actors.find(current) == m_actors.end()) {
        return false;
    }

    if (obj.getID() != m_actors[current]->getID()) {
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
    
    // Check for on/off the map
    if (next.getX() < 0 || next.getX() >= m_tilemap->getWidth()) {
        return false;
    }

    if (next.getY() < 0 || next.getY() >= m_tilemap->getHeight()) {
        return false;
    }

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

    // Incorporate game state into decision
    ret = ret && !m_gameState->levelOver() && m_gameState->canMove();

    return ret;
}

/*
 * Actually commit the operation against our data structures
 */
void LevelManager::onPostMove(Moveable& obj, Position old) {
    auto actor = m_actorsID[obj.getID()];
    removeActor(old);
    addActor(actor);

    auto current = actor->getPosition();
    if (current != old) {
        runTriggers(actor, old);
    }
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

/*
 * Run all required trigger hooks
 */
void LevelManager::runTriggers(shared_ptr<Interactable> actor, Position old) {
    
    auto current = actor->getPosition();
    auto it = m_triggers.find(current);
    if (it != m_triggers.end()) {
        m_triggers[current]->arrive(*actor, m_gameState);
    }

    it = m_triggers.find(old);
    if (it != m_triggers.end()) {
        m_triggers[old]->leave(*actor, m_gameState);
    }
}
