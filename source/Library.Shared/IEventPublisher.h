#pragma once
#include "RTTI.h"
#include "GameTime.h"
#include "Vector.h"

namespace FieaGameEngine
{
	class IEventSubscriber;
	class IEventPublisher : public RTTI
	{
		RTTI_DECLARATIONS(IEventPublisher, RTTI);

	public:
		IEventPublisher() = default;
		IEventPublisher(const IEventPublisher& other) = default;
		IEventPublisher& operator=(const IEventPublisher& rhs) = default;
		IEventPublisher(IEventPublisher&& other) noexcept = default;
		IEventPublisher& operator=(IEventPublisher&& rhs) noexcept = default;
		virtual ~IEventPublisher() = default;

		/// <summary>
		/// Calss notify on all instances subscribed to the event of this type.
		/// </summary>
		void Deliver();

	protected:
		inline static Vector<IEventSubscriber*> _subscribers{17};
	};
}