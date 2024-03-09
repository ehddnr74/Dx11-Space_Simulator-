#pragma once
#include <Engine\CScript.h>
class CCameraScript
    : public CScript
{
private:
    CGameObject* Empty;
    CGameObject* Fadein;
    float       m_fCamSpeed;
    Vec3        OffSet;
    bool        HitPost;
    bool        _Fading;


    // Ä«¸Þ¶ó Shake
    double ShakingTime = 0.f;
    bool Shaking = false;
    float m_force = 0.05f;

    float rangeX = 0.f;
    float rangeY = 0.f;
    float rangeZ = 0.f;

    Vec3 m_OriginRot = Vec3(0.f, 0.f, 0.f);
    bool RandomRangeCheck = false;
    bool OriginRotCheck = false;
    bool ToOriginRot = false;

    void CameraShake(double ShakeTime);
    void RandomRange();


    Vec3 vFront;
    Vec3 vUp;
    Vec3 vRight;

    Vec2 PrevMousePos;
    Vector3 CameraPos;
    CGameObject* Muzzle;
    CGameObject* m_Target;
    CGameObject* HitPostProcess;
    CGameObject* SkyBox;


public:
    virtual void begin() override;
    virtual void tick() override;

    void SetTarget(CGameObject* target) { m_Target = target; }
    void SetMuzzle(CGameObject* muzzle) { Muzzle = muzzle; }
    //void SetOffset(Vec3(Off)) { Offset = Off; }
    //void SetPlayerScript(CPlayerScript ps) { PlayerScript = ps; }

    Vec3 GetvFront() { return vFront; }
    Vec3 GetvUp() { return vUp; }
    Vec3 GetvRight() { return vRight; }

    void SetHitPost(bool hitpost) { HitPost = hitpost; }

    void SetSkyBox(CGameObject* SB) { SkyBox = SB; }
    CGameObject* GetSkyBox() { return SkyBox; }

    CGameObject* GetPlayerEmpty() { return Empty; }

    float GetForce() { return m_force; }
    void SetForce(float force) { m_force = force; }

    bool GetToOriginRot() { return ToOriginRot; }
    void SetToOriginRot(bool TOR) { ToOriginRot = TOR; }
private:
    void Camera3DMove();

    CLONE(CCameraScript);
public:
    CCameraScript();
    ~CCameraScript();
};
