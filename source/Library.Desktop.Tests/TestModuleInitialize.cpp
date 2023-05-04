#include "pch.h"
#include "CppUnitTest.h"
#include "AttributedFoo.h"
#include "AttributedBar.h"
#include "RTTI.h"
#include "GameObject.h"
#include "Monster.h"
#include "ActionListSwitch.h"
#include "ActionIncrement.h"
#include "ReactionAttributed.h"
#include "ActionEvent.h"
#include "ReactionMessageAttributed.h"
#include "ActionExpression.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;
using namespace std;

namespace UnitTestsLibraryDesktop
{
	TEST_MODULE_INITIALIZE(TestModuleInitialize)
	{
		TypeManager::CreateInstance();
		TypeManager::GetInstance()->RegisterType<AttributedFoo, Attributed>(AttributedFoo::Signatures());
		TypeManager::GetInstance()->RegisterType<AttributedBar, AttributedFoo>(AttributedBar::Signatures());
		TypeManager::GetInstance()->RegisterType<GameObject, Attributed>(GameObject::Signatures());
		TypeManager::GetInstance()->RegisterType<Monster, GameObject>(Monster::Signatures());
		TypeManager::GetInstance()->RegisterType<Action, Attributed>(Action::Signatures());
		TypeManager::GetInstance()->RegisterType<ActionList, Action>(ActionList::Signatures());
		TypeManager::GetInstance()->RegisterType<ActionListSwitch, ActionList>(ActionListSwitch::Signatures());
		TypeManager::GetInstance()->RegisterType<ActionIncrement, Action>(ActionIncrement::Signatures());
		TypeManager::GetInstance()->RegisterType<ReactionAttributed, ActionList>(ReactionAttributed::Signatures());
		TypeManager::GetInstance()->RegisterType<ActionEvent, Action>(ActionEvent::Signatures());
		TypeManager::GetInstance()->RegisterType<ReactionMessageAttributed, Attributed>(ReactionMessageAttributed::Signatures());
		TypeManager::GetInstance()->RegisterType<ActionExpression, Action>(ActionExpression::Signatures());
	}

	TEST_MODULE_CLEANUP(TestModuleCleanup)
	{
		TypeManager::GetInstance()->_signatureMap.Clear();
		TypeManager::DestroyInstance();
	}
}