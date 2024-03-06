#include "pch.h"
#include "AsteroidbeltScript.h"

AsteroidbeltScript::AsteroidbeltScript()
	: CScript((UINT)SCRIPT_TYPE::ASTEROIDBELTSCRIPT)
{
}

AsteroidbeltScript::~AsteroidbeltScript()
{
}

void AsteroidbeltScript::begin()
{
}

void AsteroidbeltScript::tick()
{
    if (Check)
    {
        PositionRandom();
        Transform()->SetRelativePos(Position);
        Check = false;
    }
}

void AsteroidbeltScript::PositionRandom()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    float x = std::rand() % maxX + 1;
    float y = std::rand() % maxY + 1;
    float z = std::rand() % (maxZ - minZ + 1) + minZ;

    Position = Vec3(x, y, z);
}


