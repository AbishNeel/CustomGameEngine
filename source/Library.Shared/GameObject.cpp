#include "GameObject.h"
#include "Action.h"

using namespace std;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(GameObject);

	GameObject::GameObject() 
		: Attributed(GameObject::TypeIdClass())
	{
	}

	GameObject::GameObject(RTTI::IdType idType)
		: Attributed(idType)
	{
	}

	GameObject* GameObject::Clone() const
	{
		return new GameObject{ *this };
	}

	void GameObject::Update(GameState& gameState)
	{
		UpdateChildren(gameState);
		UpdateActions(gameState);
	}

	void GameObject::UpdateChildren(GameState& gameState)
	{
		Datum& children = GetChildren();
		for (size_t i = 0; i < children.Size(); ++i)
		{
			assert(children[i].Is(GameObject::TypeIdClass()));
			GameObject& child = static_cast<GameObject&>(children[i]);
			child.Update(gameState);
		}
	}

	void GameObject::UpdateActions(GameState& gameState)
	{
		Datum& actions = GetActions();
		for (size_t i = 0; i < actions.Size(); ++i)
		{
			assert(actions[i].Is(Action::TypeIdClass()));
			Action& action = static_cast<Action&>(actions[i]);
			action.Update(gameState);
		}
	}

	void GameObject::CreateAction(const string& actionName, const string& instanceName)
	{
		Scope* createdScope = Factory<Scope>::Create(actionName);
		assert(createdScope != nullptr);
		assert(createdScope->Is(Action::TypeIdClass()));
		Action* action = static_cast<Action*>(createdScope);
		action->Name = instanceName;
		Adopt(*action, "Actions"s);
	}

	Datum& GameObject::GetChildren()
	{
		assert(IsPrescribedAttribute("Children"s));
		return _orderVector[6]->second;
	}

	Datum& GameObject::GetActions()
	{
		assert(IsPrescribedAttribute("Actions"));
		return _orderVector[7]->second;
	}

	Vector<Signature> GameObject::Signatures()
	{
		return Vector<Signature>
		{
			{ "Name", Datum::DatumTypes::String, 1, offsetof(GameObject, Name)},
			{ "Transform", Datum::DatumTypes::Unknown , 0, 0 },
			{ "Position", Datum::DatumTypes::Vector, 1, offsetof(GameObject,Transform.Position)},
			{ "Rotation", Datum::DatumTypes::Vector, 1, offsetof(GameObject, Transform.Rotation) },
			{ "Scale", Datum::DatumTypes::Vector, 1, offsetof(GameObject, Transform.Scale) },
			{ "Children", Datum::DatumTypes::Table, 0, 0},
			{ "Actions", Datum::DatumTypes::Table, 0, 0}
		};
	}
}