#include "Interactable.h"

Interactable::Interactable(unsigned int actorID, Engine* engineRef, State startState)
	: m_ID(actorID)
	, m_currentState(startState)
	, m_engine(engineRef)
{}

Interactable::~Interactable() {}
