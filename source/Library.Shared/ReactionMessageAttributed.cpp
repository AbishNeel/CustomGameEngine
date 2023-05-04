#include "ReactionMessageAttributed.h"

using namespace std;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(ReactionMessageAttributed);

	ReactionMessageAttributed::ReactionMessageAttributed(ReactionSubtypes subtype, GameState& gameState)
		: Attributed(ReactionMessageAttributed::TypeIdClass()), _subtype{ subtype }, _gameState{ &gameState }
	{
	}

	ReactionMessageAttributed* ReactionMessageAttributed::Clone() const
	{
		return new ReactionMessageAttributed{ *this };
	}

	ReactionSubtypes ReactionMessageAttributed::GetSubtype() const
	{
		return _subtype;
	}

	GameState& ReactionMessageAttributed::GetGameState() const
	{
		return *_gameState;
	}

	void ReactionMessageAttributed::SetSubtype(ReactionSubtypes type)
	{
		_subtype = type;
	}

	Vector<Signature> ReactionMessageAttributed::Signatures()
	{
		return Vector{ 
			Signature{ "Subtype", Datum::DatumTypes::Integer, 1, offsetof(ReactionMessageAttributed, _subtype)},
			Signature{ "GameState", Datum::DatumTypes::Pointer, 0, 0}
		};
	}
}