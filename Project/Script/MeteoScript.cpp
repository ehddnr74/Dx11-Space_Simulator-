#include "pch.h"
#include "MeteoScript.h"
#include "CPlayerScript.h"
#include <time.h>

MeteoScript::MeteoScript()
	: CScript((UINT)SCRIPT_TYPE::METEOSCRIPT)
	, SpawnPosition(Vec3(0.f, 0.f, 0.f))
{
}

MeteoScript::~MeteoScript()
{
}

void MeteoScript::begin()
{
	srand(time(NULL));
	double max = 32767;	
	double a = rand() / max;
	double b = rand() / max;
	double c = rand() / max;
	SpawnPosition = Vec3(a, b, c);
}

void MeteoScript::tick()
{



}

