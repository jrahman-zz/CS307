#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "BaseManager.h"
#include "BaseMessage.h"

class CollisionManager : public BaseManager {
public:
	CollisionManager();
	virtual ~CollisionManager();

	virtual bool SendMessage(BaseMessage* msg);

protected:

private:

}

#endif
