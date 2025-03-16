#include "Subject.h"
#include "Observer.h"

dae::Subject::Subject()
	: m_pFirstObserver{ nullptr }
{
}

void dae::Subject::AddObserver(Observer* pObserver)
{
	pObserver->m_pNextObserver = m_pFirstObserver;
	m_pFirstObserver = pObserver;
}

void dae::Subject::RemoveObserver(Observer* pObserver)
{
	if (m_pFirstObserver == pObserver)
	{
		m_pFirstObserver = pObserver->m_pNextObserver;
		pObserver->m_pNextObserver = nullptr;
		return;
	}

	Observer* currentObserver = m_pFirstObserver;
	while (currentObserver != nullptr)
	{
		if (currentObserver->m_pNextObserver == pObserver)
		{
			currentObserver->m_pNextObserver = pObserver->m_pNextObserver;
			pObserver->m_pNextObserver = nullptr;
			return;
		}
		currentObserver = currentObserver->m_pNextObserver;
	}
}

void dae::Subject::Broadcast(GameObject* pGameObject, Event event)
{
	Observer* currentObserver = m_pFirstObserver;
	while (currentObserver != nullptr)
	{
		currentObserver->Broadcast(pGameObject, event);
		currentObserver = currentObserver->m_pNextObserver;
	}
}
