#include "Engine.h"

#include "MoveMessage.h"

Engine::Engine(string levelJson)
    : m_levelJson(levelJson)
    , m_isActive(true)
    , m_heroID(0)
{
    init(levelJson);    
}

Engine::~Engine() {}

void Engine::resetLevel() {
    init(m_levelJson);
}

void Engine::init(string levelJson) {
    
    // Reset data structures
    m_actors.clear();
    m_triggers.clear();

    TilemapParser parser;
    if (!parser.parse(levelJson)) {
        throw runtime_error("Failed to parse");
    }

    auto layers = parser.getTileLayers();
    if (layers.size() == 0) {
        throw runtime_error("No layers parsed");
    }

    // Load and merge layers
    auto layer_it = layers.begin();
    auto layerOne = *layer_it;
    layer_it++;

    while (layer_it != layers.end()) {
        layerOne = layerOne->merge(*layer_it);
        layer_it++;
    }
    m_tileMap = layerOne;

    // Load triggers into map
    auto triggers = parser.getTriggers();
    auto trigger_it = triggers.begin();
    while (trigger_it != triggers.end()) {
        m_triggers.push_back(*trigger_it);
        trigger_it++;
    }

    // Load actors into map
    auto actors = parser.getActors();
    auto actor_it = actors.begin();
    while (actor_it != actors.end()) {
        m_actors.push_back(*actor_it);
        actor_it++;
    }
}

shared_ptr<WorldFascade> Engine::getWorld() const {
    shared_ptr<Engine> self(const_cast<Engine*>(this));
    shared_ptr<WorldFascade> world(new WorldFascade(self));
    return world;
}

shared_ptr<HeroFascade> Engine::getHero() const {
    return nullptr;
}

void Engine::resetEngine() {

    init(m_levelJson);
}

unsigned int Engine::getTimestep() const {
    return m_currentTimestep;
}

unsigned int Engine::getHeroID() const {
    return m_heroID;
}

shared_ptr<ActionLog> Engine::getActionLog() const {
    return m_actionLog;
}
