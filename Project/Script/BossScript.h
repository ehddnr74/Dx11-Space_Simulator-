#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"
#include "CCameraScript.h"
//#include "BossPlanets.h"

class BossScript : public CScript
{

public:
    enum class BossState
    {
        Razer,
        Missile,
        MonsterSpawn,
      //VolcanicAbsorb,
      //SiriusAbsorb,
        TelePort,
        ForceShield,
        Die,
    };

private:
    double InitTime;
    BossState eBossState;
    CCameraScript* CameraScript;
    CPlayerScript* PlayerScript;
    CGameObject* Bullet;
    CGameObject* Missile;
    CGameObject* BossEmpty;
    CGameObject* BossLerpShiled;
    CGameObject* pParticleObj;

    CGameObject* FinalNarShaddaa;
    CGameObject* FinalVolcanic;

   // BossPlanets* NarShaddaaBP;
    //BossPlanets* VolcanicBP;

    vector<int> Count; // 레이저 랜덤카운트 배열 

    int HP;
    double MoveTime;
    double ShotTime;
    double lerpshiledtime = 0.f;
    bool Bulletbool;
    bool RoomEffectCheck;

    bool Ending = false;

    bool Once = false;

    bool LerpShiled = false;

    bool ShiledCheck = false;

    bool ColliderCheck = true;

    bool fading = true;

    bool DestroyParticle = true;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetPlayerScript(CPlayerScript* PS) { PlayerScript = PS; }
    //CPlayerScript* GetPlayerScript() { return PlayerScript; }

    void CreateBossBullet();
    void CreateBossMissile();
    void CreateBossRazer(int Count);
    void CreateRoomEffect();


    void SetBulletBool(bool b) { Bulletbool = b; }

    void SetDamage(int hp) { HP -= hp; }

    int GetHP() { return HP; }

    void SetNarShaddaa(CGameObject* FNS) { FinalNarShaddaa = FNS; }
    void SetVolcanic(CGameObject* FV) { FinalVolcanic = FV; }

    CGameObject* GetNarShaddaa() { return FinalNarShaddaa; }
    CGameObject* GetVolcanic() { return FinalVolcanic; }

    void SetLerp(bool lerp) { LerpShiled = lerp; }
    void SetShiled(CGameObject* shiled) { BossLerpShiled = shiled; }

    void SetColliderCheck(bool CC) { ColliderCheck = CC; }
    bool GetColliderCheck() { return ColliderCheck; }


    CLONE(BossScript);
public:
    BossScript();
    ~BossScript();

private:
    void razer();
    void missile();
    void monsterspawn();
    void teleport();
    void forceshield();
    void die();

};

