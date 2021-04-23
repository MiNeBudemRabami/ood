#define CATCH_CONFIG_MAIN
#include "..\\catch.hpp"
#include "..\\WeatherStation\\Observer.h"

namespace
{

	class CMockObserver : public IObserver<bool>
	{
	public:
		bool IsNotified() const
		{
			return m_notified;
		}

		void ResetNotified()
		{
			m_notified = false;
		}

		void SetUnsubscribeSelf(IObservable<bool>* unsubscribeSelf = nullptr)
		{
			m_unsubscribeSelf = unsubscribeSelf;
		}

	private:
		void Update(bool const& data) final
		{
			assert(!data);
			(void)data;

			m_notified = true;

			if (m_unsubscribeSelf)
			{
				m_unsubscribeSelf->RemoveObserver(*this);
			}
		}

		bool m_notified = false;
		IObservable<bool>* m_unsubscribeSelf = nullptr;
	};

	class CMockObservable : public CObservable<bool>
	{
	private:
		bool GetChangedData() const final
		{
			return false;
		}
	};

}

TEST_CASE("test basic", "[single-file]")
{
	CMockObservable observable;

	CMockObserver observer1;
	observable.RegisterObserver(observer1);

	CMockObserver observer2;
	observable.RegisterObserver(observer2);

	CMockObserver observer3;

	observable.NotifyObservers();

	REQUIRE(observer1.IsNotified());
	REQUIRE(observer2.IsNotified());
	REQUIRE(!observer3.IsNotified());
}

TEST_CASE("TestObserverSelfUnsubscribe", "[single-file]")
{
	CMockObservable observable;

	CMockObserver observer1;
	observable.RegisterObserver(observer1);

	CMockObserver observer2;
	observer2.SetUnsubscribeSelf(&observable);
	observable.RegisterObserver(observer2);

	CMockObserver observer3;
	observable.RegisterObserver(observer3);

	observable.NotifyObservers();

	REQUIRE(observer1.IsNotified());
	REQUIRE(observer2.IsNotified());
	REQUIRE(observer3.IsNotified());

	observer1.ResetNotified();
	observer2.ResetNotified();
	observer3.ResetNotified();

	observable.NotifyObservers();

	REQUIRE(observer1.IsNotified());
	REQUIRE(!observer2.IsNotified());
	REQUIRE(observer3.IsNotified());
}
