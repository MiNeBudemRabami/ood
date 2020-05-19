#pragma once

#include "IFlyBehavior.h"
#include "FlyWithCounter.h"

class FlyWithWings: public FlyWithCounter
{
public:
	void Fly() override;
};
