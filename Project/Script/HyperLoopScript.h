#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"
#include "CCameraScript.h"

class HyperLoopScript : public CScript
{
private:
    CCameraScript* CameraScript;
    CPlayerScript* PlayerScript;
    CGameObject* m_TargetObject;
    CGameObject* light;

    Ptr<CMeshData> MonsterMeshData = nullptr;
    CGameObject* Monster = nullptr;

    bool collision = false;
    bool Active = true;
    bool Destroy;
    bool MonsterSpawnCheck = false;
    bool HyperLoop_Mars_MonsterSpawn = false;
    bool BoxState = true; //하이퍼루프 활성화 상태 표시 박스

    double mTime;
    double mSetTime;
    double mSpeed;


    int DeathCount;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetTime(double settime) { mSetTime = settime; }
    void SetSpeed(double speed) { mSpeed = speed; }
    void HyperLoopStateBox();

    void SetPlayerScript(CPlayerScript* CS) { PlayerScript = CS; }

    bool GetSpawnCheck() { return HyperLoop_Mars_MonsterSpawn; }

    CLONE(HyperLoopScript);
public:
    HyperLoopScript();
    ~HyperLoopScript();
};

