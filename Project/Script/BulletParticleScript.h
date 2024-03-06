#pragma once
#include <Engine\CScript.h>
#include "BulletParticleScript.h"

class BulletParticleScript :
    public CScript
{
private:
    double ParticleTime = 0.f;

public:

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;


    CLONE(BulletParticleScript);
public:
    BulletParticleScript();
    ~BulletParticleScript();
};



