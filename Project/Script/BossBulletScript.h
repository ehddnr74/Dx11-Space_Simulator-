#pragma once
#include "CPlayerScript.h"
#include "CCameraScript.h"
#include "BossScript.h"

class BossBulletScript : public CScript
{
private:
    CCameraScript* CameraScript;
    BossScript* mBossScript;
    CPlayerScript* PlayerScript;
    CGameObject* m_TargetObject;
    CGameObject* Camera;

    Vector3 OffsetX;
    Vector3 ShootDir;
    double ShotTime;
    double BulletLife;


    bool BulletCheck = false;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetPlayerScript(CPlayerScript* PS) { PlayerScript = PS; }
    void SetBossScript(BossScript* CS) { mBossScript = CS; }

    CLONE(BossBulletScript);
public:
    BossBulletScript();
    ~BossBulletScript();
};

