#include "pch.h"
#include "MiniBossScript.h"
#include "CCameraScript.h"
#include "MiniBossBulletScript.h"
#include "DebugScript.h"
#include "time.h"
#include <random>

MiniBossScript::MiniBossScript()
	: CScript((UINT)SCRIPT_TYPE::MINIBOSSSCRIPT)
	, HP(100)
	, RandomPattern(3)
	, PatternTime(0.f)
	, Bulletbool(false)
	, TelePos(Vec3(0.f, 0.f, 0.f))
	, posX(0.f)
	, TeleCount(0)
	, DelayTime(0.f)
	, ReloadingTime(0.f)
{
}

MiniBossScript::~MiniBossScript()
{
}

void MiniBossScript::begin()
{
	CameraScript = PlayerScript->GetOwner()->GetParent()->GetScript<CCameraScript>();
	Transform()->SetRelativePos(Vec3(250000.f, 0.f, 10960000.f));
}

void MiniBossScript::tick()
{
	MiniBoss_Start_Check = mHyperLoopNeptune->GetOwner()->GetScript<HyperLoopScript_Neptune>()->GetMiniBossState();

	ReloadingTime += DT;

	if (HP <= 0)
	{
		DestroyObject(GetOwner());
	}

	MiniBossPos = Transform()->GetRelativePos();
	CameraRight = CameraScript->GetvRight();
	CameraFront = CameraScript->GetvFront();

	CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	CameraRot = CameraScript->GetOwner()->Transform()->GetRelativeRot();

	Transform()->SetRelativeRot(Vec3(CameraRot.x, -CameraRot.y, -CameraRot.z));

	if (MiniBoss_Start_Check)
	{
		switch (mPattern)
		{
		case MiniBossScript::ePattern::Move:
			Move();
			break;
		case MiniBossScript::ePattern::RightMove:
			RightMove();
			break;
		case MiniBossScript::ePattern::LeftMove:
			LeftMove();
			break;
		case MiniBossScript::ePattern::TelePort:
			Teleportation();
			break;
		default:
			break;
		}

		//범위 안에 들어오면 패턴 시작
		if (abs(MiniBossPos.z - CameraPos.z) <= abs(CameraFront.z * 5000) || TeleCheck)
		{
			PatternTime += DT;

			if (PatternTime >= 3.0f)
				Pattern();
		}
		else //범위 안에 없을시 추적
		{
			mPattern = ePattern::Move;
		}

		if (ReloadingTime > 2.f) //총알 나가는 타이밍
		{
			CreateBullet();
			ReloadingTime = 0;
		}
	}
}

void MiniBossScript::BeginOverlap(CCollider2D* _Other)
{
	if (L"Bullet" == _Other->GetOwner()->GetName()) //5방컷
	{
		HP -= 5;
	}
}

void MiniBossScript::Pattern()
{
	std::random_device rd;;
	std::mt19937 gen(rd());

	// 랜덤값 범위 설정
	std::uniform_int_distribution<int> dis(1, 3);
	RandomPattern = dis(gen);

	//패턴
	switch (RandomPattern)
	{
	case 1: mPattern = ePattern::RightMove;
		break;
	case 2: mPattern = ePattern::LeftMove;
		break;
	case 3: mPattern = ePattern::TelePort;
		break;
	}

	TeleCount++;
	PatternTime = 0.f;
}

void MiniBossScript::Move()
{
	mPattern = ePattern::Move;

	Vec3 TarGetDir = (MiniBossPos - CameraPos).Normalize();
	MiniBossPos -= TarGetDir * DT * 500.f;
	Transform()->SetRelativePos(MiniBossPos);
}

void MiniBossScript::RightMove()
{
	mPattern = ePattern::RightMove;

	MiniBossPos += CameraRight * DT * 500.f;
	Transform()->SetRelativePos(MiniBossPos);
}

void MiniBossScript::LeftMove()
{
	mPattern = ePattern::LeftMove;

	MiniBossPos -= CameraRight * DT * 500.f;
	Transform()->SetRelativePos(MiniBossPos);
}

void MiniBossScript::Teleportation()
{
	mPattern = ePattern::TelePort;

	std::random_device rd;;
	std::mt19937 gen(rd());

	if (TeleCount > 1) //연속으로 똑같은 패턴이 걸리면 계속 더블 순간이동을 하기 때문에 예외처리
	{
		DelayTime += DT;

		// 범위 설정
		std::uniform_int_distribution<int> dis(MiniBossPos.x - 8000.f, MiniBossPos.x + 8000.f);

		if (DelayTime > 1.f) //바로 나타나지 않고 없어지고 1초있다가 재배치
		{
			posX = dis(gen); // 랜덤 값 생성
			TelePos.x = posX;
			TelePos.y = CameraPos.y;
			TelePos.z = MiniBossPos.z;
			Transform()->SetRelativePos(TelePos);
			TeleCount = 0.f;
			DelayTime = 0.f;
			TeleCheck = false;
		}
		else
		{
			TeleCheck = true;
			Transform()->SetRelativePos(Vec3(MiniBossPos.x, 9999999.f, MiniBossPos.z));
		}
	}
	else
	{
		PatternTime = 3.5f;
	}
}

void MiniBossScript::CreateBullet()
{
	Ptr<CMeshData> BulletMeshData = nullptr;
	Bullet = nullptr;

	BulletMeshData = CResMgr::GetInst()->FindRes<CMeshData>(L"meshdata\\08_Uranus.mdat");
	Bullet = BulletMeshData->Instantiate();
	Bullet->Transform()->SetRelativeScale(Vec3(0.1f, 0.1f, 0.1f));

	Bullet->AddComponent(new CCollider2D);
	Bullet->AddComponent(new MiniBossBulletScript);

	MiniBossBulletScript* MBBS = Bullet->GetScript<MiniBossBulletScript>();
	MBBS->SetPlayerScript(PlayerScript);
	MBBS->SetMiniBossScript(this);

	Bullet->Collider2D()->SetOffsetPos(Vec3(0.f, 0.f, 0.f));
	Bullet->Collider2D()->SetOffsetScale(Vec3(10.f, 10.f, 10.f));
	Bullet->SetName(L"MiniBossBullet");

	Vec3 MiniBossPos = Transform()->GetRelativePos();
	Vec3 CameraPos = CameraScript->GetOwner()->Transform()->GetRelativePos();
	SpawnGameObject(Bullet, MiniBossPos, L"MiniBoss");
}

