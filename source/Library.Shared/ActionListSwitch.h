#pragma once
#include "ActionList.h"

namespace FieaGameEngine
{
	class ActionListSwitch final: public ActionList
	{
		RTTI_DECLARATIONS(ActionListSwitch, ActionList);

	public:
		ActionListSwitch();
		ActionListSwitch(const ActionListSwitch& other) = default;
		ActionListSwitch(ActionListSwitch&& other) noexcept = default;
		ActionListSwitch& operator=(const ActionListSwitch& other)= default;
		ActionListSwitch& operator=(ActionListSwitch&& other) noexcept = default;
		~ActionListSwitch() = default;

		/// <summary>
		/// Virtual constructor for ActionListIf. Creates a heap allocated Clone of "this" ActionListIf.
		/// </summary>
		/// <returns> A pointer to the newly Cloned ActionListIf. Calling context is now responsible for deleting the pointer. </returns>
		ActionListSwitch* Clone() const override;

		/// <summary>
		/// Virtual Update function that is called every frame and calls Update on all Actions in the ActionListIf.
		/// </summary>
		/// <param name="gameTime"> A const reference to a GameTime instance. </param>
		void Update(GameState& gameState) override;

		/// <summary>
		/// Static function that returns the Signatures of all Attributes of ActionListIf.
		/// </summary>
		/// <returns> The Vector of signatures of the Attributes of the ActionListIf class.</returns>
		static Vector<Signature> Signatures();

		int32_t Condition;
	};

	ConcreteFactory(ActionListSwitch, Scope);
}