#include "pch.h"
#include "CMonsterScript.h"
#include "CCameraScript.h"
#include "MonsterBulletScript.h"
#include "DebugScript.h"
#include "time.h"


CMonsterScript::CMonsterScript()
	: CScript((UINT)SCRIPT_TYPE::MONSTERSCRIPT)
	, HP(10)
	, RandomPos(1)
	, MoveTime(0.f)
	, Bulletbool(false)
	, ShotTime(3.0f)

{
}

CMonsterScript::~CMonsterScript()
{
}



void CMonsterScript::begin()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
	//Vec3 MonsterPos = Transform()->GetRelativePos();
	//Vec3 CameraFront = CameraScript->GetvFront();

	//MonsterPos.z = CameraFront.z * 3000;

	//Transform()->SetRelativePos(MonsterPos);
}

void CMonsterScript::tick()
{
	if (HP <= 0) // 추후 폭발 애니메이션 추가 // 셰이더 맞으면 빨갛게 하이라이트 
	{
		DeathState = true;
		DestroyObject(GetOwner());
		if (Debug != nullptr)
		{
			DestroyObject(Debug);
			DebugScript* DS = Debug->GetScript<DebugScript>();
			DS->SetMonsterScript(nullptr);
		}
	}

	Vec3 MonsterPos = Transform()->GetRelativePos();
	Vec3 CameraRight = CameraScript->GetvRight();
	Vec3 CameraFront = CameraScript->GetvFront();

	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	Vec3 CameraRot = CameraScript->GetOwner()->Transform()->GetRelativeRot();
	//CameraRot.y += XM_PI;
	Transform()->SetRelativeRot(Vec3(CameraRot.x, -CameraRot.y, -CameraRot.z));

	if (abs(MonsterPos.z - CameraPos.z) <= abs(CameraFront.z * 1000))
	{
		MoveTime += DT;
		if (MoveTime >= 1.5f)
		{
			MoveTime = 0.f;
			srand(time(NULL));
			RandomPos = rand() % 2 + 1;
		}

		if (RandomPos == 1)
		{
			MonsterPos -= CameraRight * DT * 100;
			Transform()->SetRelativePos(MonsterPos);
		}
		else // RandomPos == 2 인 경우 
		{
			MonsterPos += CameraRight * DT * 100;
			Transform()->SetRelativePos(MonsterPos);
		}
	}
	else
	{
		Vec3 TarGetDir = (MonsterPos - CameraPos).Normalize();

		MonsterPos -= TarGetDir * DT * 100.f;

		Transform()->SetRelativePos(MonsterPos);

		if (Bulletbool == false) // 총알이 발사중이 아니라면 시간이 흐른다. 
			ShotTime += DT;


		if (ShotTime >= 5.0f && Bulletbool == false)
		{
			ShotTime = 0.f;
			Bulletbool = true;
			CreateMonsterBullet();
		}
	}

	if (test)
	{
		CreateMonsterDebug();
		test = false;
	}
	//{
	//	if (Bulletbool == false)
	//	{
	//		Bulletbool = true;
	//	}
	//}

	//	if (Bullet != nullptr)
	//	{		
	//		Vec3 BulletPos = Bullet->Transform()->GetRelativePos();
	//		Vec3 BulletDir = (BulletPos - CameraPos).Normalize();
	//		BulletPos -= BulletDir * DT * 300.f;
	//		Bullet->Transform()->SetRelativePos(BulletPos);
	//	}
}

void CMonsterScript::BeginOverlap(CCollider2D* _Other)
{
	if (L"Bullet" == _Other->GetOwner()->GetName()) //5방컷
	{
		HP -= 10;
		Check = true;
	}
}

void CMonsterScript::CreateMonsterBullet()
{
	Ptr<CMeshData> BulletMeshData = nullptr;
	Bullet = nullptr;

	BulletMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\08_Uranus.mdat");
	Bullet = BulletMeshData->Instantiate();
	Bullet->Transform()->SetRelativeScale(Vec3(0.1f, 0.1f, 0.1f));
	Bullet->AddComponent(new CCollider2D);
	Bullet->AddComponent(new MonsterBulletScript);
	MonsterBulletScript* MBS = Bullet->GetScript<MonsterBulletScript>();
	MBS->SetPlayerScript(PlayerScript);
	MBS->SetMonsterScript(this);
	Bullet->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	Bullet->Collider2D()->SetOffsetScale(Vec3(10.f, 10.f, 10.f));
	Bullet->SetName(L"MonsterBullet");
	Vec3 MonsterPos = Transform()->GetRelativePos();
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	SpawnGameObject(Bullet, MonsterPos, L"Monster");
}

void CMonsterScript::CreateMonsterDebug()
{
	Debug = new CGameObject;

	Debug->AddComponent(new CTransform);
	Debug->AddComponent(new CMeshRender);
	Debug->AddComponent(new DebugScript);

	DebugScript* DS = Debug->GetScript<DebugScript>();
	DS->SetMonsterScript(this);

	Debug->Transform()->SetRelativeScale(Vec3(700.f, 700.f, 700.f));
	Debug->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

	Debug->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	Debug->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MonsterTargetMtrl"), 0);

	Debug->SetName(L"Debug");
	SpawnGameObject(Debug, Vec3(0.f, 0.f, 0.f), L"TargetAim");
}

