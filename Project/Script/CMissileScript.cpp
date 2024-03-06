#include "pch.h"
#include "CPlayerScript.h"
#include "CMissileScript.h"
#include "CCameraScript.h"

CMissileScript::CMissileScript()
	: CScript((UINT)SCRIPT_TYPE::MISSILESCRIPT)
	, m_TargetObject(nullptr)
	, ShotTime(0.f)
	, OffsetX(0.f, 0.f, 0.f)
	, ShootDir(0.f, 0.f, 0.f)
{
}

CMissileScript::~CMissileScript()
{

}

void CMissileScript::begin()
{
	MissileEmpty = new CGameObject;
	MissileEmpty->SetName(L"MissileEmpty");
	MissileEmpty->AddComponent(new CTransform);
	MissileEmpty->AddComponent(new CMeshRender);
	MissileEmpty->Transform()->SetRelativeScale(Vec3(0.001f, 0.001f, 0.001f));
	//Empty->Transform()->SetRelativePos()
	MissileEmpty->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	MissileEmpty->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"), 0);

	MissileEmpty->AddComponent(new CCollider2D);
	MissileEmpty->Collider2D()->SetOffsetPos(Vec3(-100000.f, 0.f, 100000.f));
	MissileEmpty->Collider2D()->SetOffsetScale(Vec3(200000.f, 200000.f, 200000.f));

	SpawnGameObject(MissileEmpty, Vec3(0.f, 0.f, 0.f), L"Player");

	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
	OffsetX = CameraScript->GetvRight();
	Vec3 OffsetY = CameraScript->GetvUp();
	ShootDir = CameraScript->GetvFront();
	//ShootUp = 

	Vec3 ParentPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	Vec3 ParentRot = CameraScript->GetOwner()->Transform()->GetRelativeRot();

	Vec3 MissileRot = Transform()->GetRelativeRot();

	//ParentPos += OffsetX * 50.f;
	ParentPos += OffsetY * 100.f;
	ParentPos += ShootDir * 100.f;

	Transform()->SetRelativeScale(Vec3(50.0f, 50.0f, 50.0f));
	Transform()->SetRelativeRot(Vec3(ParentRot+MissileRot));
	Transform()->SetRelativePos(Vec3(ParentPos));

	//SpawnGameObject(GetOwner(), ParentPos , L"Player");
}

void CMissileScript::tick()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
	Vec3 vFront = CameraScript->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	Vec3 EmptyPos = MissileEmpty->Transform()->GetRelativePos();
	Vec3 vPos = Transform()->GetRelativePos();

	EmptyPos = vPos + vFront * 100;
	//EmptyPos.y -= vUp.y * 70;
	MissileEmpty->Transform()->SetRelativePos(EmptyPos);

	ShotTime += DT;
	//UpdateDirTime += DT;

		//if (m_TargetObject != nullptr)
		//{
		//	Vec3 TargetRot = m_TargetObject->Transform()->GetRelativeRot();
		//	Vec3 TargetPos = m_TargetObject->Transform()->GetRelativePos();
		//	Vec3 MissilePos = Transform()->GetRelativePos();
		//	Vec3 MissileDir = -Transform()->GetWorldDir(DIR_TYPE::RIGHT); // 미사일의 현재 전방 방향 벡터 구하기 

		//	Vec3 TargetDir = (TargetPos - MissilePos).Normalize(); // 목표물을 향하는 방향 벡터 


		//	// 목표 방향 벡터를 사용하여 미사일의 회전 계산
		//	float dot = MissileDir.Dot(TargetDir);
		//	float angle = acos(dot) * (180.0f / XM_PI); // 두 벡터 사이의 각도
		//	Vec3 axis = MissileDir.Cross(TargetDir).Normalize(); // 회전 축
		//	Quaternion newRotation = Quaternion::CreateFromAxisAngle(axis, angle); // 회전 쿼터니언
		//	
		//	Transform()->SetRelativeRot(TargetRot + QuaternionToEulerAngles(newRotation));

		//	// 목표물을 향해 회전된 방향으로 미사일을 이동합니다.
		//	Vec3 MoveDir = MissileDir + TargetDir; // 회전된 방향과 목표물을 향하는 방향을 결합합니다.
		//	MoveDir.Normalize(); // 정규화합니다.
		//	Vec3 NewPos = MissilePos + MoveDir * DT * 1000.f; // 새로운 위치를 계산합니다.
		//	Transform()->SetRelativePos(NewPos);

		//	

		//	if (ShotTime > 5.0f)
		//	{
		//		ShotTime = 0.f;
		//		DestroyObject(MissileEmpty);
		//		DestroyObject(GetOwner());
		//		PlayerScript->SetMissileCheck(true);
		//	}
		//}

		//if (m_TargetObject == nullptr)
		//{
			Vec3 BulletPos = Transform()->GetRelativePos();
			BulletPos += ShootDir * DT * 1000.f;
			Transform()->SetRelativePos(BulletPos);


			if (ShotTime > 5.0f)
			{
				ShotTime = 0.f;
				DestroyObject(MissileEmpty);
				DestroyObject(GetOwner());
				PlayerScript->SetMissileCheck(true);
			}
		//}

}

void CMissileScript::BeginOverlap(CCollider2D* _Other)
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
		DestroyObject(GetOwner());
		DestroyObject(MissileEmpty);
	}
}


