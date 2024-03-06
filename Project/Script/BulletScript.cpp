#include "pch.h"
#include "BulletScript.h"
#include "CPlayerScript.h"
#include "CCameraScript.h"
#include "BossScript.h"
#include "BossEmptyScript.h"
#include "BulletParticleScript.h"

BulletScript::BulletScript()
	: CScript((UINT)SCRIPT_TYPE::BULLETSCRIPT)
	, m_TargetObject(nullptr)
	, ShotTime(0.f)
	, OffsetX(0.f, 0.f, 0.f)
	, ShootDir(0.f, 0.f, 0.f)
{
}

BulletScript::~BulletScript()
{			
}

void BulletScript::begin()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
	OffsetX = CameraScript->GetvRight();
	ShootDir = CameraScript->GetvFront();

	Vec3 ParentPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	Vec3 ParentRot = CameraScript->GetOwner()->Transform()->GetRelativeRot();

	ParentPos += OffsetX * 50.f;
	ParentPos += ShootDir * 500.f;

	Transform()->SetRelativeScale(Vec3(0.2f, 0.2f, 0.2f));
	Transform()->SetRelativeRot(Vec3(ParentRot));
	Transform()->SetRelativePos(Vec3(ParentPos));
}

void BulletScript::tick()
{
	ShotTime += DT;

	Vec3 BulletPos = Transform()->GetRelativePos();

	if (PlayerScript->GetBooster())
	{
		BulletPos += (ShootDir * DT * 3000.f) * 2;
	}
	else
	{
		BulletPos += ShootDir * DT * 3000.f;
	}
	Transform()->SetRelativePos(BulletPos);


	if (ShotTime > 2.0f)
	{
		ShotTime = 0.f;
		DestroyObject(GetOwner());
	}

}

void BulletScript::BeginOverlap(CCollider2D* _Other)
{
	CGameObject* pOtherObject = _Other->GetOwner();

	if (L"House" == _Other->GetOwner()->GetName())
	{
		DestroyObject(GetOwner());
	}

	if (L"Monster" == _Other->GetOwner()->GetName())
	{
		DestroyObject(GetOwner());
	}

	if (L"BossEmpty" == _Other->GetOwner()->GetName())
	{
		BossEmptyScript* BES = _Other->GetOwner()->GetScript< BossEmptyScript>();
		bool Col = BES->GetBossScript()->GetColliderCheck();
		if (Col)
		{
			BES->GetBossScript()->SetDamage(10);
			// Particle Object
			Vec3 BulletPos = Transform()->GetRelativePos();
			CGameObject* pParticleObj = new CGameObject;
			pParticleObj->SetName(L"BulletParticle");
			pParticleObj->AddComponent(new CTransform);
			pParticleObj->AddComponent(new CParticleSystem);
			pParticleObj->AddComponent(new BulletParticleScript);

			//pParticleObj->ParticleSystem()->SetTimePerCount(5.f);
			pParticleObj->ParticleSystem()->SetSpawnRate(1);
			pParticleObj->ParticleSystem()->SetSpawnColor(Vec3(0.f,1.f,1.f));
			pParticleObj->ParticleSystem()->SetSpawnScaleMin(Vec3(100.f,100.f,100.f));
			pParticleObj->ParticleSystem()->SetSpawnScaleMax(Vec3(100.f,100.f,100.f));
			pParticleObj->ParticleSystem()->SetSpace(0);
			pParticleObj->ParticleSystem()->SetMinLifeTime(1.0f);
			pParticleObj->ParticleSystem()->SetMaxLifeTime(1.5f);

			pParticleObj->ParticleSystem()->SetScaleChangeMoudule(true);
			pParticleObj->ParticleSystem()->SetStartScale(1.f);
			pParticleObj->ParticleSystem()->SetEndScale(200.f);
			pParticleObj->ParticleSystem()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\particle\\Bubbles99px.png"));
			SpawnGameObject(pParticleObj, BulletPos, 0);
		}
		DestroyObject(GetOwner());
	}

}
