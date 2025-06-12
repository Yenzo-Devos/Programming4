#include "MenuCommands.h"
#include "GameObject.h"
#include "CursorComponent.h"
#include "LeaderboardHandler.h"

game::MenuMoveCommand::MenuMoveCommand(dae::GameObject* pGameObject, MenuComponent* pMenu, glm::vec2 direction)
    : GameObjectCommand(pGameObject)
    , m_pMenu{pMenu}
    , m_Direction{ direction }
{
}

bool game::MenuMoveCommand::Execute(float)
{
    auto pos = GetGameObject()->GetWorldPosition();
    if (m_pMenu->IsOrderHorizontal())
    {
        if (m_Direction.x == 1.f)
        {
            auto nextPos = m_pMenu->GetNextItemLocation(true);
            GetGameObject()->SetLocalPosition(glm::vec3{ nextPos.x, pos.y, 0.f });
            return true;
        }
        else if (m_Direction.x == -1.f)
        {
            auto nextPos = m_pMenu->GetNextItemLocation(false);
            GetGameObject()->SetLocalPosition(glm::vec3{ nextPos.x, pos.y, 0.f });
            return true;
        }
    }
    else
    {
        if (m_Direction.y == -1.f)
        {
            auto nextPos = m_pMenu->GetNextItemLocation(false);
            GetGameObject()->SetLocalPosition(glm::vec3{ pos.x, nextPos.y, 0.f });
            return true;
        }
        else if (m_Direction.y == 1.f)
        {
            auto nextPos = m_pMenu->GetNextItemLocation(true);
            GetGameObject()->SetLocalPosition(glm::vec3{ pos.x, nextPos.y, 0.f });
            return true;
        }
    }
    return false;
}

game::MenuConfirmCommand::MenuConfirmCommand(dae::GameObject* pGameObject, dae::GameObject* pMenu)
    : GameObjectCommand(pGameObject)
    , m_pMenu{ pMenu }
{
}

bool game::MenuConfirmCommand::Execute(float)
{
    GetGameObject()->GetComponent<CursorComponent>()->Click(m_pMenu);
    return true;
}

game::ChangeLetterCommand::ChangeLetterCommand(dae::GameObject* pGameObject, MenuComponent* pMenu, glm::vec2 direction)
    : GameObjectCommand(pGameObject)
    , m_pMenu{ pMenu }
    , m_Direction{ direction }
{
}

bool game::ChangeLetterCommand::Execute(float)
{
    if (m_Direction.y == -1.f)
    {
        LeaderboardHandler::GetInstance().ChangeLetter(false, m_pMenu->GetItemSelected());
        return true;
    }
    else if (m_Direction.y == 1.f)
    {
        LeaderboardHandler::GetInstance().ChangeLetter(true, m_pMenu->GetItemSelected());
        return true;
    }
    return false;
}
