#include "ReactionAttributed.h"
#include "Event.h"
#include "ActionIncrement.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ReactionAttributed);

	ReactionAttributed::ReactionAttributed()
		: Reaction(ReactionAttributed::TypeIdClass())
	{
		Event<ReactionMessageAttributed>::Subscribe(this);
	}

	ReactionAttributed::~ReactionAttributed()
	{
		Event<ReactionMessageAttributed>::Unsubscribe(this);
	}

	ReactionAttributed* ReactionAttributed::Clone() const
	{
		auto clone = new ReactionAttributed{ *this };
		Event<ReactionMessageAttributed>::Subscribe(clone);
		return clone;
	}

	Vector<Signature> ReactionAttributed::Signatures()
	{
		return Vector{ Signature{ "Subtype", Datum::DatumTypes::Integer, 1, offsetof(ReactionAttributed, _subtype)} };
	}

	void ReactionAttributed::Notify(IEventPublisher* eventPublisher)
	{
		assert(eventPublisher != nullptr);
		assert(eventPublisher->Is(Event<ReactionMessageAttributed>::TypeIdClass()));
		Event<ReactionMessageAttributed>* reactionEvent = static_cast<Event<ReactionMessageAttributed>*>(eventPublisher);
		if (reactionEvent->Message().GetSubtype() == _subtype)
		{
			for (size_t i = 0; i < Actions().Size(); ++i)
			{
				assert(Actions()[i].Is(Action::TypeIdClass()));
				Action& action = static_cast<Action&>(Actions()[i]);
				action.ExtractArguments(reactionEvent->Message());
			}
			UpdateActions(reactionEvent->Message().GetGameState());
		}
	}
}