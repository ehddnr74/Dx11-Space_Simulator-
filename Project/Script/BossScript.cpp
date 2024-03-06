#include "pch.h"
#include "BossScript.h"
#include "BossBulletScript.h"
#include "time.h"
#include "BossShiled.h"
#include "CPlanet_Lotating.h"
#include "CPlayerScript.h"
#include "BossPlanets.h"
#include "CCameraScript.h"
#include "BossEmptyScript.h"
#include "Fading.h"
#include "time.h"

BossScript::BossScript()
	: CScript((UINT)SCRIPT_TYPE::BOSSSCRIPT)
	, HP(300)
	, MoveTime(0.f)
	, Bulletbool(false)
	, ShotTime(3.0f)
	, RoomEffectCheck(false)
	, InitTime(0.f)

{
}

BossScript::~BossScript()
{
}

void BossScript::begin()
{
	PlayerScript->SetTarGetObject(GetOwner());
	BossEmpty = new CGameObject;
	BossEmpty->SetName(L"BossEmpty");
	BossEmpty->AddComponent(new CTransform);
	BossEmpty->AddComponent(new CMeshRender);
	BossEmpty->AddComponent(new BossEmptyScript);
	BossEmptyScript* BES = BossEmpty->GetScript<BossEmptyScript>();
	BES->SetBossScript(this);
	BossEmpty->Transform()->SetRelativeScale(Vec3(0.001f, 0.001f, 0.001f));
	//Empty->Transform()->SetRelativePos()
	BossEmpty->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	BossEmpty->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"), 0);

	BossEmpty->AddComponent(new CCollider2D);
	BossEmpty->Collider2D()->SetOffsetPos(Vec3(1200000.000f, -500000.000f, -7000000.000f));
	BossEmpty->Collider2D()->SetOffsetScale(Vec3(5000000.000f, 5000000.000f, 5000000.000f));

	SpawnGameObject(BossEmpty, Vec3(0.f, 0.f, 0.f), L"Monster");

	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	Vec3 BossPos = CameraPos;
	Vec3 CameraFront = CameraScript->GetvFront();
	BossPos += CameraFront * 10000.f;
	BossPos.x -= 600.f;
	//BossPos.y += 2000.f;
	CameraPos.y -= 4000.f;
	CameraScript->GetOwner()->Transform()->SetRelativePos(CameraPos);
	Transform()->SetRelativeScale(Vec3(250.f, 250.f, 250.f));
	Transform()->SetRelativeRot(Vec3(XM_PI / 3.7f, XM_PI / 1.33f, XM_PI / 36.f));
	Transform()->SetRelativePos(Vec3(BossPos));

	{	//Sirius
		CGameObject* Sirius = new CGameObject;
		Sirius->SetName(L"Sirius");
		Sirius->AddComponent(new CTransform);
		Sirius->AddComponent(new CMeshRender);
		Sirius->AddComponent(new CPlanet_Lotating);
		Sirius->AddComponent(new BossPlanets);

		BossPlanets* SBP = Sirius->GetScript<BossPlanets>();
		SBP->SetCameraScript(CameraScript);
		SBP->SetSirius(Sirius);
		SBP->SetBossScript(this);

		Sirius->Transform()->SetRelativeScale(Vec3(10000.f, 10000.f, 10000.f));
		Sirius->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

		Sirius->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, -0.1f, 0.f));

		Sirius->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		Sirius->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SiriusMtrl"), 0);
		Sirius->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Sirius.jpg"));
		SpawnGameObject(Sirius, Vec3(0.f, 0.f, 30000000.f), L"Sirius");
	}

	{	//Volcanic
		CGameObject* Volcanic = new CGameObject;
		Volcanic->SetName(L"Volcanic");
		Volcanic->AddComponent(new CTransform);
		Volcanic->AddComponent(new CMeshRender);
		Volcanic->AddComponent(new CPlanet_Lotating);
		Volcanic->AddComponent(new BossPlanets);

		BossPlanets* VBP = Volcanic->GetScript<BossPlanets>();
		VBP->SetCameraScript(CameraScript);
		VBP->SetVolcanic(Volcanic);
		VBP->SetBossScript(this);


		Volcanic->Transform()->SetRelativeScale(Vec3(10000.f, 10000.f, 10000.f));
		Volcanic->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

		Volcanic->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

		Volcanic->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		Volcanic->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"VolcanicMtrl"), 0);
		Volcanic->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Volcanic_01.png"));

		SpawnGameObject(Volcanic, Vec3(50000.f, 0.f, 30500000.f), L"Volcanic");
	}
}

void BossScript::tick()
{
	Vec3 vFront = CameraScript->Transform()->GetRelativeDir(DIR_TYPE::FRONT);
	Vec3 EmptyPos = BossEmpty->Transform()->GetRelativePos();
	Vec3 BossToEmptyPos = Transform()->GetRelativePos();

	EmptyPos = BossToEmptyPos - vFront * 2000;
	//EmptyPos.y -= vUp.y * 70;
	BossEmpty->Transform()->SetRelativePos(EmptyPos);

	InitTime += DT;

	// 보스의 프레임마다 위치 조정 
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	Vec3 CameraRot = CameraScript->GetOwner()->Transform()->GetRelativeRot();
	Vec3 BossPos = Transform()->GetRelativePos();
	Vec3 CameraFront = CameraScript->GetvFront();
	if (BossPos.z - CameraPos.z >= 14000.f)
	{
	  BossPos.z = BossPos.z;
	}
	else
	{
	  BossPos.z += CameraFront.z * DT * 2500.f;
	}
	Transform()->SetRelativePos(BossPos);

	if (InitTime >= 5.f)
	{
		if (Once == false)
		{
			Once = true;
			PlayerScript->GetOwner()->Transform()->SetRelativeScale(0.1f, 0.1f, 0.1f);
		}

		if (RoomEffectCheck == false)
		{
			RoomEffectCheck = true;
			CreateRoomEffect();
		}

		ShotTime += DT;

		if (ShotTime >= 5.0f && Bulletbool == false)
		{
			srand(time(NULL));
			for (int i = 0; i < 6; i++)
				Count.push_back(rand() & 6 + 1);

			// 벡터 정렬 후 연속된 중복 원소를 vector의 제일 뒷부분(쓰레기값)으로 보내버린다 : unique
			// 중복된 원소들이 모여있는 뒷부분을 erase로 삭제한다.

			sort(Count.begin(), Count.end());
			Count.erase(unique(Count.begin(), Count.end()), Count.end());

			// 중복된 원소가 제거되어 남은 숫자에 해당하는 레이저들만 발사한다.
			// 가로로 3개 세로로 3개에 각각 가로 상단부터 하단으로 1번 , 2번 , 3번 세로 좌부터 우로 4번 , 5번 , 6번 해당  

			ShotTime = 0.f;
			Bulletbool = true;
			if (Ending == false)
			{
				for (int i = 0; i < Count.size(); i++)
						CreateBossRazer(Count[i]);
			}
			Count.clear();
		}

		switch (eBossState)
		{
		case BossScript::BossState::Razer:
			razer();
			break;
		case BossScript::BossState::Missile:
			missile();
			break;
		case BossScript::BossState::MonsterSpawn:
			monsterspawn();
			break;
		case BossScript::BossState::TelePort:
			teleport();
			break;
		case BossScript::BossState::ForceShield:
			forceshield();
			break;
		case BossScript::BossState::Die:
			die();
			break;
		}
	}

	if (LerpShiled && ShiledCheck == false)
	{
		ShiledCheck = true;
		// 보스 실드 소환 
		BossLerpShiled = new CGameObject;
		BossLerpShiled->SetName(L"LerpShiled");

		BossLerpShiled->AddComponent(new CTransform);
		BossLerpShiled->AddComponent(new CMeshRender);
		BossLerpShiled->AddComponent(new BossShiled);
		BossShiled* BS = BossLerpShiled->GetScript<BossShiled>();

		BossLerpShiled->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		BossLerpShiled->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"LerpShiledMtrl"), 0);
		BossLerpShiled->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Nar_Shaddaa01.png"));
		BossLerpShiled->MeshRender()->GetMaterial(0)->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Volcanic_01.png"));

		BossLerpShiled->Transform()->SetRelativeScale(Vec3(13000.f, 13000.f, 13000.f));

		Vec3 BossPos = Transform()->GetRelativePos();
		BossPos.x += 600.f;
		BossPos.y += 2000.f;
		BossPos.z -= 1800.f;
		//Vec3 CameraPos = CameraScript->Transform()->GetRelativePos();
		//CameraPos.y += 3000.f;

		SpawnGameObject(BossLerpShiled, BossPos, 0);
	}

	if (BossLerpShiled != nullptr)
	{
		Ending = true;
		lerpshiledtime += DT;

		Vec3 BossPos = Transform()->GetRelativePos();
		Vec3 ShiledPos = BossLerpShiled->Transform()->GetRelativePos();

		ShiledPos = BossPos;
		ShiledPos.x = BossPos.x + 800.f;
		ShiledPos.y = BossPos.y + 2000.f;
		ShiledPos.z = BossPos.z - 1800.f;

		BossLerpShiled->Transform()->SetRelativePos(ShiledPos);

		if (lerpshiledtime >= 8.f && fading)
		{
			fading = false;
			CGameObject* Fadein = new CGameObject;
			Fadein->SetName(L"Fading");
			Fadein->AddComponent(new CTransform);
			Fadein->AddComponent(new CMeshRender);
			Fadein->AddComponent(new Fading);
			Fadein->GetScript<Fading>()->SetFadingState(Fading::FadingState::FadeOuting);
			Fadein->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
			Fadein->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"FadingMtrl"), 0);
			SpawnGameObject(Fadein, Vec3(0.f, 0.f, 0.f), 0);
		}

		if (lerpshiledtime >= 4.5f && DestroyParticle)
		{
			Transform()->SetRelativeScale(Vec3(0.f, 0.f, 0.f));
			DestroyParticle = false;

			pParticleObj = new CGameObject;
			pParticleObj->SetName(L"BulletParticle");
			pParticleObj->AddComponent(new CTransform);
			pParticleObj->AddComponent(new CParticleSystem);
			pParticleObj->ParticleSystem()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\particle\\Sparks.png"));
			pParticleObj->ParticleSystem()->SetSpawnRate(1000);
			pParticleObj->ParticleSystem()->SetSpawnColor(Vec3(1.f, 1.f, 1.f));
			pParticleObj->ParticleSystem()->SetSpawnScaleMin(Vec3(150.f, 150.f, 150.f));
			pParticleObj->ParticleSystem()->SetSpawnScaleMax(Vec3(150.f, 150.f, 150.f));
			pParticleObj->ParticleSystem()->SetBoxShapeScale(Vec3(50000.f, 50000.f, 50000.f));
			pParticleObj->ParticleSystem()->SetSpace(0);
			pParticleObj->ParticleSystem()->SetMinLifeTime(3.0f);
			pParticleObj->ParticleSystem()->SetMaxLifeTime(3.0f);

			pParticleObj->ParticleSystem()->SetScaleChangeMoudule(true);
			pParticleObj->ParticleSystem()->SetStartScale(1.f);
			pParticleObj->ParticleSystem()->SetEndScale(0.f);

			pParticleObj->ParticleSystem()->SetAddVelocityModule(true);
			pParticleObj->ParticleSystem()->SetAddVelocityType(1);
			pParticleObj->ParticleSystem()->SetSpeed(500.f);
			pParticleObj->ParticleSystem()->SetVelocityDir(Vec3(0.f, 1.f, 0.f));
			pParticleObj->ParticleSystem()->SetOffsetAngle(500.f);

			pParticleObj->ParticleSystem()->SetRenderModule(true);
			pParticleObj->ParticleSystem()->SetVelocityAlignment(true);
			pParticleObj->ParticleSystem()->SetVelocityScale(true);
			pParticleObj->ParticleSystem()->SetMaxVelocityScale(Vec3(15.f, 1.f, 1.f));
			pParticleObj->ParticleSystem()->SetMaxSpeed(500.f);

			SpawnGameObject(pParticleObj, BossLerpShiled->Transform()->GetRelativePos(), 0);

		}

		if (BossLerpShiled != nullptr && lerpshiledtime >= 5.f)
		{
			Vec3 BossLerpShiledScale = BossLerpShiled->Transform()->GetRelativeScale();

			if (BossLerpShiledScale.x >= 0.f || BossLerpShiledScale.y >= 0.f || BossLerpShiledScale.z >= 0.f)
			{
				BossLerpShiledScale.x -= DT * 3000.f;
				BossLerpShiledScale.y -= DT * 3000.f;
				BossLerpShiledScale.z -= DT * 3000.f;
				BossLerpShiled->Transform()->SetRelativeScale(BossLerpShiledScale);
			}
		}

		if (lerpshiledtime >= 6.f && pParticleObj != nullptr)
		{
				int SpawnRate = pParticleObj->ParticleSystem()->GetSpawnRate();
				if (SpawnRate >= 150)
				{
					SpawnRate -= 50;
					pParticleObj->ParticleSystem()->SetSpawnRate(SpawnRate);
				}
		}

		if (lerpshiledtime >= 10.f)
		{
			DestroyObject(pParticleObj);
			lerpshiledtime = 0.f;
			DestroyObject(BossLerpShiled);
			SetShiled(nullptr);
			DestroyObject(GetOwner());
			DestroyObject(BossEmpty);
		}
	}
}
void BossScript::BeginOverlap(CCollider2D* _Other)
{
	//if (L"Bullet" == _Other->GetOwner()->GetName())
	//{
	//	HP -= 10;
	//}
}

void BossScript::CreateBossBullet()
{
	Ptr<CMeshData> BulletMeshData = nullptr;
	Bullet = nullptr;

	BulletMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\08_Uranus.mdat");
	Bullet = BulletMeshData->Instantiate();

	Bullet->AddComponent(new CCollider2D);
	Bullet->AddComponent(new BossBulletScript);

	Bullet->Transform()->SetRelativeScale(Vec3(0.1f, 0.1f, 0.1f));

	BossBulletScript* BBS = Bullet->GetScript<BossBulletScript>();
	BBS->SetPlayerScript(PlayerScript);
	BBS->SetBossScript(this);

	Bullet->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	Bullet->Collider2D()->SetOffsetScale(Vec3(10.f, 10.f, 10.f));
	Bullet->SetName(L"BossBullet");

	Vec3 BossPos = Transform()->GetRelativePos();
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	SpawnGameObject(Bullet, BossPos, L"Monster");
}

void BossScript::CreateBossMissile()
{
	Ptr<CMeshData> pMeshData = nullptr;
	Missile = nullptr;

	pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\boss_missile.fbx");
	Missile = pMeshData->Instantiate();

	Missile->AddComponent(new CCollider2D);
	Missile->AddComponent(new BossBulletScript);

	Missile->Transform()->SetRelativeScale(Vec3(10.f, 10.f, 10.f));

	BossBulletScript* BBS = Missile->GetScript<BossBulletScript>();
	BBS->SetPlayerScript(PlayerScript);
	BBS->SetBossScript(this);

	Missile->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	Missile->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));

	Missile->SetName(L"Missile");
	Vec3 BossPos = Transform()->GetRelativePos();
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	SpawnGameObject(Missile, BossPos, L"Monster");
}

void BossScript::CreateBossRazer(int Count)
{
	if (Count == 1)
	{
		CGameObject* Razer = new CGameObject;
		Razer->SetName(L"Razer");

		Razer->AddComponent(new CTransform);
		Razer->AddComponent(new CMeshRender);
		Razer->AddComponent(new CCollider2D);
		Razer->AddComponent(new BossBulletScript);

		Razer->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		Razer->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"RazerMtrl"), 0);

		Razer->Transform()->SetRelativeScale(Vec3(15000.f, 150.f, 1.f));

		BossBulletScript* BBS = Razer->GetScript<BossBulletScript>();
		BBS->SetPlayerScript(PlayerScript);
		BBS->SetBossScript(this);

		Razer->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
		Razer->Collider2D()->SetOffsetScale(Vec3(0.2f, 1.f, 1.f));

		Vec3 BossPos = Transform()->GetRelativePos();
		BossPos.x = CameraScript->GetPlayerEmpty()->Transform()->GetRelativePos().x;
		BossPos.y = CameraScript->GetPlayerEmpty()->Transform()->GetRelativePos().y + 2000.f;
		//BossPos.z -= 18000.f;
		Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();

		SpawnGameObject(Razer, BossPos, L"Monster");
	}
	if (Count == 2)
	{
		CGameObject* Razer = new CGameObject;
		Razer->SetName(L"Razer");

		Razer->AddComponent(new CTransform);
		Razer->AddComponent(new CMeshRender);
		Razer->AddComponent(new CCollider2D);
		Razer->AddComponent(new BossBulletScript);

		Razer->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		Razer->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"RazerMtrl"), 0);

		Razer->Transform()->SetRelativeScale(Vec3(15000.f, 150.f, 1.f));

		BossBulletScript* BBS = Razer->GetScript<BossBulletScript>();
		BBS->SetPlayerScript(PlayerScript);
		BBS->SetBossScript(this);

		Razer->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
		Razer->Collider2D()->SetOffsetScale(Vec3(0.2f, 1.f, 1.f));

		Vec3 BossPos = Transform()->GetRelativePos();
		BossPos.x = CameraScript->GetPlayerEmpty()->Transform()->GetRelativePos().x;
		BossPos.y = CameraScript->GetPlayerEmpty()->Transform()->GetRelativePos().y;
		//BossPos.z -= 18000.f;
		Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();

		SpawnGameObject(Razer, BossPos, L"Monster");
	}
	if (Count == 3)
	{
		CGameObject* Razer = new CGameObject;
		Razer->SetName(L"Razer");

		Razer->AddComponent(new CTransform);
		Razer->AddComponent(new CMeshRender);
		Razer->AddComponent(new CCollider2D);
		Razer->AddComponent(new BossBulletScript);

		Razer->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		Razer->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"RazerMtrl"), 0);

		Razer->Transform()->SetRelativeScale(Vec3(15000.f, 150.f, 1.f));

		BossBulletScript* BBS = Razer->GetScript<BossBulletScript>();
		BBS->SetPlayerScript(PlayerScript);
		BBS->SetBossScript(this);

		Razer->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
		Razer->Collider2D()->SetOffsetScale(Vec3(0.2f, 1.f, 1.f));

		Vec3 BossPos = Transform()->GetRelativePos();
		BossPos.x = CameraScript->GetPlayerEmpty()->Transform()->GetRelativePos().x;
		BossPos.y = CameraScript->GetPlayerEmpty()->Transform()->GetRelativePos().y - 2000;
		//BossPos.z -= 18000.f;
		Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();

		SpawnGameObject(Razer, BossPos, L"Monster");
	}
	if (Count == 4)
	{
		CGameObject* Razer = new CGameObject;
		Razer->SetName(L"Razer");

		Razer->AddComponent(new CTransform);
		Razer->AddComponent(new CMeshRender);
		Razer->AddComponent(new CCollider2D);
		Razer->AddComponent(new BossBulletScript);

		Razer->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		Razer->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"RazerMtrl"), 0);

		Razer->Transform()->SetRelativeScale(Vec3(150.f, 15000.f, 1.f));

		BossBulletScript* BBS = Razer->GetScript<BossBulletScript>();
		BBS->SetPlayerScript(PlayerScript);
		BBS->SetBossScript(this);

		Razer->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
		Razer->Collider2D()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));

		Vec3 BossPos = Transform()->GetRelativePos();
		BossPos.x = CameraScript->GetPlayerEmpty()->Transform()->GetRelativePos().x - 3000;
		BossPos.y = CameraScript->GetPlayerEmpty()->Transform()->GetRelativePos().y;
		//BossPos.z -= 18000.f;
		Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();

		SpawnGameObject(Razer, BossPos, L"Monster");
	}
	if (Count == 5)
	{
		CGameObject* Razer = new CGameObject;
		Razer->SetName(L"Razer");

		Razer->AddComponent(new CTransform);
		Razer->AddComponent(new CMeshRender);
		Razer->AddComponent(new CCollider2D);
		Razer->AddComponent(new BossBulletScript);

		Razer->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		Razer->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"RazerMtrl"), 0);

		Razer->Transform()->SetRelativeScale(Vec3(150.f, 15000.f, 1.f));

		BossBulletScript* BBS = Razer->GetScript<BossBulletScript>();
		BBS->SetPlayerScript(PlayerScript);
		BBS->SetBossScript(this);

		Razer->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
		Razer->Collider2D()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));

		Vec3 BossPos = Transform()->GetRelativePos();
		BossPos.x = CameraScript->GetPlayerEmpty()->Transform()->GetRelativePos().x;
		BossPos.y = CameraScript->GetPlayerEmpty()->Transform()->GetRelativePos().y;
		//BossPos.z -= 18000.f;
		Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();

		SpawnGameObject(Razer, BossPos, L"Monster");
	}
	if (Count == 6)
	{
		CGameObject* Razer = new CGameObject;
		Razer->SetName(L"Razer");

		Razer->AddComponent(new CTransform);
		Razer->AddComponent(new CMeshRender);
		Razer->AddComponent(new CCollider2D);
		Razer->AddComponent(new BossBulletScript);

		Razer->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		Razer->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"RazerMtrl"), 0);

		Razer->Transform()->SetRelativeScale(Vec3(150.f, 15000.f, 1.f));

		BossBulletScript* BBS = Razer->GetScript<BossBulletScript>();
		BBS->SetPlayerScript(PlayerScript);
		BBS->SetBossScript(this);

		Razer->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
		Razer->Collider2D()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));

		Vec3 BossPos = Transform()->GetRelativePos();
		BossPos.x = CameraScript->GetPlayerEmpty()->Transform()->GetRelativePos().x + 3000;
		BossPos.y = CameraScript->GetPlayerEmpty()->Transform()->GetRelativePos().y;
		//BossPos.z -= 18000.f;
		Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();

		SpawnGameObject(Razer, BossPos, L"Monster");
	}
}

void BossScript::CreateRoomEffect()
{
	CGameObject* RoomEffect = new CGameObject;
	RoomEffect->SetName(L"RoomEffect");
	
	RoomEffect->AddComponent(new CTransform);
	RoomEffect->AddComponent(new CMeshRender);
	RoomEffect->AddComponent(new BossShiled);
	BossShiled* BS = RoomEffect->GetScript<BossShiled>();
	BS->SetCameraScript(CameraScript);


	RoomEffect->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	RoomEffect->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ShiledMtrl"), 0);
	RoomEffect->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Shield\\Shiled3.jpg"));

	RoomEffect->Transform()->SetRelativeScale(Vec3(10000.f, 10000.f, 10000.f));

	Vec3 BossPos = Transform()->GetRelativePos();
	//Vec3 CameraPos = CameraScript->Transform()->GetRelativePos();
	//CameraPos.y += 3000.f;

	SpawnGameObject(RoomEffect, BossPos, 0);
}



void BossScript::razer()
{
}

void BossScript::missile()
{
}

void BossScript::monsterspawn()
{
}

void BossScript::teleport()
{
}

void BossScript::forceshield()
{
}

void BossScript::die()
{
}