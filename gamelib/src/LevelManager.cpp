#include "LevelManager.h"

LevelManager::LevelManager(TileLayer tilemap) {

}

LevelManager::LevelManager(TileLayer&& tilemap) {

}

LevelManager::~LevelManager() {
}

bool LevelManager::onPreStateChange(Interactable& obj, State current, State next) {
    // TODO
    return true;
}

void LevelManager::onPostStateChange(Interactable& obj, State current) {
    // TODO
}

bool LevelManager::onPreMove(Moveable& obj, Position current, Position next) {
    // TODO
    return true;
}

void LevelManager::onPostMove(Moveable& obj, Position current) {
    // TODO
}

bool LevelManager::onPreInteract(Interactable& src, Interactable& target) {
    // TODO
    return true;
}

void LevelManager::onPostInteract(Interactable& src, Interactable& target) {
    // TODO
}
