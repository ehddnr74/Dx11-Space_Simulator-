#include "pch.h"
#include "BulletParticleScript.h"

BulletParticleScript::BulletParticleScript()
	: CScript((UINT)SCRIPT_TYPE::BULLETPARTICLESCRIPT)
{

}

BulletParticleScript::~BulletParticleScript()
{

}

void BulletParticleScript::begin()
{

}

void BulletParticleScript::tick()
{
	ParticleTime += DT;

	//if (ParticleTime >= 0.5f)
	//{
		//GetOwner()->ParticleSystem()->SetSpawnRate(0);
	//}
	if (ParticleTime >= 0.8f)
	{
		ParticleTime = 0.f;
		DestroyObject(GetOwner());
	}

}

void BulletParticleScript::BeginOverlap(CCollider2D* _Other)
{

}

