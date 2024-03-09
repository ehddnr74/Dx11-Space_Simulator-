#include "pch.h"
#include "HyperLoopScript.h"
#include "CPlayerScript.h"
#include "CCameraScript.h"

HyperLoopScript::HyperLoopScript()
	: CScript((UINT)SCRIPT_TYPE::HYPERLOOPSCRIPT)
	, mTime(0.f)
	, mSetTime(100.f)
	, mSpeed(50000.f)
	, DeathCount(0)
{
}

HyperLoopScript::~HyperLoopScript()
{
}

void HyperLoopScript::begin()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
	HyperLoopStateBox();
}

void HyperLoopScript::tick()
{
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();

	if (Active)
	{
		if (BoxState == false)
		{
			BoxState = true; //하이퍼루프 상태박스 활성화
			DestroyObject(light);
			HyperLoopStateBox();
		}

		if (collision)
		{
			mTime += DT;
			CameraPos.z += DT * mSpeed;

			if (mTime >= mSetTime)
			{
				collision = false;
				HyperLoop_Mars_MonsterSpawn = true;
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

void HyperLoopScript::HyperLoopStateBox()
{
	light = new CGameObject;
	light->SetName(L"HL_Light_Mars");
	light->AddComponent(new CTransform);
	light->AddComponent(new CMeshRender);

	light->Transform()->SetRelativeScale(Vec3(1166.f, 274.f, 272.f));

	light->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CubeMesh"));
	light->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"HyperLoopStateShaderMtrl_Moon"), 0);

	if (BoxState == false)
	{
		light->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\State\\off.png"));
	}
	else
	{
		light->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\State\\on.png"));
	}

	SpawnGameObject(light, Vec3(250007.f, -2556.f, 1699330.f), L"HL_Light");
}
