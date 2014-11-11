#ifndef DIALOG_TRIGGER_H
#define DIALOG_TRIGGER_H

#include "json/json.h"
#include "Trigger.h"

class DialogueTrigger : public Trigger {
public:
    DialogueTrigger(Json::Value value);

protected:

    /*
     * Bad default instantiation
     */
};

#endif
