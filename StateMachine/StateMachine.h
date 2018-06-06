#pragma once
#include "AbstractState.h"

class GameLoop;
class StateMachine
        : public AbstractState
{
public:
    explicit StateMachine(GameLoop *loop);
    virtual ~StateMachine();

public:
    void init();
    void uninit();

public:
    int state() const;
    int toNextState();
};
