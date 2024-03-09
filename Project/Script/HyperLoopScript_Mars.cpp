#include "pch.h"
#include "HyperLoopScript_Mars.h"
#include "CPlayerScript.h"
#include "CCameraScript.h"
#include "CMonsterScript.h"
#include "HyperLoopScript.h"

HyperLoopScript_Mars::HyperLoopScript_Mars()
	: CScript((UINT)SCRIPT_TYPE::HYPERLOOPSCRIPT_MARS)
	, mTime(0.f)
	, mSetTime(100.f)
	, mSpeed(50000.f)
	, DeathCount(0)
{
}

HyperLoopScript_Mars::~HyperLoopScript_Mars()
{
}


void HyperLoopScript_Mars::begin()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
	HyperLoopStateBox();

}

void HyperLoopScript_Mars::tick()
{
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();

	if (MonsterSpawnCheck_Tracking)//몬스터 소환 타이밍 추적
		MonsterSpawnCheck = m_HyperLoop->GetOwner()->GetScript<HyperLoopScript>()->GetSpawnCheck();

	if (Active) //하이퍼루프 기능 활성화
	{
		if (BoxState == false)
		{
			BoxState = true; //하이퍼루프 상태박스 활성화
			DestroyObject(light);
			HyperLoopStateBox();
		}

		if (collision) //플레이어와 하이퍼루프 충돌 상태 확인
		{
			mTime += DT;
			CameraPos.z += DT * mSpeed;

			if (mTime >= mSetTime)
			{
				collision = false;
				HyperLoop_Jupiter_MonsterSpawn = true;
				mTime = 0.f;
			}
			CameraScript->Transform()->SetRelativePos(CameraPos);
		}
	}

	if (MonsterSpawnCheck)
	{
		MonsterSpawn_01(); //몬스터 소환
		MonsterSpawn_State_Check = true;
		MonsterSpawnCheck = false;
		MonsterSpawnCheck_Tracking = false;
	}

	if (DeathCount == 1)
	{
		Destroy = false;
		MonsterSpawn_State_Check = false; //몬스터가 Destroy가 됐기 때문에 정보를 가져오면 안된다.
		//collision = false;
	}

	if (MonsterSpawn_State_Check)
		Destroy = Monster->GetScript<CMonsterScript>()->GetDeath(); //몬스터 Death상태 확인

	if (DeathCount == 1)
		Active = true; //하이퍼루프 기능 활성화

	if (Destroy)
	{
		DeathCount += 1;
		Destroy = false;
	}
}

void HyperLoopScript_Mars::BeginOverlap(CCollider2D* _Other)
{
	if (L"Empty" == _Other->GetOwner()->GetName())
	{
		collision = true;
	}
}

void HyperLoopScript_Mars::MonsterSpawn_01()
{
	MonsterMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\kkkkkkk.fbx");
	Monster = MonsterMeshData->Instantiate();
	Monster->AddComponent(new CMonsterScript);
	Monster->AddComponent(new CCollider2D);

	CMonsterScript* MS = Monster->GetScript<CMonsterScript>();
	MS->SetPlayerScript(PlayerScript);

	Monster->Transform()->SetRelativeScale(Vec3(80.f, 80.f, 80.f));
	//Monster->Transform()->SetRelativeRot(Vec3(0.f, XM_PI, 0.f));

	Monster->Collider2D()->SetOffsetPos(Vec3(0.f, 1.f, 1.f));
	Monster->Collider2D()->SetOffsetScale(Vec3(10.f, 10.f, 10.f));
	Monster->SetName(L"Monster");
	SpawnGameObject(Monster, Vec3(250000, 0.f, 2495000.f), L"Monster");
}

void HyperLoopScript_Mars::HyperLoopStateBox()
{
	light = new CGameObject;
	light->SetName(L"HL_Light_Mars");
	light->AddComponent(new CTransform);
	light->AddComponent(new CMeshRender);

	light->Transform()->SetRelativeScale(Vec3(1166.f, 274.f, 272.f));

	light->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CubeMesh"));
	light->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"HyperLoopStateShaderMtrl_Mars"), 0);

	if (BoxState == false)
	{
		light->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\State\\off.png"));
	}
	else
	{
		light->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\State\\on.png"));
	}

	SpawnGameObject(light, Vec3(250007.f, -2556.f, 2499330.f), L"HL_Light");
}
