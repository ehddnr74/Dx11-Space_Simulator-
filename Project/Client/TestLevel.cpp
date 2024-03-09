#include "pch.h"
#include "TestLevel.h"

#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\components.h>

#include <Engine\CResMgr.h>
#include <Engine\CCollisionMgr.h>

#include <Script\CPlayerScript.h>
#include <Script\CMissileScript.h>
#include <Script\CMonsterScript.h>
#include <Script\CCameraScript.h>
#include <Script\CPlanet_Lotating.h>
#include <Script\MeteoScript.h>
#include <Script\BlackholeScript.h>
#include <Script\BossScript.h>
#include <Script\HyperLoopScript.h>
#include <Script\DebugScript.h>
#include <Script\AsteroidbeltScript.h>
#include <Engine\CParticleSystem.h>
#include <Script\MiniBossScript.h>

#include <Script\HyperLoopScript.h>
#include <Script\HyperLoopScript_Mars.h>
#include <Script\HyperLoopScript_Jupiter.h>
#include <Script\HyperLoopScript_Saturn.h>
#include <Script\HyperLoopScript_Neptune.h>
#include <Script\HyperLoopScript_Uranus.h>

#include "CLevelSaveLoad.h"


#include <Engine/CSetColorShader.h>

//a

void CreateTestLevel()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	pCurLevel->ChangeState(LEVEL_STATE::STOP);

	// Layer 이름설정
	pCurLevel->GetLayer(0)->SetName(L"Default");
	pCurLevel->GetLayer(1)->SetName(L"MiniBoss");
	pCurLevel->GetLayer(2)->SetName(L"Player");
	pCurLevel->GetLayer(3)->SetName(L"Monster");
	pCurLevel->GetLayer(4)->SetName(L"sun");
	pCurLevel->GetLayer(5)->SetName(L"sun_postprocess");
	pCurLevel->GetLayer(6)->SetName(L"02_Mercury");
	pCurLevel->GetLayer(7)->SetName(L"03_Venus");
	pCurLevel->GetLayer(8)->SetName(L"04_Earth");
	pCurLevel->GetLayer(9)->SetName(L"Earth_Cloud");
	pCurLevel->GetLayer(10)->SetName(L"Moon");
	pCurLevel->GetLayer(11)->SetName(L"05_Mars");
	pCurLevel->GetLayer(12)->SetName(L"06_Jupiter");
	pCurLevel->GetLayer(13)->SetName(L"07_Saturn");
	pCurLevel->GetLayer(14)->SetName(L"07_SaturnRing");
	pCurLevel->GetLayer(15)->SetName(L"08_Uranus");
	pCurLevel->GetLayer(16)->SetName(L"08_UranusRing");
	pCurLevel->GetLayer(17)->SetName(L"09_Neptune");
	pCurLevel->GetLayer(18)->SetName(L"HyperLoop_Moon");
	pCurLevel->GetLayer(19)->SetName(L"HyperLoop_Mars");
	pCurLevel->GetLayer(20)->SetName(L"HyperLoop_Jupiter");
	pCurLevel->GetLayer(21)->SetName(L"HyperLoop_Saturn");
	pCurLevel->GetLayer(22)->SetName(L"HyperLoop_Uranus");
	pCurLevel->GetLayer(23)->SetName(L"HyperLoop_Neptune");
	pCurLevel->GetLayer(24)->SetName(L"blackhole");
	pCurLevel->GetLayer(25)->SetName(L"Sirius");
	pCurLevel->GetLayer(26)->SetName(L"Volcanic");
	pCurLevel->GetLayer(27)->SetName(L"Volcanic_Lava");
	pCurLevel->GetLayer(28)->SetName(L"Nar_Shaddaa");
	pCurLevel->GetLayer(29)->SetName(L"HL_Light");
	pCurLevel->GetLayer(30)->SetName(L"TargetAim");

	// Main Camera Object 생성
	CGameObject* pMainCam = new CGameObject;
	pMainCam->SetName(L"MainCamera");

	pMainCam->AddComponent(new CTransform);
	pMainCam->AddComponent(new CCamera);
	pMainCam->AddComponent(new CCameraScript);

	pMainCam->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
	pMainCam->Camera()->SetCameraIndex(0);		// MainCamera 로 설정
	pMainCam->Camera()->SetLayerMaskAll(true);	// 모든 레이어 체크
	pMainCam->Camera()->SetLayerMask(31, false);// UI Layer 는 렌더링하지 않는다.

	//pMainCam->Transform()->SetRelativeRot(-XM_PI * 1.6, XM_PI * 3, 0.f);

	SpawnGameObject(pMainCam, Vec3(248994.f, -1403.f, 1665336.f), 0);
	pMainCam->Transform()->SetMainCamera(pMainCam);

	// UI cameara
	CGameObject* pUICam = new CGameObject;
	pUICam->SetName(L"UICamera");

	pUICam->AddComponent(new CTransform);
	pUICam->AddComponent(new CCamera);

	pUICam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pUICam->Camera()->SetCameraIndex(1);		// Sub 카메라로 지정
	pUICam->Camera()->SetLayerMask(31, true);	// 31번 레이어만 체크

	SpawnGameObject(pUICam, Vec3(0.f, 0.f, 0.f), 0);


	// SkyBox 추가
	CGameObject* pSkyBox = new CGameObject;
	pSkyBox->SetName(L"SkyBox");

	pSkyBox->AddComponent(new CTransform);
	pSkyBox->AddComponent(new CSkyBox);

	CCameraScript* CameraScript = pMainCam->GetScript<CCameraScript>();
	CameraScript->SetSkyBox(pSkyBox);

	pSkyBox->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100.f));
	pSkyBox->SkyBox()->SetSkyBoxType(SKYBOX_TYPE::SPHERE);
	pSkyBox->SkyBox()->SetSkyBoxTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\skybox\\Sky02.jpg"));

	SpawnGameObject(pSkyBox, Vec3(0.f, 0.f, 0.f), L"Player");


	// 광원 추가
	CGameObject* pLightObj = new CGameObject;
	pLightObj->SetName(L"Point Light");

	pLightObj->AddComponent(new CTransform);
	pLightObj->AddComponent(new CLight3D);

	pLightObj->Transform()->SetRelativeRot(Vec3(XM_PI/* / 4.f*/, XM_PI /*/ 4.f*/, XM_PI));//0.f));
	//pLightObj->Light3D()->SetLightType(LIGHT_TYPE::POINT);
	pLightObj->Light3D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLightObj->Light3D()->SetRadius(100000000.f);
	pLightObj->Light3D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
	pLightObj->Light3D()->SetLightAmbient(Vec3(0.f, 0.f, 0.f));

	SpawnGameObject(pLightObj, Vec3(/*-10000.*/0.f, 0.f, 0.f), 0);

	// ============
	// 우주선 FBX
	// ============	
	Ptr<CMeshData> pMeshData = nullptr;
	CGameObject* Plane = nullptr;
	{
		pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Space Ship.fbx");
		//pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\untitled.mdat");
		Plane = pMeshData->Instantiate();
		Plane->Transform()->SetRelativeScale(Vec3(0.1f, 0.1f, 0.1f));
		Plane->Transform()->SetRelativeRot(Vec3(XM_PI / 2.05f, XM_PI * 1.022f, XM_PI / 180.f));
		Plane->AddComponent(new CPlayerScript);

		CCameraScript* CCS = pMainCam->GetScript<CCameraScript>();
		CCS->SetTarget(Plane);

		Plane->SetName(L"SpaceShip");
		SpawnGameObject(Plane, Vec3(11.f, -80.f, 180.f), L"Player");

		pMainCam->AddChild(Plane);
	}

	////// ============
	////// 몬스터 FBX
	////// ============	
	//{
	//	Ptr<CMeshData> MonsterMeshData = nullptr;
	//	CGameObject* Monster = nullptr;
	//
	//	MonsterMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\kkkkkkk.fbx");
	//	//HouseMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\test78678678.mdat");
	//	Monster = MonsterMeshData->Instantiate();
	//	Monster->AddComponent(new CMonsterScript);
	//	CMonsterScript* MS = Monster->GetScript<CMonsterScript>();
	//	CPlayerScript* CPS = Plane->GetScript<CPlayerScript>();
	//	MS->SetPlayerScript(CPS);
	//	Monster->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 50.f));
	//	//Monster->Transform()->SetRelativeRot(Vec3(0.f, XM_PI, 0.f));
	//	Monster->AddComponent(new CCollider2D);
	//	Monster->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	//	Monster->Collider2D()->SetOffsetScale(Vec3(8.f, 8.f, 8.f));
	//	Monster->SetName(L"Monster");
	//	SpawnGameObject(Monster, Vec3(0.f, 0.f, 3000.f), L"Monster");
	//	MS->begin();
	//}

	//// ============
	//// Test
	//// ============	
	//{
	//	CGameObject* test = new CGameObject;
	//	test->SetName(L"test2");
	//	test->AddComponent(new CTransform);
	//	test->AddComponent(new CMeshRender);
	//
	//	test->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100.f));
	//
	//	test->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	//	test->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"HyperLoopStateShaderMtrl"), 0);
	//	test->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\State\\off.png"));
	//
	//	SpawnGameObject(test, Vec3(0.f, 0.f, 500.f), L"Player");
	//}
		
	// ============
	// SolarSystem
	// ============	
	{
		// 인스턴싱 테스트
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;

		{	//태양
			CGameObject* Sun = new CGameObject;
			Sun->SetName(L"sun");
			Sun->AddComponent(new CTransform);
			Sun->AddComponent(new CMeshRender);
			Sun->AddComponent(new CPlanet_Lotating);


			Sun->Transform()->SetRelativeScale(Vec3(200000.f, 200000.f, 200000.f));
			Sun->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

			Sun->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

			Sun->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
			Sun->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"sunMtrl"), 0);
			Sun->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solarsystem\\sun.jpg"));

			SpawnGameObject(Sun, Vec3(0.f, 0.f, 0.f), L"sun");
		}

		//{	//태양 PostProcess
		//	CGameObject* sun_postprocess = new CGameObject;
		//	sun_postprocess->SetName(L"sun_postprocess");
		//	sun_postprocess->AddComponent(new CTransform);
		//	sun_postprocess->AddComponent(new CMeshRender);
		//
		//	sun_postprocess->Transform()->SetRelativeScale(Vec3(1000000.f, 1000000.f, 1000000.f));
		//
		//	sun_postprocess->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		//	sun_postprocess->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DistortionMtrl"), 0);
		//	sun_postprocess->MeshRender()->GetMaterial(0)->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\noise\\noise_01.png"));
		//
		//	SpawnGameObject(sun_postprocess, Vec3(0.f, 0.f, 0.f), L"sun_postprocess");
		//}

		{	//수성
			CGameObject* Mercury = new CGameObject;
			Mercury->SetName(L"02_Mercury");
			Mercury->AddComponent(new CTransform);

			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\02_Mercury.fbx");
			//pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\02_Mercury.mdat");
			Mercury = pMeshData->Instantiate();

			Mercury->AddComponent(new CPlanet_Lotating);
			Mercury->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 1.0f, 0.f));
			Mercury->Transform()->SetRelativeScale(Vec3(5000.f, 5000.f, 5000.f));
			SpawnGameObject(Mercury, Vec3(0.f, 0.f, 600000.f), L"02_Mercury");
		}

		{	//금성
			CGameObject* Venus = new CGameObject;
			Venus->SetName(L"03_Venus");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\03_Venus.fbx");
			//pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\03_Venus.mdat");
			Venus = pMeshData->Instantiate();
			Venus->Transform()->SetRelativeScale(Vec3(7000.f, 7000.f, 7000.f));

			Venus->AddComponent(new CPlanet_Lotating);
			Venus->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

			SpawnGameObject(Venus, Vec3(0.f, 0.f, 1000000.f), L"03_Venus");
		}

		{	//지구
			CGameObject* Earth = new CGameObject;
			Earth->SetName(L"04_Earth");

			Earth->AddComponent(new CTransform);
			Earth->AddComponent(new CMeshRender);
			Earth->AddComponent(new CPlanet_Lotating);

			Earth->Transform()->SetRelativeScale(Vec3(50000.f, 50000.f, 50000.f));
			Earth->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

			Earth->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
			Earth->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"EarthMtrl"), 0);
			Earth->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solarsystem\\Earth.png"));

			SpawnGameObject(Earth, Vec3(0.f, 0.f, 1700000.f), L"04_Earth");
		}

		{	//지구 구름
			CGameObject* Earth_Cloud = new CGameObject;
			Earth_Cloud->SetName(L"Earth_Cloud");

			Earth_Cloud->AddComponent(new CTransform);
			Earth_Cloud->AddComponent(new CMeshRender);
			Earth_Cloud->AddComponent(new CPlanet_Lotating);

			Earth_Cloud->Transform()->SetRelativeScale(Vec3(50500.f, 50500.f, 50500.f));
			Earth_Cloud->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

			Earth_Cloud->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
			Earth_Cloud->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Earth_CloudMtrl"), 0);
			Earth_Cloud->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solarsystem\\Earth_Cloud.png"));

			SpawnGameObject(Earth_Cloud, Vec3(0.f, 0.f, 1700000.f), L"Earth_Cloud");
		}

		{	//달
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Moon.fbx");
			//pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\04_Moon.mdat", L"meshdata\\04_Moon.mdat");
			pObj = pMeshData->Instantiate();
			pObj->SetName(L"Moon");
			pObj->Transform()->SetRelativeScale(Vec3(20000.f, 20000.f, 20000.f));
			SpawnGameObject(pObj, Vec3(300000.f, 0.f, 1700000.f), L"Moon");
		}

		{	//화성
			CGameObject* Mars = new CGameObject;
			Mars->SetName(L"05_Mars");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\05_Mars.fbx");
			//pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\05_Mars.mdat");
			Mars = pMeshData->Instantiate();

			Mars->AddComponent(new CPlanet_Lotating);
			Mars->Transform()->SetRelativeScale(Vec3(30000.f, 30000.f, 30000.f));
			Mars->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Mars, Vec3(0.f, 0.f, 2500000.f), L"05_Mars");
		}

		{	//목성
			CGameObject* Jupiter = new CGameObject;
			Jupiter->SetName(L"06_Jupiter");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\06_Jupiter.fbx");
			//pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\06_Jupiter.mdat");
			Jupiter = pMeshData->Instantiate();

			Jupiter->AddComponent(new CPlanet_Lotating);
			Jupiter->Transform()->SetRelativeScale(Vec3(500.f, 500.f, 500.f));
			Jupiter->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Jupiter, Vec3(0.f, 0.f, 5000000.f), L"06_Jupiter");
		}

		{	//토성
			CGameObject* Saturn = new CGameObject;
			Saturn->SetName(L"07_Saturn");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\07_Saturn.fbx");
			//pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\07_Saturn.mdat");
			Saturn = pMeshData->Instantiate();

			Saturn->AddComponent(new CPlanet_Lotating);
			Saturn->Transform()->SetRelativeScale(Vec3(.7f, .7f, .7f));
			Saturn->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Saturn, Vec3(0.f, 0.f, 6000000.f), L"07_Saturn");
		}

		{	//토성 고리
			CGameObject* SaturnRing = new CGameObject;
			SaturnRing->SetName(L"07_SaturnRing");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\07_SaturnRing.fbx");
			//pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\07_SaturnRing.mdat");
			SaturnRing = pMeshData->Instantiate();

			//SaturnRing->AddComponent(new CPlanet_Lotating);
			//SaturnRing->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SaturnRing->Transform()->SetRelativeScale(Vec3(.7f, .7f, .7f));
			SaturnRing->Transform()->SetRelativeRot(Vec3(-0.5f, 0.f, 0.f));
			SpawnGameObject(SaturnRing, Vec3(0.f, 0.f, 6000000.f), L"07_SaturnRing");
		}

		{	//천왕성
			CGameObject* Uranus = new CGameObject;
			Uranus->SetName(L"08_Uranus");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\08_Uranus.fbx");
			//pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\08_Uranus.mdat");
			//pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\08_Uranus.mdat", L"meshdata\\08_Uranus.mdat");
			Uranus = pMeshData->Instantiate();

			Uranus->AddComponent(new CPlanet_Lotating);
			Uranus->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100.f));
			Uranus->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Uranus, Vec3(0.f, 0.f, 8000000), L"08_Uranus");
		}

		{	//천왕성 고리
			CGameObject* UranusRing = new CGameObject;
			UranusRing->SetName(L"08_UranusRing");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\kkkk.fbx");
			//pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\08_UranusRing.mdat");
			UranusRing = pMeshData->Instantiate();

			//UranusRing->AddComponent(new CPlanet_Lotating);
			//UranusRing->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			UranusRing->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100.f));
			UranusRing->Transform()->SetRelativeRot(Vec3(-1.0f, 0.f, 0.f));
			SpawnGameObject(UranusRing, Vec3(0.f, 0.f, 8000000), L"08_UranusRing");
		}

		{	//해왕성
			CGameObject* Neptune = new CGameObject;
			Neptune->SetName(L"09_Neptune");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\09_Neptune.fbx");
			//pMeshData = CResMgr::GetInst()->Load<CMeshData>(L"meshdata\\09_Neptune.mdat", L"meshdata\\09_Neptune.mdat");
			Neptune = pMeshData->Instantiate();

			Neptune->AddComponent(new CPlanet_Lotating);
			Neptune->Transform()->SetRelativeScale(Vec3(5000.f, 5000.f, 5000.f));
			Neptune->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(Neptune, Vec3(0.f, 0.f, 9000000), L"09_Neptune");
		}
	}

	// ============
	// HyperLoop
	// ============	
	{
		Ptr<CMeshData> HyperLoopMeshData = nullptr;
		HyperLoopMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\HyperLoop.fbx");

		CGameObject* HyperLoop_Moon = new CGameObject;
		CGameObject* HyperLoop_Mars = new CGameObject;
		CGameObject* HyperLoop_Jupiter = new CGameObject;
		CGameObject* HyperLoop_Saturn = new CGameObject;
		CGameObject* HyperLoop_Uranus = new CGameObject;
		CGameObject* HyperLoop_Neptune = new CGameObject;

		{	//달 HyperLoop
			HyperLoop_Moon = HyperLoopMeshData->Instantiate();
			HyperLoop_Moon->AddComponent(new CPlanet_Lotating);
			HyperLoop_Moon->AddComponent(new CCollider2D);
			HyperLoop_Moon->AddComponent(new HyperLoopScript);

			HyperLoopScript* HL = HyperLoop_Moon->GetScript<HyperLoopScript>();
			CPlayerScript* CPS = Plane->GetScript<CPlayerScript>();
			HL->SetPlayerScript(CPS);

			HyperLoop_Moon->GetScript<HyperLoopScript>()->SetTime(15.5f);

			HyperLoop_Moon->Transform()->SetRelativeScale(Vec3(30.f, 30.f, 30.f));
			HyperLoop_Moon->Transform()->SetRelativeRot(Vec3(1.5f, 0.f, 0.f));

			HyperLoop_Moon->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
			HyperLoop_Moon->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));

			HyperLoop_Moon->SetName(L"HyperLoop_Moon");
			SpawnGameObject(HyperLoop_Moon, Vec3(250000.f, 0.f, 1700000.f), L"HyperLoop_Moon");
		}

		{	//화성 HyperLoop
			HyperLoop_Mars = HyperLoopMeshData->Instantiate();
			HyperLoop_Mars->AddComponent(new CPlanet_Lotating);
			HyperLoop_Mars->AddComponent(new CCollider2D);
			HyperLoop_Mars->AddComponent(new HyperLoopScript_Mars);

			HyperLoopScript_Mars* HL = HyperLoop_Mars->GetScript<HyperLoopScript_Mars>();
			HyperLoopScript* HLS = HyperLoop_Moon->GetScript<HyperLoopScript>();
			CPlayerScript* CPS = Plane->GetScript<CPlayerScript>();

			HL->SetPlayerScript(CPS);
			HL->SetHyperLoopConnet(HLS);

			HyperLoop_Mars->GetScript<HyperLoopScript_Mars>()->SetTime(24.5f);
			HyperLoop_Mars->GetScript<HyperLoopScript_Mars>()->SetSpeed(100000.f);

			HyperLoop_Mars->Transform()->SetRelativeScale(Vec3(30.f, 30.f, 30.f));
			HyperLoop_Mars->Transform()->SetRelativeRot(Vec3(1.5f, 0.f, 0.f));

			HyperLoop_Mars->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
			HyperLoop_Mars->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));

			HyperLoop_Mars->SetName(L"HyperLoop_Mars");
			SpawnGameObject(HyperLoop_Mars, Vec3(250000.f, 0.f, 2500000.f), L"HyperLoop_Mars");
		}

		{	//목성 HyperLoop
			HyperLoop_Jupiter = HyperLoopMeshData->Instantiate();
			HyperLoop_Jupiter->AddComponent(new CPlanet_Lotating);
			HyperLoop_Jupiter->AddComponent(new CCollider2D);
			HyperLoop_Jupiter->AddComponent(new HyperLoopScript_Jupiter);

			HyperLoopScript_Jupiter* HL = HyperLoop_Jupiter->GetScript<HyperLoopScript_Jupiter>();
			HyperLoopScript_Mars* HLSM = HyperLoop_Mars->GetScript<HyperLoopScript_Mars>();
			CPlayerScript* CPS = Plane->GetScript<CPlayerScript>();

			HL->SetPlayerScript(CPS);
			HL->SetHyperLoopConnet(HLSM);

			HyperLoop_Jupiter->GetScript<HyperLoopScript_Jupiter>()->SetTime(19.5f);

			HyperLoop_Jupiter->Transform()->SetRelativeScale(Vec3(30.f, 30.f, 30.f));
			HyperLoop_Jupiter->Transform()->SetRelativeRot(Vec3(1.5f, 0.f, 0.f));

			HyperLoop_Jupiter->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
			HyperLoop_Jupiter->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));

			HyperLoop_Jupiter->SetName(L"HyperLoop_Jupiter");
			SpawnGameObject(HyperLoop_Jupiter, Vec3(250000.f, 0.f, 5000000.f), L"HyperLoop_Jupiter");
		}

		{	//토성 HyperLoop		
			HyperLoop_Saturn = HyperLoopMeshData->Instantiate();
			HyperLoop_Saturn->AddComponent(new CPlanet_Lotating);
			HyperLoop_Saturn->AddComponent(new CCollider2D);
			HyperLoop_Saturn->AddComponent(new HyperLoopScript_Saturn);

			HyperLoopScript_Saturn* HL = HyperLoop_Saturn->GetScript<HyperLoopScript_Saturn>();
			HyperLoopScript_Jupiter* HLSJ = HyperLoop_Jupiter->GetScript<HyperLoopScript_Jupiter>();
			CPlayerScript* CPS = Plane->GetScript<CPlayerScript>();

			HL->SetPlayerScript(CPS);
			HL->SetHyperLoopConnet(HLSJ);

			HyperLoop_Saturn->GetScript<HyperLoopScript_Saturn>()->SetTime(19.7f);
			HyperLoop_Saturn->GetScript<HyperLoopScript_Saturn>()->SetSpeed(100000.f);

			HyperLoop_Saturn->Transform()->SetRelativeScale(Vec3(30.f, 30.f, 30.f));
			HyperLoop_Saturn->Transform()->SetRelativeRot(Vec3(1.5f, 0.f, 0.f));

			HyperLoop_Saturn->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
			HyperLoop_Saturn->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));

			HyperLoop_Saturn->SetName(L"HyperLoop_Saturn");
			SpawnGameObject(HyperLoop_Saturn, Vec3(250000.f, 0.f, 6000000.f), L"HyperLoop_Saturn");
		}

		{	//천왕성 HyperLoop
			HyperLoop_Uranus = HyperLoopMeshData->Instantiate();
			HyperLoop_Uranus->AddComponent(new CPlanet_Lotating);
			HyperLoop_Uranus->AddComponent(new CCollider2D);
			HyperLoop_Uranus->AddComponent(new HyperLoopScript_Uranus);

			HyperLoopScript_Uranus* HL = HyperLoop_Uranus->GetScript<HyperLoopScript_Uranus>();
			HyperLoopScript_Saturn* HLSS = HyperLoop_Saturn->GetScript<HyperLoopScript_Saturn>();
			CPlayerScript* CPS = Plane->GetScript<CPlayerScript>();

			HL->SetPlayerScript(CPS);
			HL->SetHyperLoopConnet(HLSS);

			HyperLoop_Uranus->GetScript<HyperLoopScript_Uranus>()->SetTime(19.5f);

			HyperLoop_Uranus->Transform()->SetRelativeScale(Vec3(30.f, 30.f, 30.f));
			HyperLoop_Uranus->Transform()->SetRelativeRot(Vec3(1.5f, 0.f, 0.f));

			HyperLoop_Uranus->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
			HyperLoop_Uranus->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));

			HyperLoop_Uranus->SetName(L"HyperLoop_Uranus");
			SpawnGameObject(HyperLoop_Uranus, Vec3(250000.f, 0.f, 8000000.f), L"HyperLoop_Uranus");
		}

		{	//해왕성 HyperLoop
			HyperLoop_Neptune = HyperLoopMeshData->Instantiate();
			HyperLoop_Neptune->AddComponent(new CPlanet_Lotating);
			HyperLoop_Neptune->AddComponent(new CCollider2D);
			HyperLoop_Neptune->AddComponent(new HyperLoopScript_Neptune);

			HyperLoopScript_Neptune* HL = HyperLoop_Neptune->GetScript<HyperLoopScript_Neptune>();
			HyperLoopScript_Uranus* HLSU = HyperLoop_Uranus->GetScript<HyperLoopScript_Uranus>();
			CPlayerScript* CPS = Plane->GetScript<CPlayerScript>();

			HL->SetPlayerScript(CPS);
			HL->SetHyperLoopConnet(HLSU);

			HyperLoop_Neptune->GetScript<HyperLoopScript_Neptune>()->SetTime(19.5f);
			HyperLoop_Neptune->GetScript<HyperLoopScript_Neptune>()->SetSpeed(100000.f);

			HyperLoop_Neptune->Transform()->SetRelativeScale(Vec3(30.f, 30.f, 30.f));
			HyperLoop_Neptune->Transform()->SetRelativeRot(Vec3(1.5f, 0.f, 0.f));

			HyperLoop_Neptune->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
			HyperLoop_Neptune->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));

			HyperLoop_Neptune->SetName(L"HyperLoop_Neptune");
			SpawnGameObject(HyperLoop_Neptune, Vec3(250000.f, 0.f, 9000000.f), L"HyperLoop_Neptune");
		}

		// ============
		// MiniBoss
		// ============	
		{
			Ptr<CMeshData> MinibossMeshData = nullptr;
			CGameObject* MiniBoss = new CGameObject;
			MiniBoss->SetName(L"MiniBoss");
			pMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\MiniBoss.fbx");
			MiniBoss = pMeshData->Instantiate();

			MiniBoss->AddComponent(new MiniBossScript);
			MiniBoss->AddComponent(new CCollider2D);

			MiniBossScript* MBS = MiniBoss->GetScript<MiniBossScript>();
			CPlayerScript* CPS = Plane->GetScript<CPlayerScript>();
			HyperLoopScript_Neptune* HL = HyperLoop_Neptune->GetScript<HyperLoopScript_Neptune>();
			MBS->SetPlayerScript(CPS);
			MBS->SetHyperLoopConnect(HL);

			MiniBoss->Collider2D()->SetOffsetPos(Vec3(-0.5f, 0.f, 3.f));
			MiniBoss->Collider2D()->SetOffsetScale(Vec3(6.f, 6.f, 6.f));

			MiniBoss->Transform()->SetRelativeScale(Vec3(350.f, 350.f, 350.f));
			SpawnGameObject(MiniBoss, Vec3(250000.f, 0.f, 10960000.f), L"MiniBoss");
		}
	}

	// ============
	// BlackHole
	// ============	
	{
		Ptr<CMeshData> BlackHoleMeshData = nullptr;

		{	//blackhole
			CGameObject* BlackHole = new CGameObject;
			BlackHole->SetName(L"blackhole");
			BlackHole->AddComponent(new CTransform);
			BlackHole->AddComponent(new CMeshRender);

			BlackHole->AddComponent(new CPlanet_Lotating);

			BlackHole->Transform()->SetRelativeScale(Vec3(10000.f, 10000.f, 10000.f));
			BlackHole->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

			BlackHole->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

			BlackHole->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
			BlackHole->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BlackholeMtrl"), 0);
			SpawnGameObject(BlackHole, Vec3(250000.f, 0.f, 11000000.f), L"blackhole");
		}

		{	//blackhole ring
			CGameObject* BlackHole_Ring = new CGameObject;
			BlackHole_Ring->SetName(L"BlackHole_Ring");

			BlackHole_Ring->AddComponent(new CTransform);
			BlackHole_Ring->AddComponent(new CMeshRender);
			BlackHole_Ring->AddComponent(new CPlanet_Lotating);
			BlackHole_Ring->AddComponent(new BlackholeScript);
			BlackHole_Ring->AddComponent(new CCollider2D);

			BlackholeScript* BS = BlackHole_Ring->GetScript<BlackholeScript>();
			CPlayerScript* CPS = Plane->GetScript<CPlayerScript>();
			BS->SetPlayerScript(CPS);

			BlackHole_Ring->Transform()->SetRelativeScale(Vec3(30000.f, 100.f, 30000.f));
			BlackHole_Ring->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 10.f, 0.f));

			BlackHole_Ring->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
			BlackHole_Ring->Collider2D()->SetOffsetScale(Vec3(1.f, 20.f, 1.f));

			BlackHole_Ring->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
			BlackHole_Ring->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BlackholeRingMtrl"), 0);
			BlackHole_Ring->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\skybox\\skybox_03.jpeg"));

			SpawnGameObject(BlackHole_Ring, Vec3(250000.f, 0.f, 11000000.f), L"blackhole");
		}
	}

	// 충돌 시킬 레이어 짝 지정
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"Monster");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"MiniBoss");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"blackhole");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"TargetAim");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"HyperLoop_Moon");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"HyperLoop_Mars");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"HyperLoop_Jupiter");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"HyperLoop_Saturn");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"HyperLoop_Uranus");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"HyperLoop_Neptune");
}
