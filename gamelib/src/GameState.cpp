#include "GameState.h"

GameState::GameState()
    : m_levelOver(false)
    , m_canMove(true)
{}

bool GameState::canMove() const {
    return m_canMove;
}

bool GameState::levelOver() const {
    return m_levelOver;
}

void GameState::setCanMove(bool value) {
    m_canMove = value;
}

void GameState::setLevelOver(bool value) {
    m_levelOver = value;
}
