#include "pch.h"
#include "ParticleSystemUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CParticleSystem.h>

ParticleSystemUI::ParticleSystemUI()
	: ComponentUI("##ParticleSystem", COMPONENT_TYPE::PARTICLESYSTEM)
{
	SetName("ParticleSystem");
}

ParticleSystemUI::~ParticleSystemUI()
{
}

int ParticleSystemUI::render_update()
{
	if (FALSE == ComponentUI::render_update())
		return FALSE;

	bool SpawnModule = GetTarget()->ParticleSystem()->GetSpawnMoudule();
	ImGui::Checkbox("SpawnModule", &SpawnModule);
	GetTarget()->ParticleSystem()->SetSpawnModule(SpawnModule);

	if (SpawnModule)
	{
		int SpawnRate = GetTarget()->ParticleSystem()->GetSpawnRate();
		ImGui::Text("Spawn Rate");
		ImGui::SameLine();
		ImGui::DragInt("##Rate", &SpawnRate);
		GetTarget()->ParticleSystem()->SetSpawnRate(SpawnRate);

		Vec3 SpawnColor = GetTarget()->ParticleSystem()->GetSpawnColor();
		ImGui::Text("Color");
		ImGui::SameLine();
		ImGui::DragFloat3("##Color", SpawnColor);
		GetTarget()->ParticleSystem()->SetSpawnColor(SpawnColor);

		Vec3 SpawnScaleMin = GetTarget()->ParticleSystem()->GetSpawnScaleMin();
		ImGui::Text("ScaleMin");
		ImGui::SameLine();
		ImGui::DragFloat3("##ScaleMin", SpawnScaleMin);

		GetTarget()->ParticleSystem()->SetSpawnScaleMin(SpawnScaleMin);

		Vec3 SpawnScaleMax = GetTarget()->ParticleSystem()->GetSpawnScaleMax();
		ImGui::Text("ScaleMax");
		ImGui::SameLine();
		ImGui::DragFloat3("##ScaleMax", SpawnScaleMax);

		GetTarget()->ParticleSystem()->SetSpawnScaleMax(SpawnScaleMax);

		int SpawnShapeType = GetTarget()->ParticleSystem()->GetSpawnShapeType();
		ImGui::Text("ShapeType");
		ImGui::SameLine();
		ImGui::DragInt("##ShapeType", &SpawnShapeType);

		GetTarget()->ParticleSystem()->SetSpawnShapeType(SpawnShapeType);

		Vec3 SpawnBoxScale = GetTarget()->ParticleSystem()->GetBoxShapeScale();
		ImGui::Text("BoxScale");
		ImGui::SameLine();
		ImGui::DragFloat3("##BoxScale", SpawnBoxScale);

		GetTarget()->ParticleSystem()->SetBoxShapeScale(SpawnBoxScale);

		int Space = GetTarget()->ParticleSystem()->GetSpace();
		ImGui::Text("Space");
		ImGui::SameLine();
		ImGui::DragInt("##Space", &Space);

		GetTarget()->ParticleSystem()->SetSpace(Space);

		float MinLifeTime = GetTarget()->ParticleSystem()->GetMinLifeTime();
		ImGui::Text("MinLifeTime");
		ImGui::SameLine();
		ImGui::DragFloat("##MinLifeTime", &MinLifeTime);

		GetTarget()->ParticleSystem()->SetMinLifeTime(MinLifeTime);

		float MaxLifeTime = GetTarget()->ParticleSystem()->GetMaxLifeTime();
		ImGui::Text("MaxLifeTime");
		ImGui::SameLine();
		ImGui::DragFloat("##MaxLifeTime", &MaxLifeTime);

		GetTarget()->ParticleSystem()->SetMaxLifeTime(MaxLifeTime);

	}

	bool ScaleChangeModule = GetTarget()->ParticleSystem()->GetScaleChangeMoudule();
	ImGui::Checkbox("ScaleChangeModule", &ScaleChangeModule);
	GetTarget()->ParticleSystem()->SetScaleChangeMoudule(ScaleChangeModule);

	if (ScaleChangeModule)
	{
		float StartScale = GetTarget()->ParticleSystem()->GetStartScale();
		ImGui::Text("StartScale");
		ImGui::SameLine();
		ImGui::DragFloat("##StartScale", &StartScale);
		GetTarget()->ParticleSystem()->SetStartScale(StartScale);

		float EndScale = GetTarget()->ParticleSystem()->GetEndScale();
		ImGui::Text("EndScale");
		ImGui::SameLine();
		ImGui::DragFloat("##EndScale", &EndScale);
		GetTarget()->ParticleSystem()->SetEndScale(EndScale);
	}

	bool ColorChangeModule = GetTarget()->ParticleSystem()->GetColorChangeMoudule();
	ImGui::Checkbox("ColorChangeModule", &ColorChangeModule);
	GetTarget()->ParticleSystem()->SetColorChangeMoudule(ColorChangeModule);

	if (ColorChangeModule)
	{
		Vec3 StartColor = GetTarget()->ParticleSystem()->GetStartColor();
		ImGui::Text("StartColor");
		ImGui::SameLine();
		ImGui::DragFloat3("##StartColor", StartColor);
		GetTarget()->ParticleSystem()->SetStartColor(StartColor);

		Vec3 EndColor = GetTarget()->ParticleSystem()->GetEndColor();
		ImGui::Text("EndColor");
		ImGui::SameLine();
		ImGui::DragFloat3("##EndColor", EndColor);
		GetTarget()->ParticleSystem()->SetEndColor(EndColor);
	}

	bool AddVelocityModule = GetTarget()->ParticleSystem()->GetAddVelocityModule();
	ImGui::Checkbox("AddVelocityModule", &AddVelocityModule);
	GetTarget()->ParticleSystem()->SetAddVelocityModule(AddVelocityModule);

	if (AddVelocityModule)
	{
		int AddVelocityType = GetTarget()->ParticleSystem()->GetAddVelocityType();
		ImGui::Text("AddVelocityType");
		ImGui::SameLine();
		ImGui::DragInt("##AddVelocityType", &AddVelocityType);
		GetTarget()->ParticleSystem()->SetAddVelocityType(AddVelocityType);

		float Speed = GetTarget()->ParticleSystem()->GetSpeed();
		ImGui::Text("Speed");
		ImGui::SameLine();
		ImGui::DragFloat("##Speed", &Speed);
		GetTarget()->ParticleSystem()->SetSpeed(Speed);

		Vec3 VelocityDir = GetTarget()->ParticleSystem()->GetVelocityDir();
		ImGui::Text("VelocityDir");
		ImGui::SameLine();
		ImGui::DragFloat3("##VelocityDir", VelocityDir);
		GetTarget()->ParticleSystem()->SetVelocityDir(VelocityDir);

		float OffsetAngle = GetTarget()->ParticleSystem()->GetOffsetAngle();
		ImGui::Text("OffsetAngle");
		ImGui::SameLine();
		ImGui::DragFloat("##Speed", &OffsetAngle);
		GetTarget()->ParticleSystem()->SetOffsetAngle(OffsetAngle);
	}
	bool DragModule = GetTarget()->ParticleSystem()->GetDragModule();
	ImGui::Checkbox("DragModule", &DragModule);
	GetTarget()->ParticleSystem()->SetDragModule(DragModule);

	if (DragModule)
	{
		float StartDrag = GetTarget()->ParticleSystem()->GetStartDrag();
		ImGui::Text("StartDrag");
		ImGui::SameLine();
		ImGui::DragFloat("##StartDrag", &StartDrag);
		GetTarget()->ParticleSystem()->SetStartDrag(StartDrag);

		float EndDrag = GetTarget()->ParticleSystem()->GetEndDrag();
		ImGui::Text("EndDrag");
		ImGui::SameLine();
		ImGui::DragFloat("##EndDrag", &EndDrag);
		GetTarget()->ParticleSystem()->SetEndDrag(EndDrag);
	}
	bool NoiseForceModule = GetTarget()->ParticleSystem()->GetNoiseForceModule();
	ImGui::Checkbox("NoiseForceModule", &NoiseForceModule);
	GetTarget()->ParticleSystem()->SetNoiseForceModule(NoiseForceModule);

	if (NoiseForceModule)
	{
		float fNoiseTerm = GetTarget()->ParticleSystem()->GetNoiseTerm();
		ImGui::Text("NoiseTerm");
		ImGui::SameLine();
		ImGui::DragFloat("##NoiseTerm", &fNoiseTerm);
		GetTarget()->ParticleSystem()->SetNoiseTerm(fNoiseTerm);

		float fNoiseForce = GetTarget()->ParticleSystem()->GetNoiseForce();
		ImGui::Text("NoiseForce");
		ImGui::SameLine();
		ImGui::DragFloat("##NoiseForce", &fNoiseForce);
		GetTarget()->ParticleSystem()->SetNoiseForce(fNoiseForce);
	}
	bool RenderModule = GetTarget()->ParticleSystem()->GetRenderModule();
	ImGui::Checkbox("RenderModule", &RenderModule);
	GetTarget()->ParticleSystem()->SetRenderModule(RenderModule);

	if (RenderModule)
	{
		bool VelocityAlignment = GetTarget()->ParticleSystem()->GetVelocityAlignment();
		ImGui::Text("VelocityAlignment");
		ImGui::SameLine();
		ImGui::Checkbox("##VelocityAlignment", &VelocityAlignment);
		GetTarget()->ParticleSystem()->SetVelocityAlignment(VelocityAlignment);

		bool VelocityScale = GetTarget()->ParticleSystem()->GetVelocityScale();
		ImGui::Text("VelocityScale");
		ImGui::SameLine();
		ImGui::Checkbox("##VelocityScale", &VelocityScale);
		GetTarget()->ParticleSystem()->SetVelocityScale(VelocityScale);

		Vec3 vMaxVelocityScale = GetTarget()->ParticleSystem()->GetMaxVelocityScale();
		ImGui::Text("MaxVelocityScale");
		ImGui::SameLine();
		ImGui::DragFloat3("##MaxVelocityScale", vMaxVelocityScale);
		GetTarget()->ParticleSystem()->SetMaxVelocityScale(vMaxVelocityScale);

		float vMaxSpeed = GetTarget()->ParticleSystem()->GetMaxSpeed();
		ImGui::Text("MaxSpeed");
		ImGui::SameLine();
		ImGui::DragFloat("##MaxSpeed", &vMaxSpeed);
		GetTarget()->ParticleSystem()->SetMaxSpeed(vMaxSpeed);
	}
	return TRUE;
}