#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"
#include "CCameraScript.h"

class CMonsterScript :
    public CScript
{
private:
    CPlayerScript* PlayerScript;
    CCameraScript* CameraScript;
    CGameObject* Bullet;
    CGameObject* Debug;

    double MoveTime;
    double ShotTime;
    int HP;
    int RandomPos;
    bool Bulletbool;

    bool Check = false;

    bool test = true;
    bool DeathState;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetPlayerScript(CPlayerScript* CS) { PlayerScript = CS; }

    void CreateMonsterBullet();

    void CreateMonsterDebug();

    void SetBulletBool(bool b) { Bulletbool = b; }

    void SetCheck(bool a) { Check = a; }

    CPlayerScript* GetPlayerScript() { return PlayerScript; }
    bool GetCheck() { return Check; }
    bool GetDeath() { return DeathState; }

    CLONE(CMonsterScript);
public:
    CMonsterScript();
    ~CMonsterScript();
};


