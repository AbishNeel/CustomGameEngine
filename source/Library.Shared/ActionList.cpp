#include "ActionList.h"

using namespace std;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionList);

	ActionList::ActionList()
		: Action(ActionList::TypeIdClass())
	{
	}

	ActionList::ActionList(RTTI::IdType idType)
		: Action(idType)
	{
	}

	ActionList* ActionList::Clone() const
	{
		return new ActionList{ *this };
	}

	Vector<Signature> ActionList::Signatures()
	{
		return Vector{ Signature { "Actions", Datum::DatumTypes::Table, 0, 0} };
	}

	Datum& ActionList::Actions()
	{
		return _orderVector[2]->second;
	}

	void ActionList::Update(GameState& gameState)
	{
		UpdateActions(gameState);
	}

	void ActionList::UpdateActions(GameState& gameState)
	{
		Datum& childActions = Actions();
		for (size_t i = 0; i < childActions.Size(); ++i)
		{
			assert(childActions[i].Is(Action::TypeIdClass()));
			Action& action = static_cast<Action&>(childActions[i]);
			action.Update(gameState);
		}
	}
}