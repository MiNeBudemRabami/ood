#pragma once
#include "IFlyBehavior.h"

class FlyWithCounter : public IFlyBehavior
{
public:
	virtual ~FlyWithCounter() = default;
	virtual void FlyCounter(unsigned count) = 0;

	void Fly() final;

private:
	unsigned count = 0;
};