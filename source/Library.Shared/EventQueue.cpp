#include "EventQueue.h"
#include <algorithm>

using namespace std;

namespace FieaGameEngine
{
	void EventQueue::Enqueue(shared_ptr<IEventPublisher> eventPublisher, const GameTime& gameTime, chrono::milliseconds delay)
	{
		_eventQueue.PushBack(EventQueueArgs{ eventPublisher, gameTime.CurrentTime(), delay });
	}

	void EventQueue::Update(const GameTime& gameTime)
	{
		if (_isUpdating)
			return;

		_isUpdating = true;

		auto it = partition(_eventQueue.begin(), _eventQueue.end(), [&gameTime](const EventQueueArgs& args) { return gameTime.CurrentTime() < args.timeEnqueued + args.delay; });
		for (auto tempIt = it; tempIt != _eventQueue.end(); ++tempIt)
			(*tempIt).eventPublisher->Deliver();

		Vector<EventQueueArgs> requeueEvents{ _eventQueue.Capacity() };
		for (auto tempIt = it; tempIt != _eventQueue.end(); ++tempIt)
		{
			if ((*tempIt).eventPublisher.use_count() > size_t(1))
				requeueEvents.PushBack(*it);
		}
		_eventQueue.Remove(it, _eventQueue.end());

		for (it = requeueEvents.begin(); it != requeueEvents.end(); ++it)
			Enqueue((*it).eventPublisher, gameTime, (*it).delay);

		_isUpdating = false;
	}

	void EventQueue::Clear()
	{
		_eventQueue.Clear();
	}

	bool EventQueue::IsEmpty()
	{
		return _eventQueue.IsEmpty();
	}

	size_t EventQueue::Size()
	{
		return _eventQueue.Size();
	}
}