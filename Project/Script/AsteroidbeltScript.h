#pragma once
#include <Engine\CScript.h>

class AsteroidbeltScript : public CScript
{
private:
    const int maxX = 1000000;
    const int maxY = 10000;
    const int minZ = 3000000;
    const int maxZ = 3500000;

    Vec3 Position;
 
    bool Check = true;
public:
    virtual void begin() override;
    virtual void tick() override;

    void PositionRandom();

    Vec3 GetPosition() { return Position; }

    CLONE(AsteroidbeltScript);

public:
    AsteroidbeltScript();
    ~AsteroidbeltScript();
};

