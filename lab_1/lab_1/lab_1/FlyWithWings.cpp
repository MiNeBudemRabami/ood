#include "pch.h"
#include "FlyWithWings.h"

class FlyWithWings : public FlyWithCounter
{
public:
	void FlyCounter(unsigned count) override
	{
		std::cout << "I'm flying with wings!! " << count << " times" << std::endl;
	}
};