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

		//���� �ȿ� ������ ���� ����
		if (abs(MiniBossPos.z - CameraPos.z) <= abs(CameraFront.z * 5000) || TeleCheck)
		{
			PatternTime += DT;

			if (PatternTime >= 3.0f)
				Pattern();
		}
		else //���� �ȿ� ������ ����
		{
			mPattern = ePattern::Move;
		}

		if (ReloadingTime > 2.f) //�Ѿ� ������ Ÿ�̹�
		{
			CreateBullet();
			ReloadingTime = 0;
		}
	}
}

void MiniBossScript::BeginOverlap(CCollider2D* _Other)
{
	if (L"Bullet" == _Other->GetOwner()->GetName()) //5����
	{
		HP -= 5;
	}
}

void MiniBossScript::Pattern()
{
	std::random_device rd;;
	std::mt19937 gen(rd());

	// ������ ���� ����
	std::uniform_int_distribution<int> dis(1, 3);
	RandomPattern = dis(gen);

	//����
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

	if (TeleCount > 1) //�������� �Ȱ��� ������ �ɸ��� ��� ���� �����̵��� �ϱ� ������ ����ó��
	{
		DelayTime += DT;

		// ���� ����
		std::uniform_int_distribution<int> dis(MiniBossPos.x - 8000.f, MiniBossPos.x + 8000.f);

		if (DelayTime > 1.f) //�ٷ� ��Ÿ���� �ʰ� �������� 1���ִٰ� ���ġ
		{
			posX = dis(gen); // ���� �� ����
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

