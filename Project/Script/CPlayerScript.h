#pragma once
#include <Engine\CScript.h>
#include "CCameraScript.h"

//#include "CMissileScript.h"
#include <Engine\CFrustum.h>


class CPlayerScript :
    public CScript
{
private:
    CGameObject* Camera;
    CGameObject* Bullet;
    CGameObject* Missile;
    CGameObject* Enemy;
    CCameraScript* CameraScript;
    //CMissileScript* MissileScript;
    Vec2        PrevMousePos;
    float       m_fSpeed;
    bool        m_Booster;

    Vec3        OffSet;
    Vec3        ShootDir;
    Vec3        vFront;

    double BulletTime = 0.f;
    bool BulletCheck = true;
    bool MissileCheck = true;

    CGameObject* m_Target = nullptr;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetBooster(bool Booster) { m_Booster = Booster; }
    bool GetBooster() { return m_Booster; }

    CPlayerScript* GetPlayerScript() { return this; }
    void SetCameraScript(CCameraScript* CS) { CameraScript = CS; }
    CCameraScript* GetCameraScript() { return CameraScript; }

    void SetBullet(CGameObject* bullet) { Bullet = bullet; }

    void SetEnemy(CGameObject* enemy) { Enemy = enemy; }
    Vec3 GetvFront() { return vFront; }

    //void SetMissileScript(CMissileScript* MS) { MissileScript = MS; }
    //CMissileScript* GetMissileScript() { return MissileScript; }
    //void SetBossScript(BossScript* BS) { bossScript = BS; }

    void SetMissileCheck(bool Mcheck) { MissileCheck = Mcheck; }
    void SetBulletCheck(bool Bcheck) { BulletCheck = Bcheck; }

    void SetTarGetObject(CGameObject* tgobj) { m_Target = tgobj; }

private:
    void Shoot();
    void Move();
    void Booster();
    void CreateBullet();
    void CreateMissile();



public:
    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _FILE) override;
    CLONE(CPlayerScript);
public:
    CPlayerScript();
    ~CPlayerScript();
};