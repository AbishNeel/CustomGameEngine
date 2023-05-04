#include "Event.h"
#include "DefaultEquality.h"

namespace FieaGameEngine
{
	template <typename T>
	RTTI_DEFINITIONS(Event<T>);

	template <typename T>
	Event<T>::Event(T& message)
		: _message{ message }
	{
	}

	template <typename T>
	inline void Event<T>::Subscribe(IEventSubscriber* eventToQueue)
	{
		if (eventToQueue == nullptr)
			throw std::runtime_error("Cannot enqueue a null pointer");
		if (_subscribers.Find(eventToQueue) != _subscribers.end())
			return;

		_subscribers.PushBack(eventToQueue);
	}

	template <typename T>
	inline void Event<T>::Unsubscribe(IEventSubscriber* eventToRemove)
	{
		auto it = _subscribers.Find(eventToRemove);
		if (it != _subscribers.end())
		{
			auto end = it;
			++end;
			_subscribers.Remove(it, end);
		}
	}

	template <typename T>
	inline void Event<T>::UnsubscribeAll()
	{
		_subscribers.Clear();
	}

	template <typename T>
	inline T& Event<T>::Message()
	{
		return _message;
	}
}