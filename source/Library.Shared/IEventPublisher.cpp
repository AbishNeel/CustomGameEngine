#include "IEventPublisher.h"
#include "IEventSubscriber.h"

using namespace std;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(IEventPublisher);

	void IEventPublisher::Deliver()
	{
		for (auto subscriber : _subscribers)
			subscriber->Notify(this);
	}
}