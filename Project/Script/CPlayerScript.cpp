#include "pch.h"
#include "CPlayerScript.h"

#include <Engine\CMeshRender.h>
#include <Engine\CMaterial.h>

#include "CMissileScript.h"
#include "CCameraScript.h"
#include "BulletScript.h"
#include "BossScript.h"


CPlayerScript::CPlayerScript()
	: CScript((UINT)SCRIPT_TYPE::PLAYERSCRIPT)
	, PrevMousePos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_Booster(false)
	, OffSet(Vec3(0.f, 0.f, 0.f))
	, ShootDir(Vec3(0.f,0.f,0.f))
	, vFront(Vec3(0.f, 0.f, 0.f))
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, &m_fSpeed, "Player Speed");
}

CPlayerScript::~CPlayerScript()
{

}

void CPlayerScript::begin()
{
	Camera = GetCameraScript()->GetOwner();
	//Vec3 CameraPos = Camera->Transform()->GetRelativePos();
	//Transform()->SetRelativePos(CameraPos.x + 53.f, CameraPos.y - 170.f, CameraPos.z + 500);
	//OffSet = Vec3(0.f, 0.f, -500.f);
	// 동적 재질 생성
	MeshRender()->GetDynamicMaterial(0);
}

void CPlayerScript::tick()
{
	//PrevMousePos = CKeyMgr::GetInst()->GetMousePos();

	Move();
}

void CPlayerScript::Shoot()
{
	//CreateBullet();
	// //미사일 프리팹 참조
	//Ptr<CPrefab> pMissilePrefab = CResMgr::GetInst()->FindRes<CPrefab>(L"MissilePrefab");
	//Vec3 vMissilePos = Transform()->GetRelativePos() + Vec3(0.f, 0.5f, 0.f) * Transform()->GetRelativeScale();
	//CGameObject* pCloneMissile = pMissilePrefab->Instantiate();

	//// 레벨에 추가
	//SpawnGameObject(pCloneMissile, vMissilePos, L"PlayerProjectile");
}

void CPlayerScript::Move()
{
	Vec3 vCurPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRot();
	Vec2 MousePos = CKeyMgr::GetInst()->GetMousePos(); //Y = 426

	Vec3 vFront = Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	Vec3 vUp = Transform()->GetRelativeDir(DIR_TYPE::UP);
	Vec3 vRight = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);



	if (KEY_PRESSED(KEY::Q))
		m_Booster = true;

	if (KEY_RELEASE(KEY::Q))
		m_Booster = false;

	if (KEY_TAP(KEY::T))
	{
		//MissileCheck = true;
		if(MissileCheck)
		CreateMissile();
	}

	if (KEY_TAP(KEY::F))
	{
		//BulletCheck = false;
		if (BulletCheck)
		CreateBullet();
	}
	if (BulletCheck == false)
	{
		BulletTime += DT;
		if (BulletTime >= 0.5f)
		{
			BulletCheck = true;
			BulletTime = 0.f;
		}
	}

	if (KEY_PRESSED(KEY::W))
	{
	}


	if (KEY_PRESSED(KEY::S))
	{

	}
	if (KEY_PRESSED(KEY::A))
	{
	}

	if (KEY_PRESSED(KEY::D))
	{
	}

	Transform()->SetRelativeRot(vRot);
	Transform()->SetRelativePos(vCurPos);
	PrevMousePos = CKeyMgr::GetInst()->GetMousePos();
}

void CPlayerScript::Booster()
{
}

void CPlayerScript::CreateBullet()
{
	BulletCheck = false;
	//Bullet = new CGameObject;
	//Bullet->SetName(L"Bullet");
	//Bullet->AddComponent(new CTransform);
	//Bullet->AddComponent(new CMeshRender);
	//Bullet->AddComponent(new BulletScript);
	//BulletScript* BS = Bullet->GetScript<BulletScript>();
	//BS->SetPlayerScript(this);

	////Bullet->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100.f));
	////Bullet->Transform()->SetRelativeRot(Vec3(ParentRot));
	//Bullet->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	//Bullet->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"), 0);


	//Bullet->AddComponent(new CCollider2D);
	//Bullet->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	//Bullet->Collider2D()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));

	//SpawnGameObject(Bullet, Vec3(0.f, 0.f, 0.f), L"Player");

	Ptr<CMeshData> BulletMeshData = nullptr;
	CGameObject* Bullet = nullptr;
	BulletMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\08_Uranus.mdat");
	Bullet = BulletMeshData->Instantiate();
	Bullet->AddComponent(new BulletScript);
	BulletScript* BS = Bullet->GetScript<BulletScript>();
	BS->SetPlayerScript(this);
	Bullet->AddComponent(new CCollider2D);
	Bullet->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	Bullet->Collider2D()->SetOffsetScale(Vec3(1000.f, 1000.f, 1000.f));
	Bullet->SetName(L"Bullet");
	SpawnGameObject(Bullet, Vec3(0.f, 0.f, 200.f), L"Player");
}


void CPlayerScript::CreateMissile()
{
	MissileCheck = false;
	Ptr<CMeshData> MissileMeshData = nullptr;
	CGameObject* Missile = nullptr;
	//BulletMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\boss_missile_02.fbx");
	MissileMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\boss_missile_02.mdat");
	Missile = MissileMeshData->Instantiate();
	Missile->AddComponent(new CMissileScript);
	CMissileScript* MS = Missile->GetScript<CMissileScript>();
	MS->SetPlayerScript(this);

	if (m_Target != nullptr)
	{
		MS->SetTargetObject(m_Target);
	}


	
	//Bullet->AddComponent(new CCollider2D);
	//Bullet->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	Missile->Transform()->SetRelativeScale(Vec3(0.f, 0.f, 0.f));
	Missile->Transform()->SetRelativeRot(Vec3(0.f, XM_PI / 2.f, 0.f));
	Missile->SetName(L"Missile");
	SpawnGameObject(Missile, Vec3(0.f, 0.f, 200.f), L"Player");
}

void CPlayerScript::BeginOverlap(CCollider2D* _Other)
{
	CGameObject* pOtherObject = _Other->GetOwner();

	if (pOtherObject->GetName() == L"Monster")
	{
		DestroyObject(pOtherObject);
	}

	//test
}







void CPlayerScript::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_fSpeed, sizeof(float), 1, _File);
}

void CPlayerScript::LoadFromLevelFile(FILE* _File)
{
	fread(&m_fSpeed, sizeof(float), 1, _File);
}