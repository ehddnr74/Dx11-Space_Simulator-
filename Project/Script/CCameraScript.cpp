#include "pch.h"
#include "CCameraScript.h"
#include <Engine\CTransform.h>
#include <Engine\CCamera.h>
#include "CPlayerScript.h"
#include "HitPostScript.h"
#include "Fading.h"
#include "BossEmptyScript.h"
#include<random>

std::mt19937_64 rng(0);
std::uniform_real_distribution<> dist(-10, 10);

CCameraScript::CCameraScript()
	: CScript((UINT)SCRIPT_TYPE::CAMERASCRIPT)
	, vFront(Vec3(0.f, 0.f, 0.f))
	, vUp(Vec3(0.f, 0.f, 0.f))
	, vRight(Vec3(0.f, 0.f, 0.f))
	, m_Target(nullptr)
	, m_fCamSpeed(1000.f)
	, CameraPos(Vec3(0.f, 0.f, 0.f))
	, PrevMousePos(Vec2(0.f, 0.f))
	, OffSet(Vec3(0.f, 0.f, 0.f))
	, HitPost(false)
	, _Fading(false)
{
}

CCameraScript::~CCameraScript()
{
}

void CCameraScript::begin()
{
	//Vec3 vPos = Transform()->GetRelativePos();

	//Transform()->SetMainCamera(this->GetOwner());
	Vec3 TarGetPos = m_Target->Transform()->GetRelativePos();
	OffSet = Vec3(0.f, 0.f, -500.f);
	//CameraPos = TarGetPos - CameraPos;
	//Transform()->SetRelativePos(CameraPos);

	CPlayerScript* PlayerScript = m_Target->GetScript<CPlayerScript>()->GetPlayerScript();
	PlayerScript->SetCameraScript(this);

	//Vec3 MuzzlePos = Muzzle->Transform()->GetRelativePos();
	//MuzzlePos = Transform()->GetRelativePos() + OffSet;

	//우주선 collider
	Empty = new CGameObject;
	Empty->SetName(L"Empty");
	Empty->AddComponent(new CTransform);
	Empty->AddComponent(new CMeshRender);
	//Empty->AddComponent(new BossEmptyScript);

	Empty->Transform()->SetRelativeScale(Vec3(0.001f, 0.001f, 0.001f));
	//Empty->Transform()->SetRelativePos()
	Empty->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	Empty->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"), 0);

	Empty->AddComponent(new CCollider2D);
	Empty->Collider2D()->SetOffsetPos(Vec3(0.0f, 0.0f, 0.0f));
	Empty->Collider2D()->SetOffsetScale(Vec3(200000.f, 200000.f, 200000.f));

	SpawnGameObject(Empty, Vec3(0.f, 0.f, 300.f), L"Player");
}


void CCameraScript::tick()
{
	vFront = Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	Vec3 EmptyPos = Empty->Transform()->GetRelativePos();
	Vec3 vPos = Transform()->GetRelativePos();

	//BossEmptyScript* BES = Empty->GetScript<BossEmptyScript>();
	//->SetPlayerEmpty(Empty);

	EmptyPos = vPos + vFront * 300;
	EmptyPos.y -= vUp.y * 70;
	Empty->Transform()->SetRelativePos(EmptyPos);
	Camera3DMove();
}

void CCameraScript::Camera3DMove()
{
	CPlayerScript* PlayerScript = m_Target->GetScript<CPlayerScript>()->GetPlayerScript();

	float fSpeed = m_fCamSpeed;
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRot();

	vFront = Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	vUp = Transform()->GetRelativeDir(DIR_TYPE::UP);
	vRight = Transform()->GetRelativeDir(DIR_TYPE::RIGHT);
	Vec2 MousePos = CKeyMgr::GetInst()->GetMousePos();
	Vec3 TarGetRot = m_Target->Transform()->GetRelativeRot();
	Vec3 TarGetPos = m_Target->Transform()->GetRelativePos();


	if (KEY_PRESSED(KEY::W))
	{
		vRot.x -= DT * 0.7f;
		//vPos += DT * vUp * fSpeed;
		if (TarGetRot.x <= XM_PI / 2.1f)
		{
			TarGetRot.x += DT * 0.2f;
			m_Target->Transform()->SetRelativeRot(TarGetRot);
		}
	}

	if (KEY_PRESSED(KEY::S))
	{
		vRot.x += DT * 0.7f;
		//vPos -= DT * vUp * fSpeed;
		if (TarGetRot.x >= XM_PI / 2.3f)
		{
			TarGetRot.x -= DT * 0.2f;
			m_Target->Transform()->SetRelativeRot(TarGetRot);
		}
	}

	if (KEY_PRESSED(KEY::A))
	{
		vRot.y -= DT * 1.0f;
		//vPos -= DT * vRight * fSpeed;
		if (TarGetRot.z <= XM_PI / 20.f)
		{
			TarGetRot.z += DT * 0.3f;
			m_Target->Transform()->SetRelativeRot(TarGetRot);
		}
	}

	if (KEY_PRESSED(KEY::D))
	{
		vRot.y += DT * 1.0f;
		//vPos += DT * vRight * fSpeed;

		if (TarGetRot.z >= -(XM_PI / 20.f))
		{
			TarGetRot.z -= DT * 0.3f;
			m_Target->Transform()->SetRelativeRot(TarGetRot);
		}
	}


	if (KEY_PRESSED(KEY::LSHIFT))
	{
		vPos += DT * vFront * fSpeed;
	}

	//if (KEY_PRESSED(KEY::RBTN))
	//{
	//	Vec2 vMouseDir = CKeyMgr::GetInst()->GetMouseDir();
	//	vRot.y += DT * vMouseDir.x * 5.f;
	//	vRot.x -= DT * vMouseDir.y * 5.f;
	//}

	if (m_Target != nullptr)
	{
		if (PlayerScript->GetBooster()) // 부스터가 켜져있는상태
		{
			vPos += DT * vFront * fSpeed * 2;

			if (TarGetPos.z <= 230.f)
			{

				TarGetPos.z += 80.f * DT;
				m_Target->Transform()->SetRelativePos(TarGetPos);
			}
		}

		if (PlayerScript->GetBooster() == false) // 부스터가 꺼져있는상태

			if (TarGetPos.z >= 180.f && TarGetPos.z <= 231.f)
			{
				TarGetPos.z -= DT * 80.f;
				m_Target->Transform()->SetRelativePos(TarGetPos);
			}
	}
	PrevMousePos = MousePos;
	Transform()->SetRelativePos(vPos);
	m_Target->Transform()->SetRelativePos(TarGetPos);
	Transform()->SetRelativeRot(vRot);

	if (HitPost)
	{
		Shaking = true;
		HitPost = false;
		HitPostProcess = new CGameObject;
		HitPostProcess->SetName(L"HitPost");
		HitPostProcess->AddComponent(new CTransform);
		HitPostProcess->AddComponent(new CMeshRender);
		HitPostProcess->AddComponent(new HitPostScript);
		HitPostScript* HPS = HitPostProcess->GetScript<HitPostScript>();
		HPS->SetCameraScript(this);
		HitPostProcess->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		HitPostProcess->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"GrayMtrl"), 0);
		SpawnGameObject(HitPostProcess, Vec3(0.f, 0.f, 0.f), 0);
	}

	if (Shaking)
		CameraShake(1.f);
}

void CCameraScript::CameraShake(double ShakeTime)
{
	if (OriginRotCheck == false) // 처음의 카메라 회전값 저장
	{
		OriginRotCheck = true;
		m_OriginRot = Transform()->GetRelativeRot();
	}

	//if (RandomRangeCheck == false) // 랜덤값 구하기 
	//{
		//RandomRangeCheck = true;
	RandomRange();
	//Vec3 TargetRot = m_OriginRot + Vec3(rangeX, rangeY, rangeZ); // 목표회전값
//}

	ShakingTime += DT;

	Vec3 CameraRot = Transform()->GetRelativeRot(); // 카메라 현재 회전상태
	CameraRot.x += rangeX * DT * m_force;
	CameraRot.y += rangeY * DT * m_force;
	CameraRot.z += rangeZ * DT * m_force;
	Transform()->SetRelativeRot(CameraRot);

	if (ShakingTime >= ShakeTime)
	{
		OriginRotCheck = false;
		ShakingTime = 0.f;
		Shaking = false;

		if (ToOriginRot)
			Transform()->SetRelativeRot(m_OriginRot); // 회전값을 기존으로 되돌림 True or Flase 선택 가능
	}
}


void CCameraScript::RandomRange()
{
	rangeX = dist(rng);
	rangeY = dist(rng);
	rangeZ = dist(rng);
}
