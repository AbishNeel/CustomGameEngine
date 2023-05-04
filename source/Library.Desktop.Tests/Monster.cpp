#include "pch.h"
#include "Monster.h"

using namespace FieaGameEngine;

namespace UnitTests
{
	RTTI_DEFINITIONS(Monster);

	Monster::Monster() 
		: GameObject(Monster::TypeIdClass())
	{
	}

	Monster* Monster::Clone() const
	{
		return new Monster{ *this };
	}

	void Monster::Update(GameState& gameState)
	{
		UpdateChildren(gameState);
		UpdateActions(gameState);
		++UpdateCounter;
	}

	FieaGameEngine::Vector<FieaGameEngine::Signature> Monster::Signatures()
	{
		return FieaGameEngine::Vector{ FieaGameEngine::Signature{ "Health", Datum::DatumTypes::Integer, 1, offsetof(Monster, Health)} };
	}
}