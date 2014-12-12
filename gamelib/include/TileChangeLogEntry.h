#ifndef TILE_CHANGE_LOG_ENTRY_H
#define TILE_CHANGE_LOG_ENTRY_H

#include <string>

#include "LogEntry.h"
#include "json/json.h"
#include "Position.h"

using namespace std;

class TileChangeLogEntry : public LogEntry {

public:

    TileChangeLogEntry(int newTileID, Position position);
    TileChangeLogEntry() = delete;
    virtual ~TileChangeLogEntry();

protected:
    Json::Value serialize() override;
    string getType() override;

private:
    int m_newTileID;
    Position m_position;
};

#endif
