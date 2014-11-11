#ifndef DIALOG_TRIGGER_H
#define DIALOG_TRIGGER_H

#include "json/json.h"
#include "Trigger.h"

class DialogueTrigger : public Trigger {
public:
    DialogueTrigger(Json::Value value);
    virtual ~DialogueTrigger();

protected:

    /*
     * Ban default instantiation
     */
    DialogueTrigger() = delete;

    virtual bool arriveImpl(Interactable& target, shared_ptr<GameState> state);
    virtual bool leaveImpl(Interactable& target, shared_ptr<GameState> state);

private:

    string m_dialogue;
    unsigned int m_sourceActor;
};

#endif
