#include "pch.h"
#include "BlackholeScript.h"
#include "CPlayerScript.h"
#include "CCameraScript.h"
#include "BossScript.h"
#include "Fading.h"
#include "BossShiled.h"

BlackholeScript::BlackholeScript()
	: CScript((UINT)SCRIPT_TYPE::BLACKHOLESCRIPT)
{
}

BlackholeScript::~BlackholeScript()
{
}

void BlackholeScript::begin()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
}

void BlackholeScript::tick()
{
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	Vec3 CameraRot = CameraScript->GetOwner()->Transform()->GetRelativeRot();


	float Distance = Transform()->GetRelativePos().z - CameraPos.z;

	if (Dist == false && Distance <= 25000.f)
	{
		Dist = true;
		Distortion = new CGameObject;
		Distortion->SetName(L"Distortion");
		Distortion->AddComponent(new CTransform);
		Distortion->AddComponent(new CMeshRender);
		Distortion->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		Distortion->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DistortionMtrl"), 0);
		Distortion->Transform()->SetRelativeScale(200.f, 200.f, 200.f);
		SpawnGameObject(Distortion, Vec3(0.f, 0.f, 0.f), 0);
	}

	//if (Distortion != nullptr)
	//{
	//	if (Distance >= 26000.f)
	//	{
	//		//Dist = false;
	//		DestroyObject(Distortion);
	//	}
	//}

	//if (Tele_in)
	//{
	//	//CameraPos = Vec3(23797.109f, -2210.932f, 990286.562f);
	//	//PlayerScript->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
	//	//CameraRot = Vec3(1.47715068f, 3.29867244f, 0.0349065848f);
	//	CameraPos = Vec3(0.f, 0.f, 30500000.f);
	//	CameraScript->GetOwner()->Transform()->SetRelativePos(CameraPos);
	//	//CameraScript->GetOwner()->Transform()->SetRelativeRot(Vec3(XM_PI / 180.f, (XM_PI / 180.f), 0.f));
	//	//CameraScript->GetOwner()->Transform()->SetRelativeRot(CameraRot);

	//	if (Distortion != nullptr)
	//		DestroyObject(Distortion);

	//	Tele_in = false;
	//}
}

void BlackholeScript::BeginOverlap(CCollider2D* _Other)
{
	if (L"Empty" == _Other->GetOwner()->GetName())
	{
		PlayerScript->GetOwner()->Transform()->SetRelativeScale(0.f, 0.f, 0.f);
		CameraScript->GetSkyBox()->SkyBox()->SetSkyBoxTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\skybox\\skybox_05.jpg"));

		//CGameObject* Shield = new CGameObject;
		//Shield->SetName(L"Shield");

		//Shield->AddComponent(new CTransform);
		//Shield->AddComponent(new CMeshRender);
		//Shield->AddComponent(new BossShiled);
		//BossShiled* BS = Shield->GetScript<BossShiled>();
		//BS->SetCameraScript(CameraScript);


		//Shield->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		//Shield->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ShiledMtrl"), 0);
		//Shield->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Shield\\Shiled3.jpg"));

		//Shield->Transform()->SetRelativeScale(Vec3(10000.f, 10000.f, 10000.f));


		//SpawnGameObject(Shield, Vec3(0.f,0.f,0.f), 0);


		// FadeOut

		CGameObject* Fadein = new CGameObject;
		Fadein->SetName(L"Fading");
		Fadein->AddComponent(new CTransform);
		Fadein->AddComponent(new CMeshRender);
		Fadein->AddComponent(new Fading);
		Fadein->GetScript<Fading>()->SetFadingState(Fading::FadingState::FadeOutAndIn);
		Fadein->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		Fadein->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"FadingMtrl"), 0);
		SpawnGameObject(Fadein, Vec3(0.f, 0.f, 0.f), 0);


		//Boss
		Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
		Vec3 CameraRot = CameraScript->GetOwner()->Transform()->GetRelativeRot();
		CameraPos = Vec3(0.f, 0.f, 30498532.000f);
		CameraRot = Vec3(0.f, 0.f, 0.f);
		CameraScript->GetOwner()->Transform()->SetRelativePos(CameraPos);
		CameraScript->GetOwner()->Transform()->SetRelativeRot(CameraRot);

		if (Distortion != nullptr)
				DestroyObject(Distortion);

			Ptr<CMeshData> BossStageMeshData = nullptr;
			CGameObject* Boss = nullptr;
		
			BossStageMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\boss_Test.fbx"); 
			//BossStageMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\boss_Test.mdat");
			Boss = BossStageMeshData->Instantiate();
		
			//Boss->AddComponent(new CCollider2D);
			Boss->AddComponent(new BossScript);
		
			BossScript* BS = Boss->GetScript<BossScript>();
			BS->SetPlayerScript(PlayerScript);
			//PlayerScript->SetBossScript(BS);
		
			//Boss->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100.f));
		
			//Boss->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));
		
			//CameraScript->Transform()->SetRelativeRot(Vec3(0.f, -10.f, 0.f));
		
			//Boss->Collider2D()->SetOffsetPos(Vec3(10.f, 10.f, 10.f));
			//Boss->Collider2D()->SetOffsetScale(Vec3(50.f, 50.f, 50.f));
		
			Boss->SetName(L"Boss");
			SpawnGameObject(Boss, Vec3(0.f, 0.f, 0.f), L"Monster");
			//SpawnGameObject(Boss, Vec3(0.0f, 0.0f, 5000.f), L"Boss");

	}
}
