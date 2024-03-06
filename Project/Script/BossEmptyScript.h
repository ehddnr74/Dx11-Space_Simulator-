#pragma once
#include <Engine\CScript.h>
#include "BossScript.h"

class BossEmptyScript :
    public CScript
{
private:
    BossScript* bossScript;
    CGameObject* PlayerEmpty;
public:

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetBossScript(BossScript* BS) { bossScript = BS; }
    BossScript* GetBossScript() { return bossScript; }

    void SetPlayerEmpty(CGameObject* PE) { PlayerEmpty = PE; }

    CLONE(BossEmptyScript);
public:
    BossEmptyScript();
    ~BossEmptyScript();
};


