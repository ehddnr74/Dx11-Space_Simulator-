#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"
#include "CCameraScript.h"
#include "HyperLoopScript_Neptune.h"

class HyperLoopScript_Neptune;
class MiniBossScript : public CScript
{
private:
    enum class ePattern
    {
        Move,
        RightMove,
        LeftMove,
        TelePort
    };

    CPlayerScript* PlayerScript;
    CCameraScript* CameraScript;
    CGameObject* Bullet;
    HyperLoopScript_Neptune* mHyperLoopNeptune;

    int HP;
    int RandomPattern;
    int TeleCount;

    float posX;

    double PatternTime;
    double ShotTime;
    double DelayTime;
    double ReloadingTime;

    bool MiniBoss_Start_Check = false;
    bool Bulletbool;
    bool TeleCheck = false;

    Vec3 MiniBossPos;
    Vec3 CameraRight;
    Vec3 CameraFront;
    Vec3 CameraPos;
    Vec3 CameraRot;
    Vec3 TelePos;
    ePattern mPattern;

public:

    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void Pattern();
    void Move();
    void RightMove();
    void LeftMove();
    void Teleportation();
    void CreateBullet();

    void SetBulletBool(bool b) { Bulletbool = b; }
    void SetPlayerScript(CPlayerScript* CS) { PlayerScript = CS; }
    void SetHyperLoopConnect(HyperLoopScript_Neptune* HLSN) { mHyperLoopNeptune = HLSN; }


    CLONE(MiniBossScript);
public:
    MiniBossScript();
    ~MiniBossScript();
};

