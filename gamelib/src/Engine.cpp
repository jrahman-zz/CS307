#include "Engine.h"

#include "MoveMessage.h"

Engine::Engine(string levelJson)
    : m_levelJson(levelJson)
    , m_isActive(true)
    , m_heroID(0)
{
    Init(levelJson);    
}

Engine::~Engine() {}

void Engine::Init(string levelJson) {
    
    // Reset
    m_actors.clear();
    m_actorID.clear();
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
        m_triggers[get<0>(*trigger_it)] = get<1>(*trigger_it);
        trigger_it++;
    }

    // Load actors into map
    auto actors = parser.getActors();
    auto actor_it = actors.begin();
    while (actor_it != actors.end()) {
        m_actors[get<0>(*actor_it)] = get<1>(*actor_it);
        actor_it++;
    }
}

shared_ptr<WorldFascade> Engine::getWorld() const {
    shared_ptr<Engine> self(const_cast<Engine*>(this));
    shared_ptr<WorldFascade> world(new WorldFascade(self));
    return world;
}

shared_ptr<HeroFascade> Engine::getHero() const {
    shared_ptr<Engine> self(const_cast<Engine*>(this));
    shared_ptr<HeroFascade> hero(new HeroFascade(self, getHeroID()));
    return hero;
}

bool Engine::executeCommand(unsigned int actorID, shared_ptr<Command> cmd) {
    // TODO, how will this integrate with the logging mechanism
    
    auto actor = m_actors[Position(0, 0)];
    auto log_entry = (*cmd)(*actor);
    
    m_log->log(log_entry);
    return log_entry->getResult();
}

bool Engine::sendMessage(BaseMessage *msg) {

    // TODO, fill this out
    auto type = msg->getType();
    if (type == MessageType::MOVE) {
        MoveMessage* m = dynamic_cast<MoveMessage*>(msg);
        auto target_id = m->getTarget();
        auto target = m_actorID[target_id];
        auto actor = dynamic_pointer_cast<Moveable>(get<1>(target));
        if (actor == nullptr) {
            // TODO, handle badness
            return false;
        }
    }
    return true;
}

void Engine::resetEngine() {

    Init(m_levelJson);
}

unsigned int Engine::getTimestep() const {
    return m_timestep;
}

unsigned int Engine::getHeroID() const {
    return m_heroID;
}

shared_ptr<ActionLog> Engine::getActionLog() const {
    return m_log;
}
