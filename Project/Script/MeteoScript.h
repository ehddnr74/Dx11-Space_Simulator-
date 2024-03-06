#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"

class MeteoScript :
    public CScript
{
private:
    Vec3 SpawnPosition;

public:

public:
    virtual void begin() override;
    virtual void tick() override;

    Vec3 GetSpawnPosition() { return SpawnPosition; }

    CLONE(MeteoScript);
public:
    MeteoScript();
    ~MeteoScript();
};

