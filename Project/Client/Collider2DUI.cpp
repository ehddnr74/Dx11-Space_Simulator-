#include "pch.h"
#include "Collider2DUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CCollider2D.h>

Collider2DUI::Collider2DUI()
    : ComponentUI("##Coillider2D", COMPONENT_TYPE::COLLIDER2D)
{
    SetName("Coillider2D");
}

Collider2DUI::~Collider2DUI()
{
}

int Collider2DUI::render_update()
{
    if (FALSE == ComponentUI::render_update())
        return FALSE;

	Vec3 vOffset = GetTarget()->Collider2D()->GetOffsetPos();
	Vec3 vScale = GetTarget()->Collider2D()->GetOffsetScale();

	ImGui::Text("Offset");
	ImGui::SameLine();
	ImGui::DragFloat3("##OffSet", vOffset);

	ImGui::Text("Scale");
	ImGui::SameLine();
	ImGui::DragFloat3("##Scale", vScale);

	GetTarget()->Collider2D()->SetOffsetPos(vOffset);
	GetTarget()->Collider2D()->SetOffsetScale(vScale);

    return TRUE;
}