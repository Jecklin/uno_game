#pragma once

class Transform
{
public:
    virtual bool transform() = 0;
    virtual int srcState() const = 0;
    virtual int tarState() const = 0;
};
