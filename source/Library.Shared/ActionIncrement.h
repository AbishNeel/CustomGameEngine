#pragma once
#include "Action.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class ActionIncrement final : public Action
	{
		RTTI_DECLARATIONS(ActionIncrement, Action);

	public:
		ActionIncrement();
		ActionIncrement(const ActionIncrement& other) = default;
		ActionIncrement(ActionIncrement&& other) noexcept = default;
		ActionIncrement& operator=(const ActionIncrement& rhs) noexcept = default;
		ActionIncrement& operator=(ActionIncrement&& rhs) noexcept = default;
		~ActionIncrement() = default;

		/// <summary>
		/// Virtual constructor for ActionIncrement. Creates a heap allocated Clone of "this" ActionIncrement.
		/// </summary>
		/// <returns> A pointer to the newly Cloned ActionIncrement. Calling context is now responsible for deleting the pointer. </returns>
		ActionIncrement* Clone() const override;

		/// <summary>
		/// Virtual Update function that is called every frame. Every time it is called, it adds the step variable to the target variable.
		/// </summary>
		/// <param name="gameTime"> A const reference to a GameTime instance. </param>
		void Update(GameState& gameState) override;

		/// <summary>
		/// Static function that returns the Signatures of all Attributes of ActionIncrement.
		/// </summary>
		/// <returns> The Vector of signatures of the Attributes of the ActionIncrement class.</returns>
		static Vector<Signature> Signatures();

		std::string Target;
		int32_t Step;
	};

	ConcreteFactory(ActionIncrement, Scope);
}