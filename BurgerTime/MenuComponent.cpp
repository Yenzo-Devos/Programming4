#include "MenuComponent.h"
#include "GameObject.h"

game::MenuComponent::MenuComponent(dae::GameObject* pOwner, bool areItemsHorizontal)
    : BaseComponent(pOwner)
    , m_isOrderedHorizontal{ areItemsHorizontal }
{
}

void game::MenuComponent::AddMenuItem(dae::GameObject* pMenuItem)
{
    m_pMenuItems.emplace_back(pMenuItem);
}

glm::vec2 game::MenuComponent::GetNextItemLocation(bool isNext)
{
    int size = static_cast<int>(m_pMenuItems.size());
    if (isNext)
        m_ItemSelected = (m_ItemSelected + 1) % size;
    else 
        m_ItemSelected = (m_ItemSelected - 1 + size) % size;

    return m_pMenuItems[m_ItemSelected]->GetWorldPosition();
}
