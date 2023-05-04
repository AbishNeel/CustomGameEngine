#pragma once
#include "Attributed.h"
#include "RTTI.h"
#include "TypeManager.h"
#include "Factory.h"
#include "GameState.h"

namespace FieaGameEngine
{
	/// <summary>
	/// Transform struct which contains Vector4 variables for Position, Rotation and Scale.
	/// </summary>
	struct Transform final
	{
		glm::vec4 Position;
		glm::vec4 Rotation;
		glm::vec4 Scale;
	};

	/// <summary>
	/// GameObject class which derives from Attributed.
	/// </summary>
	class GameObject : public Attributed
	{
		RTTI_DECLARATIONS(GameObject, Attributed);

	public:
		GameObject();
		GameObject(const GameObject& other) = default;
		GameObject(GameObject&& other) noexcept = default;
		GameObject& operator=(const GameObject& rhs) = default;
		GameObject& operator=(GameObject&& rhs) noexcept = default;
		virtual ~GameObject() = default;

		/// <summary>
		/// Virtual Update function that is called every frame and calls Update on all children GameObjects and Actions.
		/// </summary>
		/// <param name="gameTime"> A const reference to a GameTime instance. </param>
		virtual void Update(GameState& gameState);

		/// <summary>
		/// Clone method that returns a heap allocated copy of "this" GameObject. Essentially a "virtual constrcutor".
		/// </summary>
		/// <returns> Pointer to the newly created GameObject. The calling context is responsible for deleting it.</returns>
		virtual GameObject* Clone() const override;

		/// <summary>
		/// Function to get all the children GameObjects of "this" GameObject.
		/// </summary>
		/// <returns> Datum containing all the children GameObjects. </returns>
		Datum& GetChildren();

		/// <summary>
		/// Getter for all the Actions of the GameObject.
		/// </summary>
		/// <returns> Reference to a Datum containing all the Actions of the GameObject. </returns>
		Datum& GetActions();

		/// <summary>
		/// Function to dynamically create and adopt a new Action to the GameObject.
		/// </summary>
		/// <param name="actionName"> The name of the Action to be created. </param>
		/// <param name="instanceName"> The name of the instance of the created Action. </param>
		void CreateAction(const std::string& actionName, const std::string& instanceName);

		/// <summary>
		/// Static function that gets the Signatures of all the Attributes of GameObject.
		/// </summary>
		/// <returns> The Vector of signatures of the Attributes of the GameObject class. </returns>
		static Vector<Signature> Signatures();

		std::string Name{};
		Transform Transform{};

	protected:
		/// <summary>
		/// Constructor that is responsible for calling Attributed's constructor with the passed in typeId.
		/// </summary>
		/// <param name="idType"> The idType to call Attributed's constructor with. </param>
		GameObject(RTTI::IdType idType);

		/// <summary>
		/// Helper function that calls Update on all children GameObjects.
		/// </summary>
		/// <param name="gameTime"> Const reference to a GameTime instance to call the children Updates with. </param>
		void UpdateChildren(GameState& gameState);

		/// <summary>
		/// Helper function that calls Update on all Actions of the GameObject.
		/// </summary>
		/// <param name="gameTime"> Const reference to a GameTime instance to call the Actions' Updates with. </param>
		void UpdateActions(GameState& gameState);
	};

	ConcreteFactory(GameObject, Scope);
}