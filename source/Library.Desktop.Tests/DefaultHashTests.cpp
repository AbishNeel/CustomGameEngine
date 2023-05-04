#include "pch.h"
#include "CppUnitTest.h"
#include "DefaultHash.h"
#include "Foo.h"
#include "ToStringSpecializations.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std;
using namespace UnitTests;

namespace LibraryDesktopTests
{
	TEST_CLASS(DefaultHashTests)
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

		TEST_METHOD(StringHash)
		{
			DefaultHash<string> hashFunc{};
			string a = "abc";
			string b = "abc";
			string c = "abcd";

			Assert::AreNotSame(a, b);
			Assert::AreEqual(hashFunc(a), hashFunc(b));
			Assert::AreNotEqual(hashFunc(a), hashFunc(c));
		}

		TEST_METHOD(CharStarHash)
		{
			DefaultHash<char*> hashFunc{};
			char* a = "abc";
			char* b = "cba";
			char* c = "abcd";

			Assert::AreNotSame(a, b);
			Assert::AreEqual(hashFunc(a), hashFunc(b));
			Assert::AreNotEqual(hashFunc(a), hashFunc(c));
		}

		TEST_METHOD(IntegerHash)
		{
			DefaultHash<int> hashFunc{};
			int a = 10;
			int b = 10;
			int c = 20;

			Assert::AreNotSame(a, b);
			Assert::AreEqual(hashFunc(a), hashFunc(b));
			Assert::AreNotEqual(hashFunc(a), hashFunc(c));
		}

		TEST_METHOD(FooHashFunc)
		{
			FooHash hashFunc{};
			Foo a{ 10 };
			Foo b{ 10 };
			Foo c{ 20 };

			Assert::AreNotSame(a, b);
			Assert::AreEqual(hashFunc(a), hashFunc(b));
			Assert::AreNotEqual(hashFunc(a), hashFunc(c));
		}

	private:
		inline static _CrtMemState _startMemState;
	};
}