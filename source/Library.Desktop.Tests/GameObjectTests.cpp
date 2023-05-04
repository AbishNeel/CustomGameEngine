#include "pch.h"
#include "CppUnitTest.h"
#include "GameObject.h"
#include "Datum.h"
#include "TableParseHelper.h"
#include "JsonParseCoordinator.h"
#include "Monster.h"
#include "ActionIncrement.h"
#include "GameState.h"
#include "EventQueue.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;
using namespace std;

namespace LibraryDesktopTests
{
	TEST_CLASS(GameObjectTests)
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
			if (_CrtMemDifference(&diffMemState, &_startMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(AttributesTest)
		{
			GameObject go;
			Assert::IsTrue(go.IsAttribute("Name"s));
			Assert::IsTrue(go.IsAttribute("Transform"s));
			Assert::IsTrue(go.IsAttribute("Position"s));
			Assert::IsTrue(go.IsAttribute("Rotation"s));
			Assert::IsTrue(go.IsAttribute("Scale"s));
			Assert::IsTrue(go.IsAttribute("Children"s));
		}

		TEST_METHOD(GameObjectParseTest)
		{
			auto gof = new GameObjectFactory{};

			const string filename = "../../../../../source/Library.Desktop.Tests/GameObjectJson.json";
			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<TableParseHelper::TableWrapper>();
			JsonParseCoordinator parser{ wrapper };

			parser.AddHelper(make_shared<TableParseHelper>());
			parser.DeserializeObjectFromFile(filename);
			delete (gof);

			TableParseHelper::TableWrapper* rawWrapper = static_cast<TableParseHelper::TableWrapper*>(wrapper.get());

			Assert::AreEqual(size_t(1), rawWrapper->Data->Size());

			GameObject* gameObject = dynamic_cast<GameObject*>(rawWrapper->Data->operator[](0).Get<Scope*>(0));
			Assert::AreEqual("TestGameObject"s, gameObject->Name);
			Assert::IsTrue(glm::vec4(1.0f, 23.4f, 98.1f, 0.0f) == gameObject->Transform.Position);
			Assert::IsTrue(glm::vec4(0.0f, 90.0f, 0.0f, 0.0f) == gameObject->Transform.Rotation);
			Assert::IsTrue(glm::vec4(1.0f, 1.0f, 1.0f, 0.0f) == gameObject->Transform.Scale);

			
			Datum& children = gameObject->GetChildren();
			Assert::AreEqual(size_t(2), children.Size());
			GameObject* child1 = dynamic_cast<GameObject*>(children.Front<Scope*>());
			GameObject* child2 = dynamic_cast<GameObject*>(children.Back<Scope*>());
			Assert::AreEqual("Child1"s, child1->Name);
			Assert::AreEqual("Child2"s, child2->Name);
		}

		TEST_METHOD(Clone)
		{
			auto gof = new GameObjectFactory{};
			UNREFERENCED_LOCAL(gof);

			const string filename = "../../../../../source/Library.Desktop.Tests/GameObjectJson.json";
			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<TableParseHelper::TableWrapper>();
			JsonParseCoordinator parser{ wrapper };

			parser.AddHelper(make_shared<TableParseHelper>());
			parser.DeserializeObjectFromFile(filename);
			delete (gof);

			TableParseHelper::TableWrapper* rawWrapper = static_cast<TableParseHelper::TableWrapper*>(wrapper.get());

			GameObject* gameObject = dynamic_cast<GameObject*>(rawWrapper->Data->operator[](0).Get<Scope*>(0));
			GameObject* clone = gameObject->Clone();

			Assert::AreEqual(gameObject->Name, clone->Name);
			Assert::IsTrue(gameObject->Transform.Position == clone->Transform.Position);
			Assert::IsTrue(gameObject->Transform.Rotation == clone->Transform.Rotation);
			Assert::IsTrue(gameObject->Transform.Scale == clone->Transform.Scale);

			delete(clone);
		}

		TEST_METHOD(Update)
		{
			EventQueue eventQueue;
			GameTime gameTime;
			GameState gameState{ eventQueue, gameTime };

			GameObject gameObject;
			Monster* monster = new Monster{};
			gameObject.Adopt(*monster, "Children");

			Assert::AreEqual(size_t(0), monster->UpdateCounter);
			gameObject.Update(gameState);
			Assert::AreEqual(size_t(1), monster->UpdateCounter);
		}

		TEST_METHOD(CreateAction)
		{
			auto aif = ActionIncrementFactory{};

			GameObject gameObject;
			gameObject.Name = "Cool GameObject"s;

			gameObject.CreateAction("ActionIncrement"s, "Random Name"s);

			Assert::IsTrue(gameObject.GetActions()[0].Is(ActionIncrement::TypeIdClass()));
			Assert::AreEqual("Random Name"s, gameObject.GetActions()[0].As<ActionIncrement>()->Name);
		}

	private:
		inline static _CrtMemState _startMemState;
	};
}