#include "ActionListSwitch.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionListSwitch);

	ActionListSwitch::ActionListSwitch()
		: ActionList(ActionList::TypeIdClass())
	{
	}

	ActionListSwitch* ActionListSwitch::Clone() const
	{
		return new ActionListSwitch{ *this };
	}

	Vector<Signature> ActionListSwitch::Signatures()
	{
		return Vector{ Signature { "Condition", Datum::DatumTypes::Integer, 1, offsetof(ActionListSwitch, Condition)} };
	}

	void ActionListSwitch::Update(GameState& gameState)
	{
		assert(Actions()[Condition].Is(Action::TypeIdClass()));
		Action& action = static_cast<Action&>(Actions()[Condition]);
		action.Update(gameState);
	}
}