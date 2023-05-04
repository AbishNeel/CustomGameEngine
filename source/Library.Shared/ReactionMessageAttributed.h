#pragma once
#include "Attributed.h"
#include "TypeManager.h"
#include "GameState.h"

namespace FieaGameEngine
{
	enum class ReactionSubtypes
	{
		ItsNotLookingGoodBrev
	};

	class ReactionMessageAttributed final : public Attributed
	{
		RTTI_DECLARATIONS(ReactionMessageAttributed, Attributed);

	public:
		/// <summary>
		/// Constructor for ReactionMessageAttributed.
		/// </summary>
		/// <param name="subtype"> The reaction subtype of this object. </param>
		/// <param name="gameState"> The game state being used by the game loop. </param>
		ReactionMessageAttributed(ReactionSubtypes subtype, GameState& gameState);

		/// <summary>
		/// Virtual constructor for ReactionMessageAttributed. Calling context is responsible for deleting this pointer.
		/// </summary>
		/// <returns> Pointer to the heap allocated cloned ReactionMessageAttributed instance. </returns>
		ReactionMessageAttributed* Clone() const override;

		/// <summary>
		/// Getter for this instances's reaction subtype.
		/// </summary>
		/// <returns> The reaction subtype of this message.</returns>
		ReactionSubtypes GetSubtype() const;

		/// <summary>
		/// Function to set the reaction subtype of this message.
		/// </summary>
		/// <param name="type"> The value of reaction subtype to assign to this message. </param>
		void SetSubtype(ReactionSubtypes type);

		/// <summary>
		/// Function to get the game state from this message.
		/// </summary>
		/// <returns> Reference to the game state instance. </returns>
		GameState& GetGameState() const;

		/// <summary>
		/// Static function that returns the Signatures of all Attributes of ReactionMessageAttributed.
		/// </summary>
		/// <returns> The Vector of signatures of the Attributes of the ReactionMessageAttributed class.</returns>
		static Vector<Signature> Signatures();
	
	private:
		ReactionSubtypes _subtype;

		GameState* _gameState;
	};
}