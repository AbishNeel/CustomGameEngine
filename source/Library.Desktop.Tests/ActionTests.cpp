#include "pch.h"
#include "CppUnitTest.h"
#include "ActionListSwitch.h"
#include "JsonParseCoordinator.h"
#include "TableParseHelper.h"
#include "Monster.h"
#include "ActionIncrement.h"
#include "GameState.h"
#include "EventQueue.h"
#include "ActionExpression.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std;
using namespace UnitTests;


namespace LibraryDesktopTests
{
	TEST_CLASS(ActionTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&_startMemState);
#endif
		}
		TEST_METHOD_CLEANUP(Cleanup)
		{
#if defined(DEBUG) || defined(_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &_startMemState,
				&endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(ActionAttributeTests)
		{
			ActionListSwitch actionList;
			Assert::IsTrue(actionList.IsPrescribedAttribute("Actions"s));
			Assert::IsTrue(actionList.IsPrescribedAttribute("Name"s));
			Assert::IsTrue(actionList.IsPrescribedAttribute("Condition"s));
		}

		TEST_METHOD(ActionListIfTests)
		{
			auto mf = MonsterFactory{};
			auto aif = ActionIncrementFactory{};
			auto alif = ActionListSwitchFactory{};

			EventQueue eventQueue;
			GameTime gameTime;
			GameState gameState{ eventQueue, gameTime };

			const string filename = "../../../../../source/Library.Desktop.Tests/ActionsJson.json";
			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<TableParseHelper::TableWrapper>();
			JsonParseCoordinator parser{ wrapper };

			parser.AddHelper(make_shared<TableParseHelper>());
			parser.DeserializeObjectFromFile(filename);

			TableParseHelper::TableWrapper* rawWrapper = static_cast<TableParseHelper::TableWrapper*>(wrapper.get());

			Assert::AreEqual(size_t(1), rawWrapper->Data->Size());

			Monster* monster = dynamic_cast<Monster*>(rawWrapper->Data->operator[](0).Get<Scope*>(0));
			Assert::AreEqual("Monster Guy"s, monster->Name);
			Assert::AreEqual(100, monster->Health);

			monster->Update(gameState);
			Assert::AreEqual(105, monster->Health);

			ActionListSwitch& actionIf = dynamic_cast<ActionListSwitch&>(monster->GetActions()[0]);
			actionIf.Condition = 1;
			monster->Update(gameState);

			Assert::AreEqual(95, monster->Health);
		}

		TEST_METHOD(ActionListUpdateTests)
		{
			EventQueue eventQueue;
			GameTime gameTime;
			GameState gameState{ eventQueue, gameTime };

			Monster monster;
			ActionList* actionList = new ActionList{};
			ActionIncrement* actionIncrement = new ActionIncrement{};
			actionIncrement->Step = 10;
			actionIncrement->Target = "Health"s;
			actionList->Adopt(*actionIncrement, "Actions"s);
			monster.Adopt(*actionList, "Actions"s);

			Assert::AreEqual(0, monster.Health);
			monster.Update(gameState);
			Assert::AreEqual(10, monster.Health);
		}

		TEST_METHOD(ActionExpression)
		{
			EventQueue eventQueue;
			GameTime gameTime;
			GameState gameState{ eventQueue, gameTime };
			const string filename = "../../../../../source/Library.Desktop.Tests/ActionExpressionJson.json";

			ActionExpressionFactory aef;
			GameObjectFactory gof;

			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<TableParseHelper::TableWrapper>();
			JsonParseCoordinator parser{ wrapper };

			parser.AddHelper(make_shared<TableParseHelper>());
			parser.DeserializeObjectFromFile(filename);

			TableParseHelper::TableWrapper* rawWrapper = static_cast<TableParseHelper::TableWrapper*>(wrapper.get());
			GameObject* gameObject = dynamic_cast<GameObject*>(rawWrapper->Data->operator[](0).Get<Scope*>(0));

			Assert::IsTrue("AExpr"s == gameObject->Find("Actions")->Get<Scope*>(0)->Find("Name"s)->Get<string>(0));
			gameObject->Update(gameState);
			Assert::AreEqual("90.000000"s, gameObject->Find("Actions")->Get<Scope*>(0)->Find("Expression")->Get<string>(0));

		}

	private:
		inline static _CrtMemState _startMemState;
	};
}