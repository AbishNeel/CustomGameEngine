#pragma once

namespace FieaGameEngine
{
	class IEventPublisher;
	class IEventSubscriber
	{
	public:
		IEventSubscriber() = default;
		IEventSubscriber(const IEventSubscriber& other) = default;
		IEventSubscriber& operator=(const IEventSubscriber& rhs) = default;
		IEventSubscriber(IEventSubscriber&& other) noexcept = default;
		IEventSubscriber& operator=(IEventSubscriber&& rhs) noexcept = default;
		virtual ~IEventSubscriber() = default;

		virtual void Notify(IEventPublisher* eventPublisher) = 0;
	};
}