#ifndef LEVEL_EXIT_TRIGGER_H
#define LEVEL_EXIT_TRIGGER_H

#include "json/json.h"

#include "Trigger.h"

class LevelExitTrigger : public Trigger {
public:
    LevelExitTrigger(Json::Value value);
    virtual ~LevelExitTrigger();

protected:

    /*
     * Ban default constructor
     */
    LevelExitTrigger() = delete;

    bool arriveImpl(Interactable& target, shared_ptr<GameState> state) override;
    bool leaveImpl(Interactable& target, shared_ptr<GameState> state) override;

private:
    int m_nextLevelID;
};

#endif
