#include "pch.h"
#include "MiniBossBulletScript.h"

MiniBossBulletScript::MiniBossBulletScript()
	: CScript((UINT)SCRIPT_TYPE::MINIBOSSBULLETSCRIPT)
	, m_TargetObject(nullptr)
	, ShotTime(0.f)
	, OffsetX(0.f, 0.f, 0.f)
	, ShootDir(0.f, 0.f, 0.f)
{
}

MiniBossBulletScript::~MiniBossBulletScript()
{
}

void MiniBossBulletScript::begin()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>(); // 카메라스크립트 가져오기 
	//OffsetX = CameraScript->GetvRight(); //카메라의 x축방향
	ShootDir = (mMiniBossScript->GetOwner()->Transform()->GetRelativePos() - CameraScript->GetOwner()->Transform()->GetRelativePos()).Normalize();

	Vec3 ParentPos = CameraScript->GetOwner()->Transform()->GetRelativePos(); // 카메라 위치
	Transform()->SetRelativeScale(Vec3(0.1f, 0.1f, 0.1f));
}

void MiniBossBulletScript::tick()
{
	ShotTime += DT;

	Vec3 BulletPos = Transform()->GetRelativePos();
	BulletPos -= ShootDir * DT * 1000.f;
	Transform()->SetRelativePos(BulletPos);


	if (ShotTime > 5.0f)
	{
		ShotTime = 0.f;
		DestroyObject(GetOwner());
		mMiniBossScript->SetBulletBool(false);
	}
}

void MiniBossBulletScript::BeginOverlap(CCollider2D* _Other)
{
	if (L"Empty" == _Other->GetOwner()->GetName())
	{
		DestroyObject(GetOwner());
		mMiniBossScript->SetBulletBool(false);

		CameraScript->SetHitPost(true);
	}
}
