#pragma once
class Observer
{
public:
	virtual ~Observer() = default;
	virtual void Broadcast() = 0;
private:
};

