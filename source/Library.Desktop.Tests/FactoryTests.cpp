#include "pch.h"
#include "CppUnitTest.h"
#include "Factory.h"
#include "JsonParseCoordinator.h"
#include "AttributedFoo.h"
#include "AttributedBar.h"
#include "TableParseHelper.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace UnitTests;
using namespace std;
using namespace FieaGameEngine;

namespace LibraryDesktopTests
{
	TEST_CLASS(FactoryTests)
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

		TEST_METHOD(AttributedFooParseTest)
		{
			auto aff =AttributedFooFactory{};
			UNREFERENCED_LOCAL(aff);

			const string filename = "../../../../../source/Library.Desktop.Tests/AttributedFooJson.json";
			shared_ptr<JsonParseCoordinator::Wrapper> wrapper = make_shared<TableParseHelper::TableWrapper>();
			JsonParseCoordinator parser{ wrapper };

			parser.AddHelper(make_shared<TableParseHelper>());
			parser.DeserializeObjectFromFile(filename);

			TableParseHelper::TableWrapper* rawWrapper = static_cast<TableParseHelper::TableWrapper*>(wrapper.get());

			Assert::AreEqual(size_t(1), rawWrapper->Data->Size());

			AttributedFoo* attributedFoo = dynamic_cast<AttributedFoo*>(rawWrapper->Data->operator[](0).Get<Scope*>(0));
			Assert::AreEqual(5, attributedFoo->ExternalInteger);
			Assert::AreEqual(3.5f, attributedFoo->ExternalFloat);
			Assert::AreEqual("this is a string"s, attributedFoo->ExternalString);
			Assert::IsTrue(glm::vec4(1.0f, 23.4f, 98.1f, 0.0f) == attributedFoo->ExternalVector);
			Assert::IsTrue(glm::mat4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.1f, 11.1f, 12.1f, 13.1f, 14.1f, 15.1f, 16.1f) == attributedFoo->ExternalMatrix);

			Assert::AreEqual(10, attributedFoo->ExternalIntegerArray[0]);
			Assert::AreEqual(20, attributedFoo->ExternalIntegerArray[1]);
			Assert::AreEqual(30, attributedFoo->ExternalIntegerArray[2]);
			Assert::AreEqual(40, attributedFoo->ExternalIntegerArray[3]);

			Assert::AreEqual(10.5f, attributedFoo->ExternalFloatArray[0]);
			Assert::AreEqual(20.5f, attributedFoo->ExternalFloatArray[1]);
			Assert::AreEqual(30.5f, attributedFoo->ExternalFloatArray[2]);
			Assert::AreEqual(40.5f, attributedFoo->ExternalFloatArray[3]);

			Assert::AreEqual("first"s, attributedFoo->ExternalStringArray[0]);
			Assert::AreEqual("second"s, attributedFoo->ExternalStringArray[1]);
			Assert::AreEqual("third"s, attributedFoo->ExternalStringArray[2]);
			Assert::AreEqual("fourth"s, attributedFoo->ExternalStringArray[3]);

			Assert::IsTrue(glm::vec4(1.0f, 23.4f, 98.1f, 0.0f) == attributedFoo->ExternalVectorArray[0]);
			Assert::IsTrue(glm::vec4(3.0f, 13.4f, 8.1f, 10.0f) == attributedFoo->ExternalVectorArray[1]);

			Assert::IsTrue(glm::mat4(1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f, 9.9f, 10.1f, 11.1f, 12.1f, 13.1f, 14.1f, 15.1f, 16.1f) == attributedFoo->ExternalMatrixArray[0]);
			Assert::IsTrue(glm::mat4(1.5f, 2.5f, 3.5f, 4.5f, 5.5f, 6.5f, 7.5f, 8.5f, 9.5f, 10.5f, 11.5f, 12.5f, 13.5f, 14.5f, 15.5f, 16.5f) == attributedFoo->ExternalMatrixArray[1]);
		}

		TEST_METHOD(FindFactory)
		{
			auto aff = AttributedFooFactory{};
			UNREFERENCED_LOCAL(aff);

			Assert::IsNotNull(Factory<Scope>::Find("AttributedFoo"s));
			Assert::IsNull(Factory<Scope>::Find("AttributedBar"s));
		}

		TEST_METHOD(CreateFactory)
		{
			auto aff = AttributedFooFactory{};
			UNREFERENCED_LOCAL(aff);

			Scope* concreteScope = Factory<Scope>::Create("AttributedFoo"s);
			Assert::IsNotNull(concreteScope);
			delete(concreteScope);
		}

	private:
		inline static _CrtMemState _startMemState;
	};
}