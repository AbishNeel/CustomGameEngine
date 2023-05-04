#pragma once
#include "IEventSubscriber.h"
#include "IEventPublisher.h"

namespace UnitTests
{
	class FooSubscriber final : public FieaGameEngine::IEventSubscriber
	{
		void Notify(FieaGameEngine::IEventPublisher* eventPublisher) override;

	public:
		int Count{ 0 };
	};
}