#include "ActionEvent.h"
#include "Event.h"

using namespace std;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionEvent);

	ActionEvent::ActionEvent()
		: Action(ActionEvent::TypeIdClass())
	{
	}

	ActionEvent* ActionEvent::Clone() const
	{
		return new ActionEvent{ *this };
	}

	void ActionEvent::Update(GameState& gameState)
	{
		ReactionMessageAttributed reactionMessage{ _subtype, gameState };
		PopulateArguments(reactionMessage);
		shared_ptr reactionEvent = make_shared<Event<ReactionMessageAttributed>>(reactionMessage);
		gameState.GetEventQueue().Enqueue(reactionEvent, gameState.GetGameTime(), chrono::milliseconds(_delay));
	}

	void ActionEvent::PopulateArguments(ReactionMessageAttributed& reactionMessage)
	{
		const auto& auxiliaryAttributes = AuxiliaryAttributes();
		for (auto it = auxiliaryAttributes.begin(); it != auxiliaryAttributes.end(); ++it)
		{
			Datum& auxDatum = reactionMessage.AppendAuxiliaryAttribute(*it);
			auxDatum = operator[](*it);
		}
	}

	Vector<Signature> ActionEvent::Signatures()
	{
		return Vector{ 
			Signature{ "Subtype", Datum::DatumTypes::Integer, 1, offsetof(ActionEvent, _subtype)},
			Signature{ "Delay", Datum::DatumTypes::Integer, 1, offsetof(ActionEvent, _delay)}						
		};
	}
}