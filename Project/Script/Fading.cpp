#include "pch.h"
#include "Fading.h"
#include "CCameraScript.h"
#include <Engine\CMeshRender.h>

Fading::Fading()
	: CScript((UINT)SCRIPT_TYPE::FADING)
	, ratio(1.f)
	, init(false)
	, fadeout(false)
	, fadein(false)
{
}

Fading::~Fading()
{
}

void Fading::begin()
{
	//eFadingState = FadingState::FadeIn;
}

void Fading::tick()
{
	switch (eFadingState)
	{
	case Fading::FadingState::FadeIn:
		FadeIn();
		break;
	case Fading::FadingState::FadeOut:
		FadeOut();
		break;
	case Fading::FadingState::FadeOutAndIn:
		FadeOutAndIn();
		break;
	case Fading::FadingState::FadeOuting:
		fadeouting();
		break;
	}
}
void Fading::FadeIn()
{
	ratio -= DT * 0.15f;

	GetOwner()->MeshRender()->SetRatio(ratio);

	if (ratio <= 0.f)
	{
		DestroyObject(GetOwner());
		ratio = 0.f;
	}
}

void Fading::FadeOut()
{
	if (init == false)
	{
		ratio = 0.f;
		init = true;
	}

	ratio += DT * 0.15f;

	GetOwner()->MeshRender()->SetRatio(ratio);

	if (ratio >= 1.f)
	{
		DestroyObject(GetOwner());
		ratio = 0.f;
		init = true;
	}

}

void Fading::FadeOutAndIn()
{
	if (init == false)
	{
		fadeout = true;
		ratio = 0.f;
		init = true;
	}

	if (fadeout)
	{
		ratio += DT * 0.7f;
		if (ratio >= 1.f)
		{
			fadeout = false;
			fadein = true;
		}
	}
	
	if (fadein)
	{
		ratio -= DT * 0.15f;
		if (ratio <= 0.f)
		{
			DestroyObject(GetOwner());
			ratio = 0.f;
		}
	}

	GetOwner()->MeshRender()->SetRatio(ratio);
}

void Fading::fadeouting()
{
	if (init == false)
	{
		ratio = 0.f;
		init = true;
	}

	ratio += DT * 0.15f;

	GetOwner()->MeshRender()->SetRatio(ratio);
}






