#pragma once
#include <Engine\CScript.h>
#include "MiniBossScript.h"
#include "CPlayerScript.h"
#include "CCameraScript.h"

class MiniBossBulletScript : public CScript
{
private:
    CCameraScript* CameraScript;
    MiniBossScript* mMiniBossScript;
    CPlayerScript* PlayerScript;
    CGameObject* m_TargetObject;
    CGameObject* Camera;

    Vector3 OffsetX;
    Vector3 ShootDir;
    double ShotTime;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetPlayerScript(CPlayerScript* PS) { PlayerScript = PS; }
    void SetMiniBossScript(MiniBossScript* CS) { mMiniBossScript = CS; }

    CLONE(MiniBossBulletScript);
public:
    MiniBossBulletScript();
    ~MiniBossBulletScript();
};

