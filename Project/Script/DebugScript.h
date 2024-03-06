#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"
#include "CCameraScript.h"

class DebugScript : public CScript
{
private:
    CPlayerScript* PlayerScript;
    CMonsterScript* MonsterScript;
    CCameraScript* CameraScript;
    CGameObject* Debug;

    bool hitCheck = false;
    double mTime;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetMonsterScript(CMonsterScript* MS) { MonsterScript = MS; }

    CLONE(DebugScript);
public:
    DebugScript();
    ~DebugScript();
};

