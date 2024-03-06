#pragma once
#include <Engine\CScript.h>
#include "CMonsterScript.h"
#include "CPlayerScript.h"
#include "CCameraScript.h"

class MonsterBulletScript :
    public CScript
{
private:
    CCameraScript* CameraScript;
    CMonsterScript* MonsterScript;
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
    void SetMonsterScript(CMonsterScript* CS) { MonsterScript = CS; }
 
    CLONE(MonsterBulletScript);
public:
    MonsterBulletScript();
    ~MonsterBulletScript();
};

