#pragma once

class AbstractState
{
public:
    virtual int state() const = 0;
    virtual int toNextState() = 0;
};
