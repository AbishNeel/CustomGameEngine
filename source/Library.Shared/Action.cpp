#include "pch.h"
#include "Action.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Action);

	Action::Action(RTTI::IdType typeId)
		: Attributed(typeId)
	{
	}

	void Action::ExtractArguments(const Attributed& payload)
	{
		const auto& aux = payload.AuxiliaryAttributes();
		for (auto it = aux.begin(); it != aux.end(); ++it)
		{
			auto potentialArgument = Search(*it);
			if (potentialArgument == nullptr)
				continue;
			potentialArgument->Set(payload.Find(*it)->Front<int>());
		}
	}

	Vector<Signature> Action::Signatures()
	{
		return Vector{ Signature{"Name", Datum::DatumTypes::String, 1, offsetof(Action, Name)} };
	}
}