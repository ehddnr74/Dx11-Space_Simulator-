#pragma once
#include <Engine\CScript.h>
#include "CCameraScript.h"

class BossShiled : public CScript
{
private:
    CCameraScript* CameraScript;

public:

public:
    virtual void begin() override;
    virtual void tick() override;
    virtual void BeginOverlap(CCollider2D* _Other) override;

    void SetCameraScript(CCameraScript* CS) { CameraScript = CS; }

    CLONE(BossShiled);
public:
    BossShiled();
    ~BossShiled();
};



