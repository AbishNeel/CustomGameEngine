#pragma once
#include "Action.h"
#include "ReactionMessageAttributed.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class ActionEvent final : public Action
	{
		RTTI_DECLARATIONS(ActionEvent, Action);

	public:
		ActionEvent();

		/// <summary>
		/// Virtual constructor for ActionEvent. Calling context is responsible for deleting this pointer.
		/// </summary>
		/// <returns> Pointer to the heap allocated cloned ActionEvent instance. </returns>
		ActionEvent* Clone() const override;

		/// <summary>
		/// Virtual Update function that creates and enqueues an Event of type ReactionMessageAttributed.
		/// </summary>
		/// <param name="gameState"> A reference to a GameState instance. </param>
		void Update(GameState& gameState) override;

		/// <summary>
		/// Static function that returns the Signatures of all Attributes of ActionEvent.
		/// </summary>
		/// <returns> The Vector of signatures of the Attributes of the ActionEvent class.</returns>
		static Vector<Signature> Signatures();

	private:
		/// <summary>
		/// Helper function to populate the ReactionMessageAttributed payload with the Auxiliary attributes of "this" object.
		/// </summary>
		/// <param name="reactionMessage"> Reference to the ReactionMessageAttributed to populate. </param>
		void PopulateArguments(ReactionMessageAttributed& reactionMessage);

		ReactionSubtypes _subtype{0};
		int _delay;
	};

	ConcreteFactory(ActionEvent, Scope);
}