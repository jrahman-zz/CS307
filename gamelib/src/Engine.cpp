#include "Engine.h"

Engine::Engine(string levelJson)
    : m_levelJson(levelJson)
    , m_isActive(true)
    , m_levelManager(nullptr)
    , m_timekeeper(new TimeKeeper())
{
    shared_ptr<ActionLog> logger(new ActionLog(m_timekeeper));
    m_actionLog = logger;
    init(m_levelJson);    
}

Engine::~Engine() {}

void Engine::init(string levelJson) {

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
        auto actor = *actorIt;
        auto position = actor->getPosition();
        auto id = actor->getID();
        m_levelManager->addActor(position, id);
        
        actor->registerStateObserver(m_levelManager);
        actor->registerInteractObserver(m_levelManager);

        auto moveable = dynamic_pointer_cast<Moveable>(actor);
        if (moveable != nullptr) {
            moveable->registerMoveObserver(m_levelManager);
        }           

        auto loggable = dynamic_pointer_cast<Loggable>(actor);
        if (loggable != nullptr) {
            loggable->registerLogObserver(m_actionLog);
        }

        // Check for hero
        if (actor->getType() == InteractableType::HERO) {
            m_hero = dynamic_pointer_cast<Hero>(actor);
        }
        actorIt++;
    }
}

shared_ptr<WorldFascade> Engine::getWorld() const {
    shared_ptr<Engine> self(const_cast<Engine*>(this));
    shared_ptr<WorldFascade> world(new WorldFascade(self));
    return world;
}

shared_ptr<HeroFascade> Engine::getHero() const {
    if (m_hero == nullptr) {
        throw runtime_error("No hero found");
    }  
    return shared_ptr<HeroFascade>(new HeroFascade(m_hero, m_timekeeper));
}

void Engine::resetEngine() {

    // Reset data structures
    m_actors.clear();
    m_triggers.clear();
    m_hero = nullptr;
    m_actionLog->reset();
    m_timekeeper->reset();

    init(m_levelJson);
}

unsigned int Engine::getTimestep() const {
    return m_timekeeper->getTimestep();
}

string Engine::getLog() const {
    Json::FastWriter writer;
    auto json = m_actionLog->getJsonLog();
    return writer.write(json);
}
