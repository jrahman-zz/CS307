#ifndef LEVEL_EXIT_TRIGGER_H
#define LEVEL_EXIT_TRIGGER_H

#include "json/json.h"

#include "Trigger.h"

class LevelExitTrigger : public Trigger {
public:
    LevelExitTrigger(Json::Value value);

protected:

};

#endif
