#include "Engine.h"

Engine::Engine(string levelJson)
    : m_levelJson(levelJson)
    , m_isActive(true)
    , m_heroID(0)
    , m_levelManager(nullptr)
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
    auto layerIt = layers.begin();
    auto layerOne = *layerIt;
    layerIt++;

    while (layerIt != layers.end()) {
        layerOne = layerOne->merge(*layerIt);
        layerIt++;
    }
    m_tileMap = layerOne;

    shared_ptr<LevelManager> mgr(new LevelManager(*m_tileMap));
    m_levelManager = mgr;

    // Load triggers into map
    auto triggers = parser.getTriggers();
    auto triggerIt = triggers.begin();
    while (triggerIt != triggers.end()) {
        m_triggers.push_back(*triggerIt);
        m_levelManager->addTrigger(*triggerIt);
        triggerIt++;
    }

    // Load actors into map
    auto actors = parser.getActors();
    auto actorIt = actors.begin();
    while (actorIt != actors.end()) {
        m_actors.push_back(*actorIt);
        auto position = (*actorIt)->getPosition();
        auto id = (*actorIt)->getID();
        m_levelManager->addActor(position, id);
        actorIt++;
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
