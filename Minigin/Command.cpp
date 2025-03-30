#include "Command.h"
#include "GameObject.h"

dae::GameObjectCommand::GameObjectCommand(GameObject* pGameObject)
	: Command()
	, m_pGameObject{ pGameObject }
{
}

