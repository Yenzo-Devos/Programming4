#pragma once
#include "Subject.h"

namespace dae
{
	class Observer
	{
		friend class Subject;
	public:
		Observer()
		: m_pNextObserver{ nullptr }
		{ }
		virtual ~Observer() = default;
		virtual void Broadcast() = 0;

	private:
		Observer* m_pNextObserver;
	};
}