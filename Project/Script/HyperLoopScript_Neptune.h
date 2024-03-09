#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"
#include "CCameraScript.h"

class HyperLoopScript_Uranus;
class HyperLoopScript_Neptune : public CScript
{
private:
    CCameraScript* CameraScript;
    CPlayerScript* PlayerScript;
    CGameObject* m_TargetObject;
    CGameObject* Camera;
    CGameObject* light;

    HyperLoopScript_Uranus* m_HyperLoop;

    Ptr<CMeshData> MonsterMeshData = nullptr;
    CGameObject* Monster = nullptr;

    bool collision = false;
    bool Active = false;
    bool Destroy;
    bool MonsterSpawn_State_Check = false; //���� �׾����� ��Ҵ��� üũ
    bool MonsterSpawnCheck = false; //���� ��ȯ ���� ����
    bool MonsterSpawnCheck_Tracking = true; // MonsterSpawnCheck ���� Ȱ��ȭ
    bool BoxState = false; //�����۷��� Ȱ��ȭ ���� ǥ�� �ڽ�
    bool MiniBoss_State = false;

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
    void SetHyperLoopConnet(HyperLoopScript_Uranus* HLS) { m_HyperLoop = HLS; }

    bool GetMiniBossState() { return MiniBoss_State; }

    CLONE(HyperLoopScript_Neptune);
public:
    HyperLoopScript_Neptune();
    ~HyperLoopScript_Neptune();

};

