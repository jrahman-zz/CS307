#pragma once

class Actor {
  private:
    long id;
  public:
    Actor();
    
    virtual void update() = 0;
    virtual ~Actor() {}
};

