#include "TimeKeeper.h"

TimeKeeper::TimeKeeper()
    : m_timestep(0)
{}

unsigned int TimeKeeper::getTimestep() const {
    return m_timestep;
}

void TimeKeeper::incrementClock() {
    m_timestep++;
}

void TimeKeeper::reset() {
    m_timestep = 0;
}


