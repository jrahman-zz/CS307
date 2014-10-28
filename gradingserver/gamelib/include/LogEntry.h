#ifndef ACTION_H
#define ACTION_H

#include <memory>
#include "Interactable.h"
#include "json/json.h"

/*
 * Base class for logged action to be reported back to the user
 *
 */
class LogEntry {
public:
	
	LogEntry(unsigned int timestep) : 
		timestep(timestep) {}
	virtual ~Action();
	Json::Value toJson();
protected:
	
	/*
	 * Serialize specific information about the log entry type
	 */
	virtual Json::Value serialize() = 0;
	
	/*
	 * Return a string describing the type of log entry
	 */
	virtual std::string getType() = 0;
private:
	unsigned int timestep;
};

#endif // ACTION_H
