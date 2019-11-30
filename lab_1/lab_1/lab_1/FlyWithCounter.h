#pragma once
#include "IFlyBehavior.h"

class FlyWinthCounter : public IFlyBehavior
{
public:
	virtual ~FlyWinthCounter() = default;
	virtual void FlyCountet(unsigned count) = 0;

private:
	unsigned count = 0;
};