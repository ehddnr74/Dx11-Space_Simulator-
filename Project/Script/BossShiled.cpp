#include "pch.h"
#include "BossShiled.h"
#include "CCameraScript.h"

BossShiled::BossShiled()
	: CScript((UINT)SCRIPT_TYPE::BOSSSHILED)
{
}

BossShiled::~BossShiled()
{
}

void BossShiled::begin()
{
}

void BossShiled::tick()
{
	Vec3 OwnerRot = Transform()->GetRelativeRot();
	OwnerRot.x += DT * 0.5f;
	Transform()->SetRelativeRot(OwnerRot);

	if (CameraScript != nullptr)
	{
		Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
		Transform()->SetRelativePos(CameraPos);
	}

}

void BossShiled::BeginOverlap(CCollider2D* _Other)
{
}
