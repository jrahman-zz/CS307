#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

#include "Interactable.h"
#include "LogEntry.h"

using namespace std;

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
	shared_ptr<LogEntry> operator()(Interactable& actor) {
		return this->execute(actor);
	}

protected:
	/*
	 * Command implementation is provided here
 	 */
	virtual shared_ptr<LogEntry> execute(Interactable& actor) = 0;
};

#endif // COMMAND_H
