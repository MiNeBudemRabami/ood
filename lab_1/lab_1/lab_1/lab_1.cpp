#include "pch.h"
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct IDanceBehavior
{
	virtual ~IDanceBehavior() {};
	virtual void Dance() = 0;
};

class DancinWals : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "I'm dancin wals!!" << endl;
	}
};

class DancinMenuet : public IDanceBehavior
{
public:
	void Dance() override
	{
		cout << "I'm dancin menuet!!" << endl;
	}
};

class DanceNoWay : public IDanceBehavior
{
public:
	void Dance() override
	{
	}
};

struct IFlyBehavior
{
	virtual ~IFlyBehavior() {};
	virtual void Fly() = 0;
};

class FlyWinthCounter : public IFlyBehavior
{
public:
	virtual ~FlyWinthCounter() = default;

	void Fly() final
	{
		++count;
		FlyCountet(count);
	}

	virtual void FlyCountet(unsigned count) = 0;

private:
	unsigned count = 0;
};

class FlyWithWings : public FlyWinthCounter
{
public:
	void FlyCountet(unsigned count) override
	{
		cout << "I'm flying with wings!! " << count << " times" << endl;
	}
};

class FlyNoWay : public IFlyBehavior
{
public:
	void Fly() override 
	{
	}
};


struct IQuackBehavior
{
	virtual ~IQuackBehavior() {};
	virtual void Quack() = 0;
};

class QuackBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Quack Quack!!!" << endl;
	}
};
class SqueakBehavior : public IQuackBehavior
{
public:
	void Quack() override
	{
		cout << "Squeek!!!" << endl;
	}
};

class MuteQuackBehavior : public IQuackBehavior
{
public:
	void Quack() override {}
};

class Duck
{
public:
	Duck(unique_ptr<IFlyBehavior> && flyBehavior, 
		unique_ptr<IQuackBehavior> && quackBehavior,
		unique_ptr<IDanceBehavior> && danceBehavior)

	: m_quackBehavior(move(quackBehavior)),
		m_danceBehavior(move(danceBehavior))
	{
		assert(m_quackBehavior);
		SetFlyBehavior(move(flyBehavior));
	}
	void Quack() const
	{
		m_quackBehavior->Quack();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_flyBehavior->Fly();
	}
	void Dance()
	{
		m_danceBehavior->Dance();
	}
	void SetFlyBehavior(unique_ptr<IFlyBehavior>&& flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = move(flyBehavior);
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	unique_ptr<IFlyBehavior> m_flyBehavior;
	unique_ptr<IQuackBehavior> m_quackBehavior;
	unique_ptr<IDanceBehavior> m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(make_unique<FlyWithWings>(), make_unique<QuackBehavior>(), make_unique<DancinWals>())
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(make_unique<FlyWithWings>(), make_unique<QuackBehavior>(), make_unique<DancinMenuet>())
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};
class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<MuteQuackBehavior>(), make_unique<DanceNoWay>())
	{
	}
	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<SqueakBehavior>(), make_unique<DanceNoWay>())
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(make_unique<FlyNoWay>(), make_unique<QuackBehavior>(), make_unique<DanceNoWay>())
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Dance();

	duck.Fly();
	duck.Fly();
	duck.Fly();
	cout << endl;
}

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	//modelDuck.SetFlyBehavior(make_unique<FlyWithWings>());
	//PlayWithDuck(modelDuck);
}