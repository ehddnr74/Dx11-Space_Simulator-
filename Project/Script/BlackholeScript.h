#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"
#include "CCameraScript.h"

class BlackholeScript : public CScript
{
private:
    CCameraScript* CameraScript;
    CPlayerScript* PlayerScript;
    CGameObject* m_TargetObject;
    CGameObject* Camera;
    CGameObject* Distortion;

    bool Tele_in = false;
    bool Dist = false;

public:

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetPlayerScript(CPlayerScript* CS) { PlayerScript = CS; }

    CLONE(BlackholeScript);
public:
    BlackholeScript();
    ~BlackholeScript();
};

