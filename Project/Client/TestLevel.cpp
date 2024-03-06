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

#include "CLevelSaveLoad.h"


#include <Engine/CSetColorShader.h>

//a

void CreateTestLevel()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	pCurLevel->ChangeState(LEVEL_STATE::STOP);

	// Layer 이름설정
	pCurLevel->GetLayer(0)->SetName(L"Default");
	pCurLevel->GetLayer(1)->SetName(L"Tile");
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
	pCurLevel->GetLayer(18)->SetName(L"Hyperloop");
	pCurLevel->GetLayer(19)->SetName(L"blackhole");
	pCurLevel->GetLayer(21)->SetName(L"Sirius");
	pCurLevel->GetLayer(22)->SetName(L"Volcanic");
	pCurLevel->GetLayer(23)->SetName(L"Volcanic_Lava");
	pCurLevel->GetLayer(24)->SetName(L"Nar_Shaddaa");
	pCurLevel->GetLayer(25)->SetName(L"Meteo");
	pCurLevel->GetLayer(26)->SetName(L"TargetAim");

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

	SpawnGameObject(pMainCam, Vec3(0.f, 0.f, 0.f), 0);
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

	//CGameObject* pObj = new CGameObject;
	//pObj->SetName(L"Directional Light");
	//
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//
	//pObj->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"), 0);


	//SpawnGameObject(pObj, Vec3(0.f, 0.f, 0.f), 0);

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

		//Plane->AddComponent(new CCollider2D);
		//Plane->Collider2D()->SetOffsetPos(Vec3(0.f, -300.f, 0.f));
		//Plane->Collider2D()->SetOffsetScale(Vec3(1000.f,1000.f, 1000.f));
		Plane->SetName(L"SpaceShip");
		SpawnGameObject(Plane, Vec3(11.f, -80.f, 180.f), L"Player");

		pMainCam->AddChild(Plane);
	}

	// ============
	// 몬스터 FBX
	// ============	
	{
		Ptr<CMeshData> MonsterMeshData = nullptr;
		CGameObject* Monster = nullptr;
	
		MonsterMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\Enemy.fbx");
		//HouseMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\test78678678.mdat");
		Monster = MonsterMeshData->Instantiate();
		Monster->AddComponent(new CMonsterScript);
		CMonsterScript* MS = Monster->GetScript<CMonsterScript>();
		CPlayerScript* CPS = Plane->GetScript<CPlayerScript>();
		MS->SetPlayerScript(CPS);
		//CPlayerScript* PS = Plane->GetScript<CPlayerScript>();
		//PS->SetEnemy(pHouse);
		Monster->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 50.f));
		Monster->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));
		Monster->AddComponent(new CCollider2D);
		Monster->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
		Monster->Collider2D()->SetOffsetScale(Vec3(8.f, 8.f, 8.f));
		Monster->SetName(L"Monster");
		SpawnGameObject(Monster, Vec3(0.f, 0.f, 3000.f), L"Monster");
		MS->begin();
	}

		//Ptr<CMeshData> Meteo1MeshData = nullptr;
		//CGameObject* pMeteo1 = nullptr;
		//Meteo1MeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\04_meteo.fbx");

		////for (int i = 0; i < 10; ++i)
		////{
		////MeteoMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\01_meteo.mdat");
		//	pMeteo1 = Meteo1MeshData->Instantiate();
		//	pMeteo1->AddComponent(new MeteoScript);
		////MeteoScript * MS = pMeteo->GetScript<MeteoScript>();
		////MS->begin();
		////Vec3 MeteoPosition = MS->GetSpawnPosition();
		//	pMeteo1->Transform()->SetRelativeScale(Vec3(100.0f, 100.0f, 100.0f));
		////pMeteo->AddComponent(new CCollider2D);
		////pMeteo->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
		////pMeteo->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));
		//	pMeteo1->SetName(L"Meteo");
		////SpawnGameObject(pMeteo, Vec3(MeteoPosition), L"Monster");
		//SpawnGameObject(pMeteo1, Vec3(400, 600, 1200), L"Monster");
		////}


		//Ptr<CMeshData> Meteo2MeshData = nullptr;
		//CGameObject* pMeteo2 = nullptr;
		//Meteo2MeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\04_meteo.fbx");
		////for (int i = 0; i < 10; ++i)
		////{
		//	//MeteoMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\01_meteo.mdat");
		//	pMeteo2 = Meteo2MeshData->Instantiate();
		//	pMeteo2->AddComponent(new MeteoScript);
		//	//MeteoScript * MS = pMeteo->GetScript<MeteoScript>();
		//	//MS->begin();
		//	//Vec3 MeteoPosition = MS->GetSpawnPosition();
		//	pMeteo2->Transform()->SetRelativeScale(Vec3(100.0f, 100.0f, 100.0f));
		//	//pMeteo->AddComponent(new CCollider2D);
		//	//pMeteo->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
		//	//pMeteo->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));
		//	pMeteo2->SetName(L"Meteo");
		//	//SpawnGameObject(pMeteo, Vec3(MeteoPosition), L"Monster");
		//	SpawnGameObject(pMeteo2, Vec3(-400, 600, 1200), L"Monster");
		////}
		// 
	// ============
	// SolarSystem
	// ============	
	{
		// 인스턴싱 테스트
		Ptr<CMeshData> pMeshData = nullptr;
		CGameObject* pObj = nullptr;

		{	//태양
			int i = 1;
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

			SaturnRing->AddComponent(new CPlanet_Lotating);
			SaturnRing->Transform()->SetRelativeScale(Vec3(.7f, .7f, .7f));
			SaturnRing->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));
			SpawnGameObject(SaturnRing, Vec3(0.f, 0.f, 7000000.f), L"07_SaturnRing");
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

		CGameObject* HyperLoop = new CGameObject;
		HyperLoopMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\HyperLoop.fbx");
		//pMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\05_Mars.mdat");
		HyperLoop = HyperLoopMeshData->Instantiate();

		HyperLoop->AddComponent(new CPlanet_Lotating);
		HyperLoop->AddComponent(new CCollider2D);
		HyperLoop->AddComponent(new HyperLoopScript);

		HyperLoopScript* HL = HyperLoop->GetScript<HyperLoopScript>();
		CPlayerScript* CPS = Plane->GetScript<CPlayerScript>();
		HL->SetPlayerScript(CPS);

		//HyperLoop->GetScript<CPlanet_Lotating>()->SetRot(Vec3(100.f, 0.f, 0.f));

		HyperLoop->Transform()->SetRelativeScale(Vec3(10.f, 10.f, 10.f));
		HyperLoop->Transform()->SetRelativeRot(Vec3(1.5f, 0.f, 0.f));

		HyperLoop->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
		HyperLoop->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));

		HyperLoop->SetName(L"Hyperloop");
		SpawnGameObject(HyperLoop, Vec3(70000.f, 0.f, 2500000.f), L"Hyperloop");
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
			//BlackHole->AddComponent(new CCollider2D);

			BlackHole->AddComponent(new CPlanet_Lotating);
			//BlackHole->AddComponent(new BlackholeScript);

			//블랙홀 스크립트 안에 플레이어 스크립트 정보를 넣어준다.
			//BlackholeScript* BS = BlackHole->GetScript<BlackholeScript>();
			//CPlayerScript* CPS = Plane->GetScript<CPlayerScript>();
			//BS->SetPlayerScript(CPS);

			BlackHole->Transform()->SetRelativeScale(Vec3(10000.f, 10000.f, 10000.f));
			BlackHole->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

			//BlackHole->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
			//BlackHole->Collider2D()->SetOffsetScale(Vec3(1.f, 1.f, 1.f));

			BlackHole->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

			BlackHole->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
			BlackHole->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BlackholeMtrl"), 0);
			SpawnGameObject(BlackHole, Vec3(0.f, 0.f, 11000000.f), L"blackhole");
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

			SpawnGameObject(BlackHole_Ring, Vec3(0.f, 0.f, 11000000.f), L"blackhole");
		}
	}

	// ============
	// BossStage
	// ============	
	{
		//{	//Sirius
		//	CGameObject* Sirius = new CGameObject;
		//	Sirius->SetName(L"Sirius");
		//	Sirius->AddComponent(new CTransform);
		//	Sirius->AddComponent(new CMeshRender);
		//	Sirius->AddComponent(new CPlanet_Lotating);

		//	Sirius->Transform()->SetRelativeScale(Vec3(200000.f, 200000.f, 200000.f));
		//	Sirius->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

		//	Sirius->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

		//	Sirius->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		//	Sirius->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SiriusMtrl"), 0);
		//	Sirius->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Sirius.jpg"));
		//	SpawnGameObject(Sirius, Vec3(0.f, 0.f, 30000000.f), L"Sirius");
		//}

		//{	//Volcanic
		//	CGameObject* Volcanic = new CGameObject;
		//	Volcanic->SetName(L"Volcanic");
		//	Volcanic->AddComponent(new CTransform);
		//	Volcanic->AddComponent(new CMeshRender);
		//	Volcanic->AddComponent(new CPlanet_Lotating);

		//	Volcanic->Transform()->SetRelativeScale(Vec3(20000.f, 20000.f, 20000.f));
		//	Volcanic->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

		//	Volcanic->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

		//	Volcanic->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		//	Volcanic->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"VolcanicMtrl"), 0);
		//	Volcanic->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Volcanic_01.png"));

		//	SpawnGameObject(Volcanic, Vec3(50000.f, 0.f, 30500000.f), L"Volcanic");
		//}

		//{	//Volcanic_Lava
		//	CGameObject* Volcanic_Lava = new CGameObject;
		//	Volcanic_Lava->SetName(L"Volcanic_Lava");
		//	Volcanic_Lava->AddComponent(new CTransform);
		//	Volcanic_Lava->AddComponent(new CMeshRender);
		//	Volcanic_Lava->AddComponent(new CPlanet_Lotating);

		//	Volcanic_Lava->Transform()->SetRelativeScale(Vec3(20050.f, 20050.f, 20050.f));
		//	Volcanic_Lava->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

		//	Volcanic_Lava->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

		//	Volcanic_Lava->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		//	Volcanic_Lava->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Volcanic_LavaMtrl"), 0);
		//	Volcanic_Lava->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Volcanic\\Volcanic_Lava.png"));

		//	SpawnGameObject(Volcanic_Lava, Vec3(50000.f, 0.f, 30500000.f), L"Volcanic_Lava");
		//}

		//{	//Nar_Shaddaa
		//	CGameObject* Nar_Shaddaa = new CGameObject;
		//	Nar_Shaddaa->SetName(L"Nar_Shaddaa");
		//	Nar_Shaddaa->AddComponent(new CTransform);
		//	Nar_Shaddaa->AddComponent(new CMeshRender);
		//	Nar_Shaddaa->AddComponent(new CPlanet_Lotating);

		//	Nar_Shaddaa->Transform()->SetRelativeScale(Vec3(20000.f, 20000.f, 20000.f));
		//	Nar_Shaddaa->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

		//	Nar_Shaddaa->GetScript<CPlanet_Lotating>()->SetRot(Vec3(0.f, 0.1f, 0.f));

		//	Nar_Shaddaa->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		//	Nar_Shaddaa->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Nar_ShaddaaDMtrl"), 0);
		//	Nar_Shaddaa->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Planet\\Nar_Shaddaa01.png"));

		//	SpawnGameObject(Nar_Shaddaa, Vec3(50000.f, 400.000f, 30450000.f), L"Nar_Shaddaa");
		//}

			//{	// PostProcess Test 
			//	CGameObject* pPostProcess = new CGameObject;
			//	pPostProcess->SetName(L"PostProcess");
			//	pPostProcess->AddComponent(new CTransform);
			//	pPostProcess->AddComponent(new CMeshRender);
			//	pPostProcess->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
			//	pPostProcess->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"FlashMtrl"), 0);
			//	pPostProcess->MeshRender()->GetMaterial(0)->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\Flash\\Flash.png"));
			//	SpawnGameObject(pPostProcess, Vec3(0.f, 0.f, 0.f), 0);
			//}
	}

	// ============
	// Meteo
	// ============	
	//{
	//	Ptr<CMeshData> MeteoMeshData = nullptr;
	//	CGameObject* pMeteo = nullptr;
	//	MeteoMeshData = CResMgr::GetInst()->LoadFBX(L"fbx\\04_meteo.fbx");
	//
	//	for (int i = 0; i < 100; ++i)
	//	{
	//		MeteoMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\04_meteo.mdat");
	//		pMeteo = MeteoMeshData->Instantiate();
	//		pMeteo->Transform()->SetRelativeScale(Vec3(100.0f, 100.0f, 100.0f));
	//		//pMeteo->AddComponent(new AsteroidbeltScript);
	//		//pMeteo->GetScript<AsteroidbeltScript>()->tick();
	//		//Vec3 pos = pMeteo->GetScript<AsteroidbeltScript>()->GetPosition();
	//		//pMeteo->AddComponent(new CCollider2D);
	//		//pMeteo->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	//		//pMeteo->Collider2D()->SetOffsetScale(Vec3(100.f, 100.f, 100.f));
	//		pMeteo->SetName(L"Meteo");
	//		std::srand(static_cast<unsigned int>(std::time(nullptr)));
	//
	//		float x = std::rand() % 1000000 + 1;
	//		float y = std::rand() % 10000 + 1;
	//		float z = std::rand() % (3500000 - 3000000 + 1) + 3000000;
	//		SpawnGameObject(pMeteo, Vec3(x, y, z), L"Meteo");
	//	}
	//}

	// 충돌 시킬 레이어 짝 지정
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"Monster");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"blackhole");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"Hyperloop");
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"TargetAim");
}
