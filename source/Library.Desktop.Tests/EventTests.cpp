#include "pch.h"
#include "CppUnitTest.h"
#include "Event.h"
#include "FooSubscriber.h"
#include "EventQueue.h"
#include "GameClock.h"
#include "Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;
using namespace std;

namespace LibraryDesktopTests
{
	TEST_CLASS(EventTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(Deliver)
		{
			FooSubscriber fooSubscriber;
			Assert::AreEqual(0, fooSubscriber.Count);

			Foo foo{ 15 };
			Event<Foo> healthEvent{ foo };
			Event<Foo>::Subscribe(&fooSubscriber);
			healthEvent.Deliver();
			Assert::AreEqual(15, fooSubscriber.Count);

			Event<Foo>::Unsubscribe(&fooSubscriber);
			healthEvent.Deliver();
			Assert::AreEqual(15, fooSubscriber.Count);
		}

		TEST_METHOD(EventQueueUpdate)
		{
			GameClock gameClock;
			GameTime gameTime;
			FooSubscriber fooSubscriber;

			Event<Foo>::Subscribe(&fooSubscriber);
			Foo foo1{ 20 };
			Foo foo2{ 1 };
			shared_ptr<Event<Foo>> healthEvent = make_shared<Event<Foo>>(foo1);
			shared_ptr<Event<Foo>> permEvent = make_shared<Event<Foo>>(foo2);

			EventQueue eventQueue;

			gameClock.UpdateGameTime(gameTime);
			eventQueue.Enqueue(permEvent, gameTime, chrono::milliseconds{ 200 });
			gameClock.UpdateGameTime(gameTime);
			eventQueue.Enqueue(healthEvent, gameTime, chrono::milliseconds{ 1000 });
			healthEvent.reset();

			Assert::AreEqual(0, fooSubscriber.Count);
			while (eventQueue.Size() != size_t(1))
			{
				gameClock.UpdateGameTime(gameTime);
				eventQueue.Update(gameTime);
			}
			Assert::IsTrue(fooSubscriber.Count > 24);

			permEvent.reset();
			Event<Foo>::Unsubscribe(&fooSubscriber);
		}

	private:
		inline static _CrtMemState _startMemState;
	};
}