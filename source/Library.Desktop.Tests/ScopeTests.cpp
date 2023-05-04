#include "pch.h"
#include "CppUnitTest.h"
#include "Scope.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std;


namespace LibraryDesktopTests
{
	TEST_CLASS(ScopeTests)
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

		TEST_METHOD(Constructor)
		{
			Scope scope{10};
			Assert::AreEqual(size_t(0), scope.Size());
			Assert::IsNull(scope.GetParent());
		}

		TEST_METHOD(CopySemantics)
		{
			//Copy constructor
			{
				Scope rootScope;
				Scope& scope = rootScope.AppendScope("hello"s);
				Scope& newAppendedScope = scope.AppendScope("bye"s);
				newAppendedScope.Append("string"s);
				Datum& intDatum = scope.Append("int datum"s);
				intDatum.PushBack(5);

				Scope newRoot{ scope };
				Assert::IsTrue(newRoot == scope);
			}

			//Copy assignment operator
			{
				Scope rootScope;
				Scope& scope = rootScope.AppendScope("hello"s);
				Scope& newAppendedScope = scope.AppendScope("bye"s);
				newAppendedScope.Append("string"s);
				Datum& intDatum = scope.Append("int datum"s);
				intDatum.PushBack(5);

				Scope newRoot;
				Scope& nestedScope = newRoot.AppendScope("new"s);
				nestedScope = scope;
				Assert::IsTrue(nestedScope == scope);
			}
		}

		TEST_METHOD(MoveSemantics)
		{
			//Move constructor
			{
				Scope rootScope;
				Scope& scope = rootScope.AppendScope("hello"s);
				Scope& newAppendedScope = scope.AppendScope("bye"s);
				newAppendedScope.Append("string"s);
				Datum& intDatum = scope.Append("int datum"s);
				intDatum.PushBack(5);

				Scope scopeRef{ scope };
				Scope newRoot{ move(scope) };
				Assert::IsTrue(newRoot == scopeRef);
			}

			//Move assignment operator
			{
				Scope rootScope;
				Scope& scope = rootScope.AppendScope("hello"s);
				Scope& newAppendedScope = scope.AppendScope("bye"s);
				newAppendedScope.Append("string"s);
				Datum& intDatum = scope.Append("int datum"s);
				intDatum.PushBack(5);

				Scope newRoot;
				Scope& nestedScope = newRoot.AppendScope("new"s);

				Scope scopeRef{ scope };
				nestedScope = move(scope);
				Assert::IsTrue(nestedScope == scopeRef);
			}
		}

		TEST_METHOD(Append)
		{
			Scope rootScope;
			Datum& appendedDatum = rootScope.Append("hello"s);
			Assert::IsTrue(Datum::DatumTypes::Unknown == appendedDatum.Type());
			Assert::IsTrue(&appendedDatum == rootScope.Find("hello"s));
			Assert::IsTrue(rootScope.GetParent() == nullptr);
		}

		TEST_METHOD(AppendScope)
		{
			Scope rootScope;
			Scope* childScope = &rootScope.AppendScope("hello"s);

			Assert::IsTrue(rootScope.GetParent() == nullptr);
			Assert::IsTrue(&rootScope == childScope->GetParent());

			Datum& appendedDatum = rootScope.Append("float datum"s);
			appendedDatum.PushBack(5.5f);
			Assert::ExpectException<runtime_error>([&rootScope]() { rootScope.AppendScope("float datum"s); });
		}

		TEST_METHOD(Find)
		{
			Scope rootScope;
			Datum& appendedDatum = rootScope.Append("hello"s);
			Assert::IsTrue(&appendedDatum == rootScope.Find("hello"s));
			Assert::IsTrue(nullptr == rootScope.Find("bye"s));

			const Scope constScope{ rootScope };
			Assert::IsTrue(appendedDatum == *constScope.Find("hello"s));
			Assert::IsTrue(nullptr == constScope.Find("bye"s));
		}

		TEST_METHOD(Search)
		{
			Scope rootScope;
			Scope& scope = rootScope.AppendScope("hello"s);
			Scope& newAppendedScope = scope.AppendScope("bye"s);
			newAppendedScope.Append("string"s);
			Datum& intDatum = scope.Append("int datum"s);

			Assert::IsTrue(&intDatum == scope.Search("int datum"s));
			Assert::IsTrue(&intDatum == newAppendedScope.Search("int datum"s));
			Assert::IsTrue(nullptr == rootScope.Search("int datum"s));

			Scope* outScope = &newAppendedScope;

			newAppendedScope.Search("hello"s, outScope);
			Assert::IsTrue(outScope == &scope);


			const Scope constScope{ scope };
			const Scope& childScope = constScope.Find("bye"s)->operator[](0);
			Assert::IsTrue(intDatum == *childScope.Search("int datum"s));
		}

		TEST_METHOD(FindContainedScope)
		{
			Scope rootScope;
			Scope& scope = rootScope.AppendScope("hello"s);
			Scope& newAppendedScope = scope.AppendScope("bye"s);
			Datum& datum = newAppendedScope.Append("string"s);
			Scope& lastScope = newAppendedScope.AppendScope("string"s);

			pair<Datum*, size_t> result = newAppendedScope.FindContainedScope(&lastScope);
			Assert::IsTrue(&datum == result.first);
			Assert::IsTrue(size_t(0) == result.second);
			Assert::IsNull(scope.FindContainedScope(&lastScope).first);


			const Scope constScope{ scope };
			Assert::IsNull(constScope.FindContainedScope(&lastScope).first);
		}

		TEST_METHOD(Adopt)
		{
			Scope rootScope;
			Scope& scope = rootScope.AppendScope("hello"s);
			Scope newParent;
			Datum& intDatum = newParent.Append("int datum"s);
			intDatum.PushBack(5);

			Assert::IsTrue(scope.GetParent() == &rootScope);
			newParent.Adopt(scope, "child"s);
			Assert::IsTrue(scope.GetParent() == &newParent);

			Assert::ExpectException<runtime_error>([&scope, &rootScope]() { scope.Adopt(rootScope, "fail"s); });
			Assert::ExpectException<runtime_error>([&rootScope, &newParent]() { newParent.Adopt(rootScope, "int datum"s); });
		}

		TEST_METHOD(Orphan)
		{
			Scope rootScope;
			Scope& scope = rootScope.AppendScope("hello"s);
			scope.AppendScope("new"s);

			Assert::IsTrue(scope.GetParent() == &rootScope);
			Scope* orphanedScope = scope.Orphan();
			Assert::IsTrue(scope.GetParent() == nullptr);
			delete(orphanedScope);
		}

		TEST_METHOD(Clear)
		{
			Scope rootScope;
			Scope& scope = rootScope.AppendScope("hello"s);
			Scope& newAppendedScope = scope.AppendScope("bye"s);
			newAppendedScope.Append("string"s);
			Datum& intDatum = scope.Append("int datum"s);
			intDatum.PushBack(5);

			Assert::IsTrue(scope.Size() > size_t(0));
			scope.Clear();
			Assert::AreEqual(size_t(0), scope.Size());
		}

		TEST_METHOD(GetParent)
		{
			Scope rootScope;
			Scope& scope = rootScope.AppendScope("hello"s);
			Scope& newAppendedScope = scope.AppendScope("bye"s);

			Assert::IsTrue(&scope == newAppendedScope.GetParent());
			Assert::IsTrue(&rootScope == scope.GetParent());
			Assert::IsNull(rootScope.GetParent());


			const Scope constScope{ scope };
			Assert::IsNull(constScope.GetParent());
		}

		TEST_METHOD(IsAncestorOf)
		{
			Scope rootScope;
			Scope& scope = rootScope.AppendScope("hello"s);
			Scope& newAppendedScope = scope.AppendScope("bye"s);

			Assert::IsFalse(newAppendedScope.IsAncestorOf(rootScope));
			Assert::IsTrue(rootScope.IsAncestorOf(newAppendedScope));
		}

		TEST_METHOD(IsDescendantOf)
		{
			Scope rootScope;
			Scope& scope = rootScope.AppendScope("hello"s);
			Scope& newAppendedScope = scope.AppendScope("bye"s);

			Assert::IsTrue(newAppendedScope.IsDescendantOf(rootScope));
			Assert::IsFalse(rootScope.IsDescendantOf(newAppendedScope));
		}

		TEST_METHOD(OperatorBracket)
		{
			//String paramater
			{
				Scope rootScope;
				Datum d1 = rootScope.Append("A"s);
				Datum d2 = rootScope.Append("B"s);
				Datum d3 = rootScope.Append("C"s);

				Assert::IsTrue(d1 == rootScope["A"s]);
				Assert::IsTrue(d2 == rootScope["B"s]);
				Assert::IsTrue(d3 == rootScope["C"s]);

				Datum d4 = rootScope["D"s];
				Assert::IsTrue(d4 == rootScope[3]);
			}

			//size_t parameter
			{
				Scope rootScope;
				Datum d1 = rootScope.Append("A"s);
				Datum d2 = rootScope.Append("B"s);
				Datum d3 = rootScope.Append("C"s);

				Assert::IsTrue(d1 == rootScope[0]);
				Assert::IsTrue(d2 == rootScope[1]);
				Assert::IsTrue(d3 == rootScope[2]);

				Assert::ExpectException<out_of_range>([&rootScope]() { rootScope[3]; });


				const Scope constScope{ rootScope };

				Assert::IsTrue(d1 == constScope[0]);
				Assert::IsTrue(d2 == constScope[1]);
				Assert::IsTrue(d3 == constScope[2]);

				Assert::ExpectException<out_of_range>([&constScope]() { constScope[3]; });
			}
		}

		TEST_METHOD(EqualityOperators)
		{
			// == operator
			{
				Scope rootScope;
				Scope& scope = rootScope.AppendScope("hello"s);
				Scope& newAppendedScope = scope.AppendScope("bye"s);
				newAppendedScope.Append("string"s);
				Datum& intDatum = scope.Append("int datum"s);
				intDatum.PushBack(5);

				Scope newRoot;
				Scope& nestedScope = newRoot.AppendScope("new"s);
				nestedScope = scope;
				Assert::IsTrue(nestedScope == scope);
				Assert::IsFalse(nestedScope.Equals(nullptr));
			}

			// != operator
			{
				Scope rootScope;
				Scope& scope = rootScope.AppendScope("hello"s);
				Scope& newAppendedScope = scope.AppendScope("bye"s);
				newAppendedScope.Append("string"s);
				Datum& intDatum = scope.Append("int datum"s);
				intDatum.PushBack(5);

				Scope newRoot;
				Scope& nestedScope = newRoot.AppendScope("new"s);
				Assert::IsTrue(nestedScope != scope);
			}
		}

	private:
		inline static _CrtMemState _startMemState;
	};
}