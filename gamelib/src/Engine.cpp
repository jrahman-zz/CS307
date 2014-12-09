#include "Engine.h"

#include "ObjectiveTrigger.h"
#include "CompletedObjectiveLogEntry.h"

Engine::Engine(string levelJson)
    : m_levelJson(levelJson) 
    , m_levelManager(nullptr) 
    , m_isActive(true)
    , m_gameState(nullptr)
    , m_timekeeper(new TimeKeeper())
    , m_actionLog(new ActionLog(m_timekeeper))
{
    init(m_levelJson);    
}

Engine::~Engine() {}

void Engine::init(string levelJson) {

    Json::Value root;
    Json::Reader reader;

    if (!reader.parse(levelJson, root)) {
        throw invalid_argument("Invalid JSON:\n" + reader.getFormattedErrorMessages());
    }

    checkInput(root);

    TilemapParser parser(root["level"]);

    m_gameState = shared_ptr<GameState>(new GameState(
                    root["userID"].asInt(),
                    root["levelID"].asInt(),
                    -1,
                    root["classID"].asInt()
                ));

    auto layers = parser.getTileLayers();
    if (layers.size() == 0) {
        throw runtime_error("No layers parsed");
    }

    m_tileMap = mergeLayers(layers);

    shared_ptr<LevelManager> mgr(new LevelManager(m_tileMap, m_gameState));
    m_levelManager = mgr;

    // Load actors
    addActors(parser.getActors());

    // Load triggers into map
    addTriggers(parser.getTriggers()); 
}

void Engine::addTriggers(vector<shared_ptr<Trigger>> triggers) {
     for (auto triggerIt = triggers.begin(); triggerIt != triggers.end(); triggerIt++) {
        auto trigger = *triggerIt;
        trigger->registerLogObserver(m_actionLog);

        // Track and set the objective count
        unsigned int objectiveCount = 0;
        auto objective = dynamic_pointer_cast<ObjectiveTrigger>(trigger);
        if (objective != nullptr) {
            objectiveCount++;
        }

        m_gameState->setTotalObjectives(objectiveCount);

        if (!m_levelManager->addTrigger(*triggerIt)) {
            throw runtime_error("Failed to add trigger");
        }
    }
}

void Engine::addActors(vector<shared_ptr<Interactable>> actors) {
    
    // Load actors into map
    for (auto actorIt = actors.begin(); actorIt != actors.end(); actorIt++) {
        m_actors.push_back(*actorIt);
        auto actor = *actorIt;

        if (!m_levelManager->addActor(actor)) {
            throw runtime_error("Failed to add actor");
        }
        
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
    }
}

shared_ptr<TileLayer> Engine::mergeLayers(vector<shared_ptr<TileLayer>> layers) {
    // Load and merge layers
    auto layerIt = layers.begin();
    auto layerOne = *layerIt;
    layerIt++;

    shared_ptr<TileLayer> backgroundLayer;
    for (auto it = layers.begin(); it != layers.end(); it++) {
        if (!(*it)->getName().compare("BackgroundLayer")) {
            backgroundLayer = *it;
        }
    }

    if (backgroundLayer == nullptr) {
        throw invalid_argument("Missing BackgroundLayer");
    }

    for (auto layerIt = layers.begin(); layerIt != layers.end(); layerIt++) {
        if ((*layerIt)->getName().compare("BackgroundLayer")) {
            backgroundLayer = backgroundLayer->merge(*layerIt);
        }
    }

    return backgroundLayer;
}

bool Engine::startSubmission() {
    if (m_gameState->levelOver()) {
        return false; // Cannot continue to play a finished level
    }

    m_timekeeper->reset(); // Reset clock as well
    m_actionLog->reset(); // Clear any previous log entries

    m_gameState->setCanMove(true); // Renable movement

    return true; // submission can proceed
}

void Engine::endSubmission() {
    // TODO
}

void Engine::checkInput(Json::Value root) {
    if (!root.isMember("level")) {
        throw invalid_argument("No level member");
    }

    if (!root.isMember("userID")) {
        throw invalid_argument("Missing userID");
    }

    if (!root.isMember("levelID")) {
        throw invalid_argument("Missing levelID");
    }
    
    if (!root.isMember("classID")) {
        throw invalid_argument("Missing classID");
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

void Engine::startObjective(int objectiveID) {
    
    m_actionLog->reset();
    m_timekeeper->reset();    
 
    if (m_gameState->getObjectiveInProgress()) {
        throw runtime_error("Cannot start another objective now");
    }

    if (m_gameState->getCurrentObjectiveID() != objectiveID) {
        throw runtime_error("Objective doesn't match expected value");
    }
    m_gameState->setObjectiveInProgress(true);
}

void Engine::endObjective(bool success) {
    if (m_gameState->getObjectiveInProgress()) {
        m_gameState->setObjectiveInProgress(false);

        auto total = m_gameState->getTotalObjectives();
        auto completed = m_gameState->getCompletedObjectives();

        if (completed == total) {
            throw runtime_error("Too many objectives finished, over achiever");
        }

        if (success) {
            m_gameState->setCompletedObjectives(completed + 1);
            m_gameState->setObjectiveInProgress(false);
            auto entry = shared_ptr<CompletedObjectiveLogEntry>(
                    new CompletedObjectiveLogEntry(
                        completed + 1,
                        total));
            m_actionLog->onLog(entry);
        }
    } else {
        throw runtime_error("Start an objective first");
    }
}

void Engine::resetEngine() {

    // Reset data structures
    m_actors.clear();
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

    auto root = m_gameState->serialize();
    root["log"] = getLog();

    return writer.write(root);
}

Json::Value Engine::getLog() const {
    return m_actionLog->getJsonLog();
}
