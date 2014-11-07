#ifndef TIME_KEEPER_H
#define TIME_KEEPER_H


class TimeKeeper {

public:
    TimeKeeper();
    unsigned int getTimestep() const;
    void incrementClock();
    void reset();

protected:
    unsigned int m_timestep;

};

#endif
