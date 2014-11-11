#include "Engine.h"

Engine::Engine(string levelJson)
    : m_levelJson(levelJson)
    , m_isActive(true)
    , m_levelManager(nullptr)
    , m_timekeeper(new TimeKeeper())
    , m_actionLog(new ActionLog(m_timekeeper))
    , m_gameState(nullptr)
{
    init(m_levelJson);    
}

Engine::~Engine() {}

void Engine::init(string levelJson) {

    TilemapParser parser(levelJson);

    m_gameState = shared_ptr<GameState>(new GameState(
                    parser.getUserID(),
                    parser.getLevelID(),
                    -1,
                    parser.getClassID()
                ));

    auto layers = parser.getTileLayers();
    if (layers.size() == 0) {
        throw runtime_error("No layers parsed");
    }

    m_tileMap = mergeLayers(layers);

    shared_ptr<LevelManager> mgr(new LevelManager(m_tileMap, m_gameState));
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

        m_levelManager->addActor(actor);
        
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

shared_ptr<TileLayer> Engine::mergeLayers(vector<shared_ptr<TileLayer>> layers) {
    // Load and merge layers
    auto layerIt = layers.begin();
    auto layerOne = *layerIt;
    layerIt++;

    while (layerIt != layers.end()) {
        layerOne = layerOne->merge(*layerIt);
        layerIt++;
    }
    return layerOne;
}

bool Engine::startSubmission() {
    if (m_gameState->levelOver()) {
        return false; // Cannot continue to play a finished level
    }

    m_gameState->setCanMove(true); // Renable movement

    return true; // submission can proceed
}

void Engine::endSubmission() {
    // TODO
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

string Engine::getResult() const {
    Json::FastWriter writer;
    auto log = getLog();
    
    // TODO, handle result, class, user, and level ID output

    return writer.write(log);
}

Json::Value Engine::getLog() const {
    auto json = m_actionLog->getJsonLog();
    return m_actionLog->getJsonLog();
}
