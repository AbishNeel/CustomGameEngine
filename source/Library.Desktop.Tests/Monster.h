#pragma once
#include "Scope.h"
#include "GameObject.h"

namespace UnitTests
{
	class Monster final : public FieaGameEngine::GameObject
	{
		RTTI_DECLARATIONS(Monster, FieaGameEngine::GameObject);

	public:
		Monster();
		Monster(const Monster& other) = default;
		Monster(Monster&& other) noexcept = default;
		Monster& operator=(const Monster& rhs) = default;
		Monster& operator=(Monster&& rhs) noexcept = default;
		~Monster() = default;

		Monster* Clone() const override;

		virtual void Update(FieaGameEngine::GameState& gameState) override;

		static FieaGameEngine::Vector<FieaGameEngine::Signature> Signatures();

		size_t UpdateCounter;

		int32_t Health;
	};

	ConcreteFactory(Monster, Scope);
}