#ifndef COMMAND_H
#define COMMAND_H

#include "Interactable.h"

/*
 * Command is a base class that captures the concept of an
 * abstact command being issued against an object
 * 
 */
class Command {
public:
	Command();
	virtual ~Command();
	
	/*
	 * Execute the given command
 	 */
	bool operator()(Interactable& actor) {
		return this->execute(actor);
	}

protected:
	/*
	 * Command implementation is provided here
 	 */
	virtual bool execute(Interactable& actor) = 0;
};

#endif // COMMAND_H
