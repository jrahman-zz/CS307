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

    virtual bool triggerImpl(Interactable& target);
};

#endif
