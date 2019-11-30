#include "pch.h"
#include "FlyWithCounter.h"

using namespace std;

void FlyWithCounter::Fly() final
{
	++count;
	FlyCountet(count);
}
