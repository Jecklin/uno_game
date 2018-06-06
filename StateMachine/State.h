#pragma once
#include "AbstractState.h"

class Transform;
class State
        : public AbstractState
{
public:
    explicit State();
    virtual ~State();

public:
    int state() const;
    int toNextState();

public:
    void addTransform(Transform *transform);
    void removeTransform(Transform *transform);

};
