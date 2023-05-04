#include "pch.h"
#include "Event.h"
#include "FooSubscriber.h"
#include "Foo.h"

using namespace FieaGameEngine;

namespace UnitTests
{
	void FooSubscriber::Notify(IEventPublisher* eventPublisher)
	{
		if (eventPublisher->Is(Event<Foo>::TypeIdClass()))
		{
			Event<Foo>* event = static_cast<Event<Foo>*>(eventPublisher);
			Count += event->Message().Data();
		}
	}
}