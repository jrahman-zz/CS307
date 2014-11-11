#include "GameState.h"

GameState::GameState(
    unsigned int userID,
    unsigned int levelID,
    unsigned int nextLevelID,
    unsigned int classID    
    )
    : m_levelOver(false)
    , m_canMove(true)
    , m_userID(userID)
    , m_levelID(levelID)
    , m_nextLevelID(nextLevelID)
    , m_classID(classID)
{}

Json::Value GameState::serialize() const {
    Json::Value root(Json::objectValue);

    root["userID"] = m_userID;
    root["levelID"] = m_levelID;
    root["nextLevel"] = m_nextLevelID;
    root["classID"] = m_classID;

    return root;
}

bool GameState::canMove() const {
    return m_canMove;
}

bool GameState::levelOver() const {
    return m_levelOver;
}

unsigned int GameState::getUserID() const {
    return m_userID;
}

unsigned int GameState::getLevelID() const {
    return m_levelID;
}

unsigned int GameState::getNextLevelID() const {
    return m_nextLevelID;
}

unsigned int GameState::getClassID() const {
    return m_classID;
}

void GameState::setCanMove(bool value) {
    m_canMove = value;
}

void GameState::setLevelOver(bool value) {
    m_levelOver = value;
}

void GameState::setNextLevel(unsigned int levelID) {
    m_nextLevelID = levelID;
}


