#pragma once
#include "Reaction.h"
#include "ReactionMessageAttributed.h"

namespace FieaGameEngine
{
	class ReactionAttributed : public Reaction
	{
		RTTI_DECLARATIONS(ReactionAttributed, Reaction);

	public:
		ReactionAttributed();

		virtual ~ReactionAttributed();

		/// <summary>
		/// Virtual constructor for ReactionAttributed. Calling context is responsible for deleting this pointer.
		/// </summary>
		/// <returns> Pointer to the heap allocated cloned ReactionAttributed instance. </returns>
		ReactionAttributed* Clone() const override;

		/// <summary>
		/// Notify method that responds to published events "this" object is subscribed.
		/// </summary>
		/// <param name="eventPublisher"> The EventPublisher that calls this event. </param>
		void Notify(IEventPublisher* eventPublisher) override;

		/// <summary>
		/// Static function to get the Signatures of attributed this type.
		/// </summary>
		/// <returns> Vector of the Attribute signatures of this type. </returns>
		static Vector<Signature> Signatures();

	protected:
		ReactionSubtypes _subtype;
	};

	ConcreteFactory(ReactionAttributed, Scope);
}