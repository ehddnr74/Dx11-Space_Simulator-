#pragma once
#include <Engine\CScript.h>
#include "CCameraScript.h"

class HitPostScript : public CScript
{
private:
    CCameraScript* CameraScript;
    CGameObject* Camera;

    double HitPostProcessTime;
    float ratio;

public:

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetCameraScript(CCameraScript* CS) { CameraScript = CS; }

    CLONE(HitPostScript);
public:
    HitPostScript();
    ~HitPostScript();
};


