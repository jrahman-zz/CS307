#ifndef OBJECTIVE_TRIGGER_H
#define OBJECTIVE_TRIGGER_H

#include "json/json.h"

#include "Trigger.h"

class ObjectiveTrigger : public Trigger {
public:
    ObjectiveTrigger(Json::Value value);
    virtual ~ObjectiveTrigger();

protected:

    ObjectiveTrigger() = delete;

    bool arriveImpl(Interactable& target, shared_ptr<GameState> state) override;
    bool leaveImpl(Interactable& target, shared_ptr<GameState> state) override;

private:
    string m_dialogue;
    string m_prompt;
    string m_templateCode;
    int m_objectiveId;
};

#endif
