#include "GameState.h"

GameState::GameState(
    unsigned int userID,
    unsigned int levelID,
    unsigned int nextLevelID,
    unsigned int classID    
    )
    : m_levelOver(false)
    , m_canMove(true)
    , m_objectiveInProgress(false)
    , m_totalObjectives(0)
    , m_completedObjectives(0)
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
    root["completed"] = m_levelOver;

    return root;
}

bool GameState::canMove() const {
    return m_canMove && !m_objectiveInProgress;
}

bool GameState::levelOver() const {
    return m_levelOver;
}

bool GameState::getObjectiveInProgress() const {
    return m_objectiveInProgress;
}

unsigned int GameState::getTotalObjectives() const {
    return m_totalObjectives;
}

unsigned int GameState::getCompletedObjectives() const {
    return m_completedObjectives;
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

void GameState::setObjectiveInProgress(bool value) {
    m_objectiveInProgress = value;
}

void GameState::setTotalObjectives(unsigned int value) {
    m_totalObjectives = value;
}

void GameState::setCompletedObjectives(unsigned int value) {
    m_completedObjectives = value;
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


