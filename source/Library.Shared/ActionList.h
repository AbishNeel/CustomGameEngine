#pragma once
#include "Action.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class ActionList : public Action
	{
		RTTI_DECLARATIONS(ActionList, Action);

	public:
		ActionList();
		ActionList(const ActionList& other) = default;
		ActionList(ActionList&& other) noexcept = default;
		ActionList& operator=(const ActionList& rhs) = default;
		ActionList& operator=(ActionList&& rhs) noexcept = default;
		virtual ~ActionList() = default;

		/// <summary>
		/// Virtual constructor for ActionList. Creates a heap allocated Clone of "this" ActionList.
		/// </summary>
		/// <returns> A pointer to the newly Cloned ActionList. Calling context is now responsible for deleting the pointer. </returns>
		ActionList* Clone() const override;

		/// <summary>
		/// Virtual Update function that is called every frame and calls Update on all Actions in the ActionList.
		/// </summary>
		/// <param name="gameState"> A reference to a GameState instance. </param>
		virtual void Update(GameState& gameState) override;

		/// <summary>
		/// Getter for all the Actions in the ActionList.
		/// </summary>
		/// <returns> Reference to a Datum containing all the Actions in the ActionList. </returns>
		Datum& Actions();

		/// <summary>
		/// Static function that returns the Signatures of all Attributes of ActionList.
		/// </summary>
		/// <returns> The Vector of signatures of the Attributes of the ActionList class.</returns>
		static Vector<Signature> Signatures();

	protected:
		/// <summary>
		/// Constructor that calls Action's constructor with the passed in typeId.
		/// </summary>
		/// <param name="typeId"> The typeId of the child Action to pass into Action's constructor. </param>
		ActionList(RTTI::IdType typeId);

		/// <summary>
		/// Helper function that calls Update on all contained Actions.
		/// </summary>
		/// <param name="gameTime"> Const reference to a GameTime instance to call the oonatined Actions' Updates with. </param>
		void UpdateActions(GameState& gameState);
	};

	ConcreteFactory(ActionList, Scope);
}