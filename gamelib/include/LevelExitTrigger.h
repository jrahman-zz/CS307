#ifndef LEVEL_EXIT_TRIGGER_H
#define LEVEL_EXIT_TRIGGER_H

#include "json/json.h"

#include "Trigger.h"

class LevelExitTrigger : public Trigger {
public:
    LevelExitTrigger(Json::Value value);
    ~LevelExitTrigger();

protected:

    /*
     * Ban default constructor
     */
    LevelExitTrigger() = delete;

    virtual bool arriveImpl(Interactable& target, shared_ptr<GameState> state);
    virtual bool leaveImpl(Interactable& target, shared_ptr<GameState> state);

private:
    unsigned int m_nextLevelID;
};

#endif
