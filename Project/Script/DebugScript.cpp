#include "pch.h"
#include "DebugScript.h"
#include "CMonsterScript.h"
#include "CCameraScript.h"
#include "time.h"
DebugScript::DebugScript()
	: CScript((UINT)SCRIPT_TYPE::DEBUGSCRIPT)
	, mTime(0.f)
{
}

DebugScript::~DebugScript()
{
}

void DebugScript::begin()
{
	PlayerScript = MonsterScript->GetPlayerScript();
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
}

void DebugScript::tick()
{
	if (MonsterScript != nullptr)
	{
		hitCheck = MonsterScript->GetCheck();

		Vec3 MonsterPos = MonsterScript->GetOwner()->Transform()->GetRelativePos();
		Vec3 CameraRight = CameraScript->GetvRight();
		Vec3 CameraFront = CameraScript->GetvFront();

		Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
		Vec3 CameraRot = CameraScript->GetOwner()->Transform()->GetRelativeRot();

		if (hitCheck)
		{
			mTime += DT;
			Transform()->SetRelativeScale(Vec3(0.f, 0.f, 0.f));

			if (mTime >= 1.5f)
			{
				MonsterScript->SetCheck(false);
				mTime = 0.f;
			}
		}

		if (hitCheck == false)
		{
			if (abs(MonsterPos.z - CameraPos.z) <= abs(CameraFront.z * 2000))
			{
				Transform()->SetRelativeScale(Vec3(0.f, 0.f, 0.f));
			}
			else
			{
				Transform()->SetRelativeScale(Vec3(700.f, 700.f, 700.f));
			}
		}

		Transform()->SetRelativePos(MonsterPos);
	}
}

void DebugScript::BeginOverlap(CCollider2D* _Other)
{

}
