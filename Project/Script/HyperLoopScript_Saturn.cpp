#include "pch.h"
#include "HyperLoopScript_Saturn.h"
#include "CPlayerScript.h"
#include "CCameraScript.h"
#include "CMonsterScript.h"
#include "HyperLoopScript_Jupiter.h"

HyperLoopScript_Saturn::HyperLoopScript_Saturn()
	: CScript((UINT)SCRIPT_TYPE::HYPERLOOPSCRIPT_SATURN)
	, mTime(0.f)
	, mSetTime(100.f)
	, mSpeed(50000.f)
	, DeathCount(0)
{
}

HyperLoopScript_Saturn::~HyperLoopScript_Saturn()
{
}

void HyperLoopScript_Saturn::begin()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
	HyperLoopStateBox();
}

void HyperLoopScript_Saturn::tick()
{
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();

	if (MonsterSpawnCheck_Tracking)//���� ��ȯ Ÿ�̹� ����
		MonsterSpawnCheck = m_HyperLoop->GetOwner()->GetScript<HyperLoopScript_Jupiter>()->GetSpawnCheck();

	if (Active) //�����۷��� ��� Ȱ��ȭ
	{
		if (BoxState == false)
		{
			BoxState = true; //�����۷��� ���¹ڽ� Ȱ��ȭ
			DestroyObject(light);
			HyperLoopStateBox();
		}

		if (collision) //�÷��̾�� �����۷��� �浹 ���� Ȯ��
		{
			mTime += DT;
			CameraPos.z += DT * mSpeed;

			if (mTime >= mSetTime)
			{
				collision = false;
				HyperLoop_Uranus_MonsterSpawn = true;
				mTime = 0.f;
			}
			CameraScript->Transform()->SetRelativePos(CameraPos);
		}
	}

	if (MonsterSpawnCheck)
	{
		MonsterSpawn(); //���� ��ȯ
		MonsterSpawn_State_Check = true;
		MonsterSpawnCheck = false;
		MonsterSpawnCheck_Tracking = false;
	}

	if (MonsterSpawn_State_Check)
		Destroy = Monster->GetScript<CMonsterScript>()->GetDeath(); //���� Death���� Ȯ��

	if (DeathCount == 1)
		Active = true; //�����۷��� ��� Ȱ��ȭ

	if (Destroy)
	{
		DeathCount += 1;
		Destroy = false;
		MonsterSpawn_State_Check = false; //���Ͱ� Destroy�� �Ʊ� ������ ������ �������� �ȵȴ�.
		collision = false;
	}
}

void HyperLoopScript_Saturn::BeginOverlap(CCollider2D* _Other)
{
	if (L"Empty" == _Other->GetOwner()->GetName())
	{
		collision = true;
	}
}

void HyperLoopScript_Saturn::MonsterSpawn()
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
	SpawnGameObject(Monster, Vec3(250000.f, 0.f, 5995000.f), L"Monster");
}

void HyperLoopScript_Saturn::HyperLoopStateBox()
{
	light = new CGameObject;
	light->SetName(L"HL_Light_Mars");
	light->AddComponent(new CTransform);
	light->AddComponent(new CMeshRender);

	light->Transform()->SetRelativeScale(Vec3(1166.f, 274.f, 272.f));

	light->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CubeMesh"));
	light->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"HyperLoopStateShaderMtrl_Saturn"), 0);

	if (BoxState == false)
	{
		light->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\State\\off.png"));
	}
	else
	{
		light->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\State\\on.png"));
	}

	SpawnGameObject(light, Vec3(250007.f, -2556.f, 5999330.f), L"HL_Light");
}

