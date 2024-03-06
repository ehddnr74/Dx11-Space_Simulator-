#include "pch.h"
#include "CScriptMgr.h"

#include "AsteroidbeltScript.h"
#include "BlackholeScript.h"
#include "BossBulletScript.h"
#include "BossEmptyScript.h"
#include "BossPlanets.h"
#include "BossScript.h"
#include "BossShiled.h"
#include "BulletParticleScript.h"
#include "BulletScript.h"
#include "CCameraMoveScript.h"
#include "CCameraScript.h"
#include "CGravityScript.h"
#include "CMissileScript.h"
#include "CMonsterScript.h"
#include "CPlanet_Lotating.h"
#include "CPlayerScript.h"
#include "CTestScript.h"
#include "DebugScript.h"
#include "Fading.h"
#include "HitPostScript.h"
#include "HyperLoopScript.h"
#include "MeteoScript.h"
#include "MonsterBulletScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"AsteroidbeltScript");
	_vec.push_back(L"BlackholeScript");
	_vec.push_back(L"BossBulletScript");
	_vec.push_back(L"BossEmptyScript");
	_vec.push_back(L"BossPlanets");
	_vec.push_back(L"BossScript");
	_vec.push_back(L"BossShiled");
	_vec.push_back(L"BulletParticleScript");
	_vec.push_back(L"BulletScript");
	_vec.push_back(L"CCameraMoveScript");
	_vec.push_back(L"CCameraScript");
	_vec.push_back(L"CGravityScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CPlanet_Lotating");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CTestScript");
	_vec.push_back(L"DebugScript");
	_vec.push_back(L"Fading");
	_vec.push_back(L"HitPostScript");
	_vec.push_back(L"HyperLoopScript");
	_vec.push_back(L"MeteoScript");
	_vec.push_back(L"MonsterBulletScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"AsteroidbeltScript" == _strScriptName)
		return new AsteroidbeltScript;
	if (L"BlackholeScript" == _strScriptName)
		return new BlackholeScript;
	if (L"BossBulletScript" == _strScriptName)
		return new BossBulletScript;
	if (L"BossEmptyScript" == _strScriptName)
		return new BossEmptyScript;
	if (L"BossPlanets" == _strScriptName)
		return new BossPlanets;
	if (L"BossScript" == _strScriptName)
		return new BossScript;
	if (L"BossShiled" == _strScriptName)
		return new BossShiled;
	if (L"BulletParticleScript" == _strScriptName)
		return new BulletParticleScript;
	if (L"BulletScript" == _strScriptName)
		return new BulletScript;
	if (L"CCameraMoveScript" == _strScriptName)
		return new CCameraMoveScript;
	if (L"CCameraScript" == _strScriptName)
		return new CCameraScript;
	if (L"CGravityScript" == _strScriptName)
		return new CGravityScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CPlanet_Lotating" == _strScriptName)
		return new CPlanet_Lotating;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CTestScript" == _strScriptName)
		return new CTestScript;
	if (L"DebugScript" == _strScriptName)
		return new DebugScript;
	if (L"Fading" == _strScriptName)
		return new Fading;
	if (L"HitPostScript" == _strScriptName)
		return new HitPostScript;
	if (L"HyperLoopScript" == _strScriptName)
		return new HyperLoopScript;
	if (L"MeteoScript" == _strScriptName)
		return new MeteoScript;
	if (L"MonsterBulletScript" == _strScriptName)
		return new MonsterBulletScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::ASTEROIDBELTSCRIPT:
		return new AsteroidbeltScript;
		break;
	case (UINT)SCRIPT_TYPE::BLACKHOLESCRIPT:
		return new BlackholeScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSBULLETSCRIPT:
		return new BossBulletScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSEMPTYSCRIPT:
		return new BossEmptyScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSPLANETS:
		return new BossPlanets;
		break;
	case (UINT)SCRIPT_TYPE::BOSSSCRIPT:
		return new BossScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSSHILED:
		return new BossShiled;
		break;
	case (UINT)SCRIPT_TYPE::BULLETPARTICLESCRIPT:
		return new BulletParticleScript;
		break;
	case (UINT)SCRIPT_TYPE::BULLETSCRIPT:
		return new BulletScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return new CCameraMoveScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERASCRIPT:
		return new CCameraScript;
		break;
	case (UINT)SCRIPT_TYPE::GRAVITYSCRIPT:
		return new CGravityScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::PLANET_LOTATING:
		return new CPlanet_Lotating;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::TESTSCRIPT:
		return new CTestScript;
		break;
	case (UINT)SCRIPT_TYPE::DEBUGSCRIPT:
		return new DebugScript;
		break;
	case (UINT)SCRIPT_TYPE::FADING:
		return new Fading;
		break;
	case (UINT)SCRIPT_TYPE::HITPOSTSCRIPT:
		return new HitPostScript;
		break;
	case (UINT)SCRIPT_TYPE::HYPERLOOPSCRIPT:
		return new HyperLoopScript;
		break;
	case (UINT)SCRIPT_TYPE::METEOSCRIPT:
		return new MeteoScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERBULLETSCRIPT:
		return new MonsterBulletScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::ASTEROIDBELTSCRIPT:
		return L"AsteroidbeltScript";
		break;

	case SCRIPT_TYPE::BLACKHOLESCRIPT:
		return L"BlackholeScript";
		break;

	case SCRIPT_TYPE::BOSSBULLETSCRIPT:
		return L"BossBulletScript";
		break;

	case SCRIPT_TYPE::BOSSEMPTYSCRIPT:
		return L"BossEmptyScript";
		break;

	case SCRIPT_TYPE::BOSSPLANETS:
		return L"BossPlanets";
		break;

	case SCRIPT_TYPE::BOSSSCRIPT:
		return L"BossScript";
		break;

	case SCRIPT_TYPE::BOSSSHILED:
		return L"BossShiled";
		break;

	case SCRIPT_TYPE::BULLETPARTICLESCRIPT:
		return L"BulletParticleScript";
		break;

	case SCRIPT_TYPE::BULLETSCRIPT:
		return L"BulletScript";
		break;

	case SCRIPT_TYPE::CAMERAMOVESCRIPT:
		return L"CCameraMoveScript";
		break;

	case SCRIPT_TYPE::CAMERASCRIPT:
		return L"CCameraScript";
		break;

	case SCRIPT_TYPE::GRAVITYSCRIPT:
		return L"CGravityScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::PLANET_LOTATING:
		return L"CPlanet_Lotating";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::TESTSCRIPT:
		return L"CTestScript";
		break;

	case SCRIPT_TYPE::DEBUGSCRIPT:
		return L"DebugScript";
		break;

	case SCRIPT_TYPE::FADING:
		return L"Fading";
		break;

	case SCRIPT_TYPE::HITPOSTSCRIPT:
		return L"HitPostScript";
		break;

	case SCRIPT_TYPE::HYPERLOOPSCRIPT:
		return L"HyperLoopScript";
		break;

	case SCRIPT_TYPE::METEOSCRIPT:
		return L"MeteoScript";
		break;

	case SCRIPT_TYPE::MONSTERBULLETSCRIPT:
		return L"MonsterBulletScript";
		break;

	}
	return nullptr;
}