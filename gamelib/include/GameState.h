#ifndef GAME_STATE_H
#define GAME_STATE_H

class GameState {
public:
    GameState();

    bool canMove() const;
    bool levelOver() const;

    void setCanMove(bool val);
    void setLevelOver(bool val);
protected:
    bool m_canMove;
    bool m_levelOver;
};

#endif
