#pragma once
#include "ActionList.h"
#include "IEventSubscriber.h"

namespace FieaGameEngine
{
	class Reaction : public ActionList, public IEventSubscriber
	{
	protected:
		/// <summary>
		/// Protected constructor for Reaction that calls ActionList constructor with the child typeId.
		/// </summary>
		Reaction(RTTI::IdType typeId) : ActionList(typeId) {};
	};
}