#include "pch.h"
#include "BossPlanets.h"
#include "CCameraScript.h"
#include "CPlanet_Lotating.h"
#include "BossShiled.h"

BossPlanets::BossPlanets()
	: CScript((UINT)SCRIPT_TYPE::BOSSPLANETS)
	, BossHP(0)
	, bossshiledtime(0.f)
{
}

BossPlanets::~BossPlanets()
{

}

void BossPlanets::begin()
{
	
}

void BossPlanets::tick()
{
	if (BossScript != nullptr)
	{
		BossHP = BossScript->GetHP();
	}
	if (CameraScript != nullptr)
	{
		Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
		Vec3 CameraFront = CameraScript->GetvFront();
		Vec3 CameraRight = CameraScript->GetvRight();
	}

	if (bossshiled != nullptr)
	{
		BossScript->SetColliderCheck(false);
		bossshiledtime += DT;

		Vec3 BossPos = BossScript->Transform()->GetRelativePos();
		Vec3 ShiledPos = bossshiled->Transform()->GetRelativePos();

		ShiledPos = BossPos;
		ShiledPos.x = BossPos.x + 800.f;
		ShiledPos.y = BossPos.y + 2000.f;
		ShiledPos.z = BossPos.z; //- 1800.f;

		bossshiled->Transform()->SetRelativePos(ShiledPos);

		if (bossshiledtime >= 10.f)
		{
			bossshiledtime = 0.f;
			DestroyObject(bossshiled);
			SetBossShiled(nullptr);
			BossScript->SetColliderCheck(true);
		}
	}

	if (BossHP <= 0)
	{
		FinalNarShaddaa = BossScript->GetNarShaddaa();
		FinalVolcanic = BossScript->GetVolcanic();
	}
	if(BossHP <= 0 && BossScript->GetNarShaddaa() != nullptr && BossScript->GetVolcanic() != nullptr)
	{
		FinalNarShaddaa = BossScript->GetNarShaddaa();
		FinalVolcanic = BossScript->GetVolcanic();

		Vec3 BossPos = BossScript->GetOwner()->Transform()->GetRelativePos();
		Vec3 NarShaddaaPos = FinalNarShaddaa->Transform()->GetRelativePos();
		Vec3 VolcanicPos = FinalVolcanic->Transform()->GetRelativePos();
		Vec3 NarhShaddaaDir = BossPos - NarShaddaaPos;
		Vec3 VolcanicDir = BossPos - VolcanicPos;

		if (abs(BossPos.x - NarShaddaaPos.x) <= 2000.f || abs(BossPos.x - VolcanicPos.x) <= 2000.f)
		{
			DestroyObject(FinalNarShaddaa);
			DestroyObject(FinalVolcanic);
			SetNarShaddaa(nullptr);
			SetVolcanic(nullptr);
			BossScript->SetLerp(true);
		}
		else
		{
			VolcanicPos += VolcanicDir * DT * 0.7f;
			FinalVolcanic->Transform()->SetRelativePos(VolcanicPos);
			NarShaddaaPos += NarhShaddaaDir * DT * 0.7f;
			FinalNarShaddaa->Transform()->SetRelativePos(NarShaddaaPos);
		}
	}

	if (Sirius != nullptr && BossScript != nullptr && BossHP >= 101)
	{
		Vec3 BossPos = BossScript->GetOwner()->Transform()->GetRelativePos();
		Vec3 SiriusPos = BossPos;
		SiriusPos.x = BossPos.x + 15000.f;
		Transform()->SetRelativePos(SiriusPos);
	}

	if (Sirius != nullptr && BossScript != nullptr && BossHP <= 100)
	{
		Vec3 BossPos = BossScript->GetOwner()->Transform()->GetRelativePos();
		Vec3 SiriusPos = Transform()->GetRelativePos();
		Vec3 SiriusScale = Transform()->GetRelativeScale();
		Vec3 AbsoluteDir = BossPos - SiriusPos;


		//if (SiriusScale.x >= 0.f || SiriusScale.y >= 0.f || SiriusScale.z >= 0.f)
		//{
		//	SiriusScale.x -= DT * 10000.f;
		//	SiriusScale.y -= DT * 10000.f;
		//	SiriusScale.z -= DT * 10000.f;
		//	Transform()->SetRelativeScale(SiriusScale);
		//}
		
		if (abs(BossPos.x - SiriusPos.x) <= 2000.f)
		{
			// 보스 실드 소환 
			CGameObject* bossshiled = new CGameObject;
			bossshiled->SetName(L"SiriusShiled");

			bossshiled->AddComponent(new CTransform);
			bossshiled->AddComponent(new CMeshRender);
			bossshiled->AddComponent(new BossShiled);
			BossShiled* BS = bossshiled->GetScript<BossShiled>();


			bossshiled->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
			bossshiled->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BossShiledMtrl"), 0);
			bossshiled->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Sirius.jpg"));

			bossshiled->Transform()->SetRelativeScale(Vec3(13000.f, 13000.f, 13000.f));

			Vec3 BossPos = Transform()->GetRelativePos();
			BossPos.x += 600.f;
			BossPos.y += 2000.f;
			BossPos.z -= 1800.f;
			//Vec3 CameraPos = CameraScript->Transform()->GetRelativePos();
			//CameraPos.y += 3000.f;

			SpawnGameObject(bossshiled, BossPos, 0);

			//DestroyObject(Volcanic);

			// Volcanic을 NarShaddaa로 변경
			//Transform()->SetRelativeScale(Vec3(0.f, 0.f, 0.f));
			DestroyObject(Sirius);
			SetSirius(nullptr);

			Volcanic = new CGameObject;
			Volcanic->SetName(L"Volcanic");
			Volcanic->AddComponent(new CTransform);
			Volcanic->AddComponent(new CMeshRender);
			Volcanic->AddComponent(new CPlanet_Lotating);
			Volcanic->AddComponent(new BossPlanets);
			BossPlanets* NBP = Volcanic->GetScript<BossPlanets>();
			NBP->SetVolcanic(Volcanic);
			NBP->SetCameraScript(CameraScript);
			NBP->SetBossScript(BossScript);
			NBP->SetBossShiled(bossshiled);
			BossScript->SetVolcanic(Volcanic);
			//SetNarShaddaa(NarShaddaa);
			Volcanic->Transform()->SetRelativeScale(Vec3(10000.f, 10000.f, 10000.f));
			Volcanic->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

			Volcanic->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, -0.1f, 0.f));

			Volcanic->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
			Volcanic->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"VolcanicMtrl"), 0);
			Volcanic->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Volcanic_01.png"));

			SpawnGameObject(Volcanic, Vec3(50000.f, 400.000f, 30450000.f), 0);

		}
		else
		{
			SiriusPos += AbsoluteDir * DT * 0.7f;
			Transform()->SetRelativePos(SiriusPos);
		}
	}

	if (NarShaddaa != nullptr && BossScript != nullptr && BossHP >= 1 && BossHP <= 200)
	{
		Vec3 BossPos = BossScript->GetOwner()->Transform()->GetRelativePos();
		Vec3 NarShaddaa = BossPos;
		NarShaddaa.x = BossPos.x - 14000.f;
		Transform()->SetRelativePos(NarShaddaa);
	}

	if (Volcanic != nullptr && BossScript != nullptr && BossHP >= 1 && BossHP <= 100)
	{
		Vec3 BossPos = BossScript->GetOwner()->Transform()->GetRelativePos();
		Vec3 VolcanicPos = BossPos;
		VolcanicPos.x = BossPos.x + 15000.f;
		Transform()->SetRelativePos(VolcanicPos);
	}

	if (Volcanic != nullptr && BossScript != nullptr && BossHP >= 201)
	{
		Vec3 BossPos = BossScript->GetOwner()->Transform()->GetRelativePos();
		Vec3 VolcanicPos = BossPos;
		VolcanicPos.x = BossPos.x - 14000.f;
		Transform()->SetRelativePos(VolcanicPos);
	}
	if (Volcanic != nullptr && BossScript != nullptr && BossHP >= 1 && BossHP <= 200)
	{
		Vec3 BossPos = BossScript->GetOwner()->Transform()->GetRelativePos();
		Vec3 VolcanicPos = Transform()->GetRelativePos();
		Vec3 VolcanicScale = Transform()->GetRelativeScale();

		Vec3 AbsoluteDir = BossPos - VolcanicPos;

		//if (VolcanicScale.x >= 0.f && VolcanicScale.y >=0.f && VolcanicScale.z >=0.f)
		//{
		//	VolcanicScale.x -= DT * 10000.f;
		//	VolcanicScale.y -= DT * 10000.f;
		//	VolcanicScale.z -= DT * 10000.f;
		//	Transform()->SetRelativeScale(VolcanicScale);
		//}


		if (abs(BossPos.x - VolcanicPos.x) <= 2000.f)
		{
			// 보스 실드 소환 
			CGameObject* bossshiled = new CGameObject;
			bossshiled->SetName(L"VolcanicShiled");

			bossshiled->AddComponent(new CTransform);
			bossshiled->AddComponent(new CMeshRender);
			bossshiled->AddComponent(new BossShiled);
			BossShiled* BS = bossshiled->GetScript<BossShiled>();


			bossshiled->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
			bossshiled->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BossShiledMtrl"), 0);
			bossshiled->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Volcanic_01.png"));

			bossshiled->Transform()->SetRelativeScale(Vec3(13000.f, 13000.f, 13000.f));

			Vec3 BossPos = Transform()->GetRelativePos();
			BossPos.x += 600.f;
			BossPos.y += 2000.f;
			BossPos.z -= 1800.f;
			//Vec3 CameraPos = CameraScript->Transform()->GetRelativePos();
			//CameraPos.y += 3000.f;

			SpawnGameObject(bossshiled, BossPos, 0);

			//DestroyObject(Volcanic);

			// Volcanic을 NarShaddaa로 변경
			//Transform()->SetRelativeScale(Vec3(0.f, 0.f, 0.f));
			DestroyObject(Volcanic);
			SetVolcanic(nullptr);

			NarShaddaa = new CGameObject;
			NarShaddaa->SetName(L"NarShaddaa");
			NarShaddaa->AddComponent(new CTransform);
			NarShaddaa->AddComponent(new CMeshRender);
			NarShaddaa->AddComponent(new CPlanet_Lotating);
			NarShaddaa->AddComponent(new BossPlanets);
			BossPlanets* NBP = NarShaddaa->GetScript<BossPlanets>();
			NBP->SetNarShaddaa(NarShaddaa);
			NBP->SetCameraScript(CameraScript);
			NBP->SetBossScript(BossScript);
			NBP->SetBossShiled(bossshiled);
			BossScript->SetNarShaddaa(NarShaddaa);
			//SetNarShaddaa(NarShaddaa);
			NarShaddaa->Transform()->SetRelativeScale(Vec3(10000.f, 10000.f, 10000.f));
			NarShaddaa->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

			NarShaddaa->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

			NarShaddaa->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
			NarShaddaa->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Nar_ShaddaaDMtrl"), 0);
			NarShaddaa->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Nar_Shaddaa01.png"));

			SpawnGameObject(NarShaddaa, Vec3(50000.f, 400.000f, 30450000.f), 0);
			//SetNarShaddaa(NarShaddaa);
		}
		else
		{
			VolcanicPos += AbsoluteDir * DT * 0.7f;
			Transform()->SetRelativePos(VolcanicPos);
		}
	}
}

