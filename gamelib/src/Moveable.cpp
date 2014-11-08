#include "Moveable.h"

Moveable::Moveable(Json::Value value)
    : Interactable(value)
{}


Moveable::~Moveable() {

}

void Moveable::registerMoveObserver(shared_ptr<MoveObserver> obs) {
    m_moveObserver = obs;
}

bool Moveable::moveUp() {
    return move(Direction::UP);
}

bool Moveable::moveDown() {
    return move(Direction::DOWN);
}

bool Moveable::moveLeft() {
    return move(Direction::LEFT);
}

bool Moveable::moveRight() {
    return move(Direction::RIGHT);
}

bool Moveable::move(Direction direction) {
    int dx = 0, dy = 0;
    switch (direction) {
        case Direction::UP:
            dy = -1;
            break;
        case Direction::DOWN:
            dy = 1;
            break;
        case Direction::LEFT:
            dx = -1;
            break;
        case Direction::RIGHT:
            dx = 1;
            break;
    }

    int x = m_position.getX() + dx;
    int y = m_position.getY() + dy;

    Position next(x, y);
    if (m_moveObserver->onPreMove(*this, m_position, next)) {
        m_position = next;

        shared_ptr<MoveLogEntry> logEntry(new MoveLogEntry(getID(), m_position));
        log(logEntry);
        m_moveObserver->onPostMove(*this, m_position);
        return true;
    }
    return false;
}

