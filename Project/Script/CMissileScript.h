#pragma once
#include <Engine\CScript.h>
#include "CPlayerScript.h"
#include "CCameraScript.h"
#include "BossScript.h"
#include <DirectXMath.h>

class CMissileScript :
    public CScript
{
private:
    CCameraScript* CameraScript;
    CPlayerScript* PlayerScript;
    CGameObject* MissileEmpty;
    CGameObject* m_TargetObject;
    CGameObject* Camera;

    Vector3 OffsetX;
    Vector3 ShootDir;
    //Vector3 ShootUpDir;
    //Vector3 ShootDownDir;
    //Vector3 ShootRightDir;
    //Vector3 ShootLeftDir;
    double ShotTime;

    double UpdateDirTime = 0.f;

public:

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetTargetObject(CGameObject* m_TO) { m_TargetObject = m_TO; }

    void SetPlayerScript(CPlayerScript* CS) { PlayerScript = CS; }

    XMFLOAT3 QuaternionToEulerAngles(const XMVECTOR& quaternion)
    {
        XMFLOAT3 eulerAngle;
        XMVECTOR rotation = quaternion;
        XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(rotation);
        XMVECTOR eulerVector = XMQuaternionRotationMatrix(rotationMatrix);
        XMFLOAT4 euler;
        XMStoreFloat4(&euler, eulerVector);
        eulerAngle.x = euler.x;
        eulerAngle.y = euler.y;
        eulerAngle.z = euler.z;
        return eulerAngle;
    }


    CLONE(CMissileScript);
public:
    CMissileScript();
    ~CMissileScript();
};

