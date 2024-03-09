#include "pch.h"
#include "CameraUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CCamera.h>
#include <Script\CCameraScript.h>


CameraUI::CameraUI()
    : ComponentUI("##Camera", COMPONENT_TYPE::CAMERA)
{
    SetName("Camera");
}

CameraUI::~CameraUI()
{
}

int CameraUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

    CCameraScript* CS = GetTarget()->Camera()->GetOwner()->GetScript<CCameraScript>();
    float force = CS->GetForce();

    ImGui::Text("ShakingForce");
    ImGui::SameLine();
    ImGui::DragFloat("##ShakingForce", &force);
    CS->SetForce(force);

    bool ToOriginRot = CS->GetToOriginRot();
    ImGui::Checkbox("ToOriginRot", &ToOriginRot);
    CS->SetToOriginRot(ToOriginRot);


    return TRUE;
}
