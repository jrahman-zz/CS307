#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "json/json.h"

class GameState {
public:
    GameState(
            int userID,
            int levelID,
            int nextLevelID,
            int classID
            );

    Json::Value serialize() const;

    bool canMove() const;
    bool levelOver() const;

    bool getObjectiveInProgress() const;
    unsigned int getTotalObjectives() const;
    unsigned int getCompletedObjectives() const;

    int getUserID() const;
    int getLevelID() const;
    int getNextLevelID() const;
    int getClassID() const;
    int getCurrentObjectiveID() const;

    void setCanMove(bool val);
    void setLevelOver(bool val);
    void setNextLevel(int nextLevel);
    void setObjectiveInProgress(bool inProgress);
    void setCompletedObjectives(unsigned int objectives);
    void setTotalObjectives(unsigned int objectives);
    void setCurrentObjectiveID(int objectiveID);
protected:

    GameState() = delete;

    bool m_canMove;
    bool m_levelOver;

    bool m_objectiveInProgress;

    unsigned int m_totalObjectives;
    unsigned int m_completedObjectives;
    int m_currentObjectiveID;

    int m_userID;
    int m_levelID;
    int m_nextLevelID;
    int m_classID;
};

#endif
