#pragma once
#include "Attributed.h"
#include "TypeManager.h"
#include "GameState.h"

namespace FieaGameEngine
{
	class Action : public Attributed
	{
		RTTI_DECLARATIONS(Action, Attributed);

	public:
		Action(const Action& other) = default;
		Action(Action&& other) noexcept = default;
		Action& operator=(const Action& rhs) = default;
		Action& operator=(Action&& rhs) noexcept = default;
		virtual ~Action() = default;

		virtual void Update(GameState& gameState) = 0;

		/// <summary>
		/// Static function that returns the Signatures of all Attributes of Action.
		/// </summary>
		/// <returns> The Vector of signatures of the Attributes of the Action class.</returns>
		static Vector<Signature> Signatures();

		/// <summary>
		/// Function to extract the auxiliary attributes from the payload and use them as paramters.
		/// </summary>
		/// <param name="payload"> Const reference to the payload to extract the auxiliary attributes from. </param>
		void ExtractArguments(const Attributed& payload);

		std::string Name;

	protected:
		/// <summary>
		/// Constructor that calls Attributed's constructor with the passed in typeId.
		/// </summary>
		/// <param name="typeId"> The typeId of the child Action to pass into Attributed's constructor. </param>
		Action(RTTI::IdType typeId);

		Scope _arguments;
	};
}