#include "ActionIncrement.h"

using namespace std;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ActionIncrement);

	ActionIncrement::ActionIncrement()
		: Action(ActionIncrement::TypeIdClass())
	{
	}

	ActionIncrement* ActionIncrement::Clone() const
	{
		return new ActionIncrement{ *this };
	}

	void ActionIncrement::Update(GameState&)
	{
		Datum* datum = Search(Target);
		if (datum == nullptr)
			throw runtime_error("Target Datum was not found");
		assert(datum->Type() == Datum::DatumTypes::Integer);
		datum->Get<int>() += Step;
	}

	Vector<Signature> ActionIncrement::Signatures()
	{
		return Vector{
			Signature { "Target", Datum::DatumTypes::String, 1, offsetof(ActionIncrement, Target)},
			Signature { "Step", Datum::DatumTypes::Integer, 1, offsetof(ActionIncrement, Step)}
		};
	}
}