#pragma once
#include "IEventPublisher.h"

namespace FieaGameEngine
{
	struct EventQueueArgs final
	{
		std::shared_ptr<IEventPublisher> eventPublisher;
		std::chrono::high_resolution_clock::time_point timeEnqueued;
		std::chrono::milliseconds delay;
	};

	class EventQueue final
	{
	public:
		EventQueue() = default;

		/// <summary>
		/// Function to enqueue an event publisher along with a delay to the EventQueue.
		/// </summary>
		/// <param name="eventPublisher"> Pointer to the EventPublisher to enqueue. </param>
		/// <param name="gameTime"> Const reference to a GameTime instance to get the time at which the Event was enqueued. </param>
		/// <param name="delay"> The time, in milliseconds, after which the Event is to be published. Defaulted to zero. </param>
		void Enqueue(std::shared_ptr<IEventPublisher> eventPublisher, const GameTime& gameTime, std::chrono::milliseconds delay = std::chrono::milliseconds::zero());

		/// <summary>
		/// Loops through the queue and publishes any expired events and deletes/requeues them after.
		/// </summary>
		/// <param name="gameTime">Const reference to a GameTime instance to check if the Events are expired. </param>
		void Update(const GameTime& gameTime);

		/// <summary>
		/// Function to clear the contents of the EventQueue.
		/// </summary>
		void Clear();

		/// <summary>
		/// Function to check if the EventQueue is empty.
		/// </summary>
		/// <returns> True if the EventQueue is empty, false if not. </returns>
		bool IsEmpty();

		/// <summary>
		/// Function to get the size of the EventQueue.
		/// </summary>
		/// <returns> The size of the EventQueue. </returns>
		std::size_t Size();

	private:
		Vector<EventQueueArgs> _eventQueue{ 17 };

		bool _isUpdating{ false };
	};
}