#pragma once
#include "IEventPublisher.h"
#include "IEventSubscriber.h"

namespace FieaGameEngine
{
	template <typename T>
	class Event final : public IEventPublisher
	{
		RTTI_DECLARATIONS(Event, IEventPublisher);
	public:
		/// <summary>
		/// Constructor for Event.
		/// </summary>
		/// <param name="message"> The mesage that "this" event delivers to EventSubscribers. </param>
		explicit Event(T& message);

		/// <summary>
		/// Static function for an EventSubscriber to subscribe to an event of this type.
		/// </summary>
		/// <param name="eventToQueue"> Pointer to the event to add to the list of subscribers for events of this type. </param>
		/// <exception cref="runtime_error"> Throws if the passed in pointer to the EventPublisher points to null. </exception>
		static void Subscribe(IEventSubscriber* eventToQueue);

		/// <summary>
		/// Static function for an EventSubscriber to unsubscribe from an event of this type. 
		/// </summary>
		/// <param name="eventToRemove"> Pointer to the event to remove from the list of subscribers for this type. </param>
		static void Unsubscribe(IEventSubscriber* eventToRemove);

		/// <summary>
		/// Static function that clears the list of subscribers for events of this type.
		/// </summary>
		static void UnsubscribeAll();

		/// <summary>
		/// Function to get the message/payload contained by this Event.
		/// </summary>
		/// <returns> A reference to the message/payload contained by this Event. </returns>
		T& Message();

	private:
		T _message{};
	};
}
#include "Event.inl"