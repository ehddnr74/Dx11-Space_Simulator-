#include "pch.h"
#include "HitPostScript.h"
#include "CCameraScript.h"

HitPostScript::HitPostScript()
	: CScript((UINT)SCRIPT_TYPE::HITPOSTSCRIPT)
	, HitPostProcessTime(0.f)
	, ratio(0.7f)
{
}

HitPostScript::~HitPostScript()
{
}

void HitPostScript::begin()
{
}

void HitPostScript::tick()
{
	ratio -= DT * 1.0f;
	GetOwner()->MeshRender()->SetHitRatio(ratio);

	HitPostProcessTime += DT;

	if (HitPostProcessTime >= 1.f)
	{
		DestroyObject(GetOwner());
	}
}

void HitPostScript::BeginOverlap(CCollider2D* _Other)
{
}
