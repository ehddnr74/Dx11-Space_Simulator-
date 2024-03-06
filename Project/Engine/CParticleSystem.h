#pragma once
#include "CRenderComponent.h"

#include "ptr.h"
#include "CParticleUpdateShader.h"

class CStructuredBuffer;

class CParticleSystem :
    public CRenderComponent
{
private:
    CStructuredBuffer* m_ParticleBuffer;
    CStructuredBuffer* m_RWBuffer;
    CStructuredBuffer* m_ModuleDataBuffer;

    tParticleModule             m_ModuleData;
    Ptr<CParticleUpdateShader>  m_UpdateCS;

    float                       m_AccTime;

   // bool fTimePerCount = 0.f;

public:
    bool GetSpawnMoudule() { return m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN]; }
    void SetSpawnModule(bool a) { m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::PARTICLE_SPAWN] = a; }

    bool GetScaleChangeMoudule() { return m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::SCALE_CHANGE]; }
    void SetScaleChangeMoudule(bool b) { m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::SCALE_CHANGE] = b; }

    bool GetColorChangeMoudule() { return m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::COLOR_CHANGE]; }
    void SetColorChangeMoudule(bool c) { m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::COLOR_CHANGE] = c; }

    bool GetAddVelocityModule() { return m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY]; }
    void SetAddVelocityModule(bool c) { m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY] = c; }

    bool GetDragModule() { return m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::DRAG]; }
    void SetDragModule(bool c) { m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::DRAG] = c; }

    bool GetNoiseForceModule() { return m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE]; }
    void SetNoiseForceModule(bool c) { m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE] = c; }

    bool GetRenderModule() { return m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::RENDER]; }
    void SetRenderModule(bool c) { m_ModuleData.ModuleCheck[(UINT)PARTICLE_MODULE::RENDER] = c; }

    // SpawnModule
    void SetSpawnRate(int _SpawnRate) { m_ModuleData.SpawnRate = _SpawnRate; }
    int GetSpawnRate() { return m_ModuleData.SpawnRate; }
    void SetSpawnColor(Vec3 _SpawnColor) { m_ModuleData.vSpawnColor = _SpawnColor; }
    Vec3 GetSpawnColor() { return m_ModuleData.vSpawnColor; }
    void SetSpawnScaleMin(Vec3 _SpawnScaleMin) { m_ModuleData.vSpawnScaleMin = _SpawnScaleMin; }
    Vec3 GetSpawnScaleMin() { return m_ModuleData.vSpawnScaleMin; }
    void SetSpawnScaleMax(Vec3 _SpawnScaleMax) { m_ModuleData.vSpawnScaleMax = _SpawnScaleMax; }
    Vec3 GetSpawnScaleMax() { return m_ModuleData.vSpawnScaleMax; }
    void SetSpawnShapeType(int _SpawnShapeType) { m_ModuleData.SpawnShapeType = _SpawnShapeType; }
    int GetSpawnShapeType() { return m_ModuleData.SpawnShapeType; }
    void SetBoxShapeScale(Vec3 _vBoxShapeSacle) { m_ModuleData.vBoxShapeScale = _vBoxShapeSacle; }
    Vec3 GetBoxShapeScale() { return m_ModuleData.vBoxShapeScale; }
    void SetSpace(int _Space) { m_ModuleData.Space = _Space; }
    int GetSpace() { return m_ModuleData.Space; }
    void SetMinLifeTime(float _MinLifeTime) { m_ModuleData.MinLifeTime = _MinLifeTime; }
    float GetMinLifeTime() { return m_ModuleData.MinLifeTime; }
    void SetMaxLifeTime(float _MaxLifeTime) { m_ModuleData.MaxLifeTime = _MaxLifeTime; }
    float GetMaxLifeTime() { return m_ModuleData.MaxLifeTime; }

    //ScaleChangeModule
    void SetStartScale(float _StartScale) { m_ModuleData.StartScale = _StartScale; }
    float GetStartScale() { return m_ModuleData.StartScale; }
    void SetEndScale(float _EndScale) { m_ModuleData.EndScale = _EndScale; }
    float GetEndScale() { return m_ModuleData.EndScale; }

    //ColorChangeModule
    void SetStartColor(Vec3 _vStartColor) { m_ModuleData.vStartColor = _vStartColor; }
    Vec3 GetStartColor() { return m_ModuleData.vStartColor; }
    void SetEndColor(Vec3 _vEndColor) { m_ModuleData.vEndColor = _vEndColor; }
    Vec3 GetEndColor() { return m_ModuleData.vEndColor; }

    //AddVelocityModule
    void SetAddVelocityType(int _AddVelocityType) { m_ModuleData.AddVelocityType = _AddVelocityType; }
    int GetAddVelocityType() { return m_ModuleData.AddVelocityType; }
    void SetSpeed(float _Speed) { m_ModuleData.Speed = _Speed; }
    float GetSpeed() { return m_ModuleData.Speed; }
    void SetVelocityDir(Vec3 _vVelocityDir) { m_ModuleData.vVelocityDir = _vVelocityDir; }
    Vec3 GetVelocityDir() { return m_ModuleData.vVelocityDir; }
    void SetOffsetAngle(float _OffsetAngle) { m_ModuleData.OffsetAngle = _OffsetAngle; }
    float GetOffsetAngle() { return m_ModuleData.OffsetAngle; }

    //DragModule
    void SetStartDrag(float _StartDrag) { m_ModuleData.StartDrag = _StartDrag; }
    float GetStartDrag() { return m_ModuleData.StartDrag; }
    void SetEndDrag(float _EndDrag) { m_ModuleData.OffsetAngle = _EndDrag; }
    float GetEndDrag() { return m_ModuleData.EndDrag; }

    //NoiseForceModule
    void SetNoiseTerm(float _fNoiseTerm) { m_ModuleData.fNoiseTerm = _fNoiseTerm; }
    float GetNoiseTerm() { return m_ModuleData.fNoiseTerm; }
    void SetNoiseForce(float _fNoiseForce) { m_ModuleData.fNoiseForce = _fNoiseForce; }
    float GetNoiseForce() { return m_ModuleData.fNoiseForce; }

    //RenderModule
    void SetVelocityAlignment(bool _VelocityAlignment) { m_ModuleData.VelocityAlignment = _VelocityAlignment; }
    bool GetVelocityAlignment() { return m_ModuleData.VelocityAlignment; }
    void SetVelocityScale(bool _VelocityScale) { m_ModuleData.VelocityScale = _VelocityScale; }
    bool GetVelocityScale() { return m_ModuleData.VelocityScale; }
    void SetMaxVelocityScale(Vec3 _vMaxVelocityScale) { m_ModuleData.vMaxVelocityScale = _vMaxVelocityScale; }
    Vec3 GetMaxVelocityScale() { return m_ModuleData.vMaxVelocityScale; }
    void SetMaxSpeed(float _vMaxSpeed) { m_ModuleData.vMaxSpeed = _vMaxSpeed; }
    float GetMaxSpeed() { return m_ModuleData.vMaxSpeed; }

    // 생성 시 초기 색상 설정
    void SetSpawnInitialColor(Vec3 _vInitialColor) { m_ModuleData.vSpawnColor = _vInitialColor; }
    //void SetTimePerCount(float tpc) { fTimePerCount = tpc; }

public:
    virtual void finaltick() override;
    virtual void render() override;
    virtual void render(UINT _iSubset) override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CParticleSystem);
public:
    CParticleSystem();
    ~CParticleSystem();
};