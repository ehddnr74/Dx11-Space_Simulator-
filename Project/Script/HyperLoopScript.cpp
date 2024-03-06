#include "pch.h"
#include "HyperLoopScript.h"
#include "CPlayerScript.h"
#include "CCameraScript.h"

HyperLoopScript::HyperLoopScript()
	: CScript((UINT)SCRIPT_TYPE::HYPERLOOPSCRIPT)
	, mTime(0.f)
{
}

HyperLoopScript::~HyperLoopScript()
{
}

void HyperLoopScript::begin()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
}

void HyperLoopScript::tick()
{
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();

	if (Active)
	{
		if (collision)
		{
			mTime += DT;
			CameraPos.z += DT * 5000.f;

			if (mTime >= 5.f)
			{
				collision = false;
				mTime = 0.f;
			}
			CameraScript->Transform()->SetRelativePos(CameraPos);
		}
	}
}

void HyperLoopScript::BeginOverlap(CCollider2D* _Other)
{
	if (L"Empty" == _Other->GetOwner()->GetName())
	{
		collision = true;
	}
}
