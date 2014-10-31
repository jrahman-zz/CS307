#ifndef LOG_ENTRY_H
#define LOG_ENTRY_H

#include <memory>
#include "Interactable.h"
#include "json/json.h"

/*
 * Base class for logged action to be reported back to the user
 *
 */
class LogEntry {
public:
	
	LogEntry(unsigned int timestep, bool result); 
	virtual ~LogEntry();
	
	/*
	 * Serialize the log entry into JSON
 	 */
	Json::Value toJson();

	/*
 	 * Return the timestep for this entry
 	 */
	unsigned int getTimestep();

	bool getResult();
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
	unsigned int m_timestep;
	bool m_result;
};

#endif // LOG_ENTRY_H
