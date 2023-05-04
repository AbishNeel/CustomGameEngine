#include "pch.h"
#include "CppUnitTest.h"
#include <memory>
#include "IntegerParseHelper.h"
#include "JsonParseCoordinator.h"
#include <fstream>
#include <ostream>
#include "TableParseHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTests;
using namespace std;
using namespace FieaGameEngine;

namespace LibraryDesktopTests
{
	TEST_CLASS(ParserTests)
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

		TEST_METHOD(IntegerTests)
		{
			string inputString = R"({ "integer": 100 })";
			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<IntegerParseHelper::IntWrapper>();
			JsonParseCoordinator parser{ wrapper };

			parser.AddHelper(make_shared<IntegerParseHelper>());
			parser.DeserializeObject(inputString);

			IntegerParseHelper::IntWrapper* rawWrapper = static_cast<IntegerParseHelper::IntWrapper*>(wrapper.get());
			Assert::AreEqual(int32_t(100), rawWrapper->Data.Front());
			Assert::AreEqual(size_t(1), rawWrapper->Data.Size());
		}

		TEST_METHOD(IntegerArrayTests)
		{
			string inputString = R"({ "integer": [ 10, 20, 30, 40 ] })";
			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<IntegerParseHelper::IntWrapper>();
			JsonParseCoordinator parser{ wrapper };

			parser.AddHelper(make_shared<IntegerParseHelper>());
			parser.DeserializeObject(inputString);

			IntegerParseHelper::IntWrapper* rawWrapper = static_cast<IntegerParseHelper::IntWrapper*>(wrapper.get());
			Assert::AreEqual(int32_t(10), rawWrapper->Data.Front());
			Assert::AreEqual(int32_t(40), rawWrapper->Data.Back());
			Assert::AreEqual(size_t(4), rawWrapper->Data.Size());
		}

		TEST_METHOD(DeserializeObjectFromFile)
		{
			const string fileName = "TestFile.json";
			const string inputString = R"({ "integer": 100 })";

			ofstream outputFile(fileName);
			Assert::IsTrue(outputFile.good());

			outputFile << inputString;
			outputFile.close();

			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<IntegerParseHelper::IntWrapper>();
			JsonParseCoordinator parser{ wrapper };

			parser.AddHelper(make_shared<IntegerParseHelper>());
			parser.DeserializeObjectFromFile(fileName);

			IntegerParseHelper::IntWrapper* rawWrapper = static_cast<IntegerParseHelper::IntWrapper*>(wrapper.get());
			Assert::AreEqual(int32_t(100), rawWrapper->Data.Front());
			Assert::AreEqual(size_t(1), rawWrapper->Data.Size());
		}

		TEST_METHOD(MoveSemantics)
		{
			//Move constructor
			{
				shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<IntegerParseHelper::IntWrapper>();
				JsonParseCoordinator parser{ wrapper };
				parser.AddHelper(make_shared<IntegerParseHelper>());

				JsonParseCoordinator newParser{ move(parser) };

#pragma warning(push)
#pragma warning(disable:26800)
				Assert::AreEqual(size_t(0), parser.GetHelpers().Size());
				Assert::AreEqual(size_t(1), newParser.GetHelpers().Size());
#pragma  warning(pop)
			}

			//Move assignment operator
			{
				shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<IntegerParseHelper::IntWrapper>();
				JsonParseCoordinator parser{ wrapper };
				parser.AddHelper(make_shared<IntegerParseHelper>());

				JsonParseCoordinator newParser{ wrapper };
				newParser = move(parser);

#pragma warning(push)
#pragma warning(disable:26800)
				Assert::AreEqual(size_t(0), parser.GetHelpers().Size());
				Assert::AreEqual(size_t(1), newParser.GetHelpers().Size());
#pragma  warning(pop)
			}
		}

		TEST_METHOD(AddRemoveHelpers)
		{
			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<IntegerParseHelper::IntWrapper>();
			JsonParseCoordinator parser{ wrapper };

			parser.AddHelper(make_shared<IntegerParseHelper>());
			Assert::AreEqual(size_t(1), parser.GetHelpers().Size());

			parser.AddHelper(make_shared<IntegerParseHelper>());
			Assert::AreEqual(size_t(1), parser.GetHelpers().Size());

			parser.RemoveHelper(make_shared<IntegerParseHelper>());
			Assert::AreEqual(size_t(0), parser.GetHelpers().Size());
		}

		TEST_METHOD(GetSetWrapper)
		{
			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<IntegerParseHelper::IntWrapper>();
			JsonParseCoordinator parser{ wrapper };

			shared_ptr<JsonParseCoordinator::Wrapper> newWrapper = make_shared<IntegerParseHelper::IntWrapper>();
			Assert::IsTrue(wrapper == parser.GetWrapper());
			Assert::IsFalse(newWrapper == parser.GetWrapper());

			parser.SetWrapper(newWrapper);
			Assert::IsTrue(newWrapper == parser.GetWrapper());
			Assert::IsFalse(wrapper == parser.GetWrapper());
		}

		TEST_METHOD(Clone)
		{
			//IntParser
			{
				shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<IntegerParseHelper::IntWrapper>();
				JsonParseCoordinator parser{ wrapper };
				parser.AddHelper(make_shared<IntegerParseHelper>());

				JsonParseCoordinator* clone = parser.Clone();
				Assert::IsTrue(clone->GetHelpers().Front() != parser.GetHelpers().Front());
				Assert::IsTrue(clone->GetWrapper() != parser.GetWrapper());

				delete(clone);
			}

			//TableParser
			{
				shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<TableParseHelper::TableWrapper>();
				JsonParseCoordinator parser{ wrapper };
				parser.AddHelper(make_shared<TableParseHelper>());

				JsonParseCoordinator* clone = parser.Clone();
				Assert::IsTrue(clone->GetHelpers().Front() != parser.GetHelpers().Front());
				Assert::IsTrue(clone->GetWrapper() != parser.GetWrapper());

				delete(clone);
			}
		}

		TEST_METHOD(TableParsing)
		{
			const string filename = "../../../../../source/Library.Desktop.Tests/TestJson.json";
			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<TableParseHelper::TableWrapper>();
			JsonParseCoordinator parser{ wrapper };

			parser.AddHelper(make_shared<TableParseHelper>());
			parser.DeserializeObjectFromFile(filename);

			TableParseHelper::TableWrapper* rawWrapper = static_cast<TableParseHelper::TableWrapper*>(wrapper.get());

			Assert::AreEqual(size_t(6), rawWrapper->Data->Size());
			Scope& scope = *rawWrapper->Data.get();
			Datum* datum = scope.Find("AHealth"s);
			Assert::AreEqual(size_t(0), datum->Find(100));
			Assert::AreEqual(size_t(1), datum->Find(2));
			Assert::AreEqual(size_t(2), datum->Find(90));

			datum = scope.Find("BTransform"s);
			Assert::IsTrue(glm::vec4(1.0f, 23.4f, 98.1f, 0.0f) == datum->Front<glm::vec4>());

			datum = scope.Find("CWeapon"s)->operator[](0).Find("ASelectedWeapon"s);
			Assert::AreEqual(3, datum->Front<int>());

			datum = scope.Find("CWeapon"s)->operator[](0).Find("BMelee"s)->operator[](0).Find("ASword"s)->operator[](0).Find("AKatana"s);
			Assert::AreEqual(1, datum->operator[](0).Find("Aid"s)->Front<int>());
			Assert::AreEqual(100.59f, datum->operator[](0).Find("Damage"s)->Front<float>());

			datum = scope.Find("CWeapon"s)->operator[](0).Find("BMelee"s)->operator[](0).Find("ASword"s)->operator[](0).Find("BRapier"s);
			Assert::AreEqual(2, datum->operator[](0).Find("Aid"s)->Front<int>());
			Assert::AreEqual(size_t(0), datum->operator[](0).Find("Damage"s)->Find(70.59f));
			Assert::AreEqual(size_t(1), datum->operator[](0).Find("Damage"s)->Find(189.90f));
			Assert::AreEqual(size_t(2), datum->operator[](0).Find("Damage"s)->Find(228.9f));

			datum = scope.Find("CWeapon"s)->operator[](0).Find("BMelee"s)->operator[](0).Find("BSpear"s)->operator[](0).Find("AJavelin"s);
			Assert::AreEqual(3, datum->operator[](0).Find("Aid"s)->Front<int>());
			Assert::AreEqual(270.06f, datum->operator[](0).Find("Damage"s)->Front<float>());

			datum = scope.Find("Name"s);
			Assert::AreEqual("Monster"s, datum->Front<string>());

			datum = scope.Find("Matrix"s);
			Assert::IsTrue(glm::mat4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.1f, 11.1f, 12.1f, 13.1f, 14.1f, 15.1f, 16.1f) == datum->Front<glm::mat4>());
		}

	private:
		inline static _CrtMemState _startMemState;
	};
}