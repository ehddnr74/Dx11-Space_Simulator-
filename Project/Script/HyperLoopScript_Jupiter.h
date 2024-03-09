#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"
#include "CCameraScript.h"

class HyperLoopScript_Mars;
class HyperLoopScript_Jupiter : public CScript
{
private:
    CCameraScript* CameraScript;
    CPlayerScript* PlayerScript;
    CGameObject* m_TargetObject;
    CGameObject* Camera;
    CGameObject* light;

    HyperLoopScript_Mars* m_HyperLoop;

    Ptr<CMeshData> MonsterMeshData = nullptr;
    CGameObject* Monster = nullptr;

    bool collision = false;
    bool Active = false;
    bool Destroy;
    bool MonsterSpawn_State_Check = false; //몬스터 죽었는지 살았는지 체크
    bool MonsterSpawnCheck = false; //몬스터 소환 가능 상태
    bool MonsterSpawnCheck_Tracking = true; // MonsterSpawnCheck 추적 활성화
    bool HyperLoop_Saturn_MonsterSpawn = false;
    bool BoxState = false; //하이퍼루프 활성화 상태 표시 박스

    double mTime;
    double mSetTime;
    double mSpeed;


    int DeathCount;

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void MonsterSpawn();
    void HyperLoopStateBox();

    void SetActive(bool active) { Active = active; }
    void SetTime(double settime) { mSetTime = settime; }
    void SetSpeed(double speed) { mSpeed = speed; }

    void SetPlayerScript(CPlayerScript* CS) { PlayerScript = CS; }
    void SetHyperLoopConnet(HyperLoopScript_Mars* HLS) { m_HyperLoop = HLS; }

    bool GetSpawnCheck() { return HyperLoop_Saturn_MonsterSpawn; }

    CLONE(HyperLoopScript_Jupiter);
public:
    HyperLoopScript_Jupiter();
    ~HyperLoopScript_Jupiter();
};

