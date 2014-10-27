#ifndef COMMAND_H
#define COMMAND_H

/*
 * Command is a base class that captures the concept of an
 * abstact command being issued against an object
 * 
 */
class Command {
public:
	Command();
	virtual ~Command() {}
	virtual void execute(Interactable& actor) = 0;
}

#endif // COMMAND_H
