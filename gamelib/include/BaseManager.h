#ifndef BASE_MANAGER_H
#define BASE_MANAGER_H

#include "BaseMessage.h"

class BaseManager {

public:
	virtual ~BaseManager() {};
	virtual bool sendMessage(BaseMessage* msg) = 0;
protected:
	BaseManager() {}
};

#endif
