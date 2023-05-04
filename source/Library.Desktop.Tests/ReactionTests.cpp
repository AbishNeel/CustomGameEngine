#include "pch.h"
#include "CppUnitTest.h"
#include "ReactionAttributed.h"
#include "ActionEvent.h"
#include "EventQueue.h"
#include "Monster.h"
#include "ActionIncrement.h"
#include "JsonParseCoordinator.h"
#include "TableParseHelper.h"
#include "Event.h"
#include "ReactionMessageAttributed.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std;
using namespace UnitTests;

namespace LibraryDesktopTests
{
	TEST_CLASS(ReactionTests)
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

		TEST_METHOD(ReactionTest)
		{
			auto mf = MonsterFactory{};
			auto aif = ActionIncrementFactory{};
			auto alif = ReactionAttributedFactory{};

			EventQueue queue;
			GameTime gt;
			GameState gameState{ queue, gt };

			const string filename = "../../../../../source/Library.Desktop.Tests/ReactionJson.json";
			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<TableParseHelper::TableWrapper>();
			JsonParseCoordinator parser{ wrapper };

			parser.AddHelper(make_shared<TableParseHelper>());
			parser.DeserializeObjectFromFile(filename);

			TableParseHelper::TableWrapper* rawWrapper = static_cast<TableParseHelper::TableWrapper*>(wrapper.get());

			Monster* monster = dynamic_cast<Monster*>(rawWrapper->Data->operator[](0).Get<Scope*>(0));
			ReactionAttributed* reaction = dynamic_cast<ReactionAttributed*>(&monster->GetActions()[0]);
			ActionIncrement* actionIncrement = dynamic_cast<ActionIncrement*>(&reaction->Actions()[0]);

			Assert::AreEqual(5, actionIncrement->Step);

			ActionEvent actionEvent;
			actionEvent.AppendAuxiliaryAttribute("Step"s).PushBack(10);
			actionEvent.Update(gameState);
			gameState.GetEventQueue().Update(gameState.GetGameTime());

			Assert::AreEqual(10, actionIncrement->Step);
		}

	private:
		inline static _CrtMemState _startMemState;
	};
}