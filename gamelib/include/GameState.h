#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "json/json.h"

class GameState {
public:
    GameState(
            unsigned int userID,
            unsigned int levelID,
            unsigned int nextLevelID,
            unsigned int classID
            );

    Json::Value serialize() const;

    bool canMove() const;
    bool levelOver() const;

    bool getObjectiveInProgress() const;
    unsigned int getTotalObjectives() const;
    unsigned int getCompletedObjectives() const;

    unsigned int getUserID() const;
    unsigned int getLevelID() const;
    unsigned int getNextLevelID() const;
    unsigned int getClassID() const;

    void setCanMove(bool val);
    void setLevelOver(bool val);
    void setNextLevel(unsigned int nextLevel);
    void setObjectiveInProgress(bool inProgress);
    void setCompletedObjectives(unsigned int objectives);
    void setTotalObjectives(unsigned int objectives);
protected:

    GameState() = delete;

    bool m_canMove;
    bool m_levelOver;

    bool m_objectiveInProgress;

    unsigned int m_totalObjectives;
    unsigned int m_completedObjectives;

    unsigned int m_userID;
    unsigned int m_levelID;
    unsigned int m_nextLevelID;
    unsigned int m_classID;
};

#endif
