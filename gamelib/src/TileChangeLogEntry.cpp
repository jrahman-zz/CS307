#include "TileChangeLogEntry.h"

TileChangeLogEntry::TileChangeLogEntry(
        int newTileID,
        Position position)
    : LogEntry()
    , m_newTileID(newTileID)
    , m_position(position)
{
}

TileChangeLogEntry::~TileChangeLogEntry()
{}

Json::Value TileChangeLogEntry::serialize() {
    Json::Value root(Json::objectValue);
    root["position"] = m_position.toJson();
    root["tileID"] = m_newTileID;

    return root;
}

string TileChangeLogEntry::getType() {
    return "tilechange";
}
