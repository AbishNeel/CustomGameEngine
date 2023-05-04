#include "pch.h"
#include "CppUnitTest.h"
#include "Vector.h"
#include "Foo.h"
#include "ToStringSpecializations.h"
#include "DefaultEquality.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std;
using namespace UnitTests;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	std::wstring ToString<Vector<Foo>::Iterator>(const Vector<Foo>::Iterator& t)
	{
		wstring value;
		try
		{
			value = ToString(*t);
		}
		catch (const std::exception&)
		{
			value = L"end()"s;
		}
		return value;
	}

	template<>
	std::wstring ToString<Vector<Foo>::ConstIterator>(const Vector<Foo>::ConstIterator& t)
	{
		wstring value;
		try
		{
			value = ToString(*t);
		}
		catch (const std::exception&)
		{
			value = L"end()"s;
		}
		return value;
	}
}

namespace LibraryDesktopTests
{
	TEST_CLASS(VectorTests)
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

		TEST_METHOD(DefaultConstructor)
		{
			Vector<Foo> vector;
			Assert::AreEqual(size_t(0), vector.Size());
			Assert::AreEqual(size_t(0), vector.Capacity());
			Assert::ExpectException<runtime_error>([&vector]() { auto front = vector.Front(); UNREFERENCED_LOCAL(front); });
			Assert::ExpectException<runtime_error>([&vector]() { auto back = vector.Back(); UNREFERENCED_LOCAL(back); });
		}

		TEST_METHOD(CopySemantics)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			Foo c{ 3 };
			Vector<Foo> vectorA{ a, b, c };
			Vector<Foo> vectorB{ vectorA };
			Vector<Foo> vectorC;
			//Assert::IsTrue(equal(vectorA.begin(), vectorA.end(), vectorB.begin(), vectorB.end()));

			Vector<Foo>::Iterator itA = vectorA.begin();
			Vector<Foo>::Iterator itB = vectorB.begin();

			Assert::AreEqual(*itA++, *itB++);
			Assert::AreEqual(*itA++, *itB++);
			Assert::AreEqual(*itA, *itB);

			vectorC = vectorA;
			itA = vectorA.begin();
			Vector<Foo>::Iterator itC = vectorC.begin();
			Assert::AreEqual(*itA++, *itC++);
			Assert::AreEqual(*itA++, *itC++);
			Assert::AreEqual(*itA, *itC);
		}

		TEST_METHOD(MoveSemantics)
		{
			//Move constructor
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Vector<Foo> vectorA{ a, b, c };
				size_t originalSize = vectorA.Size();
				size_t originalCapacity = vectorA.Capacity();

				Vector<Foo> vectorB{ move(vectorA) };
				Assert::AreEqual(originalSize, vectorB.Size());
				Assert::AreEqual(originalCapacity, vectorB.Capacity());

				//Maybe try std::equal
				Assert::AreEqual(a, vectorB.Front());
				Assert::AreEqual(c, vectorB.Back());
			}

			//Move assignment operator
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Vector<Foo> vectorA{ a, b, c };
				size_t originalSize = vectorA.Size();
				size_t originalCapacity = vectorA.Capacity();

				Vector<Foo> vectorB{ c, a, b }; 
				vectorB = move(vectorA);
				Assert::AreEqual(size_t(0), vectorA.Size());
				Assert::AreEqual(size_t(0), vectorA.Capacity());
				Assert::AreEqual(originalSize, vectorB.Size());
				Assert::AreEqual(originalCapacity, vectorB.Capacity());

				//Maybe try std::equal
				Assert::AreEqual(a, vectorB.Front());
				Assert::AreEqual(c, vectorB.Back());
			}
		}

		TEST_METHOD(Reserve)
		{
			Vector<Foo> vector;
			vector.Reserve(10);
			Assert::AreEqual(size_t(0), vector.Size());
			Assert::AreEqual(size_t(10), vector.Capacity());
			vector.Reserve(9);
			Assert::AreEqual(size_t(10), vector.Capacity());
		}

		TEST_METHOD(PushBack)
		{
			// Passing lvalue argument
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Vector<Foo> vector;
				vector.PushBack(a);
				vector.PushBack(b);
				Assert::AreEqual(size_t(2), vector.Size());
				Assert::AreEqual(a, vector.Front());
				Assert::AreEqual(b, vector.Back());
			}

			//Passing rvalue argument
			{
				Vector<Foo> vector;
				vector.PushBack(Foo{1});
				vector.PushBack(Foo{2});
				Assert::AreEqual(size_t(2), vector.Size());
				Assert::AreEqual(Foo{ 1 }, vector.Front());
				Assert::AreEqual(Foo{ 2 }, vector.Back());
			}
		}

		TEST_METHOD(PopBack)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			Vector<Foo> vector{ a, b };
			vector.PopBack();
			Assert::AreEqual(a, vector.Back());
			vector.PopBack();
			Assert::AreEqual(size_t(0), vector.Size());
			vector.PopBack();
			Assert::AreEqual(size_t(0), vector.Size());
			vector.PushBack(a);
			vector.PushBack(b);
			Assert::AreEqual(a, vector.Front());
			Assert::AreEqual(b, vector.Back());
		}

		TEST_METHOD(RandomAccessGetter)
		{
			//Non-const version
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Vector<Foo> vector{ a, b };
				Assert::AreEqual(a, vector[0]);
				Assert::AreEqual(b, vector[1]);
				Assert::ExpectException<out_of_range>([&vector]() { vector[2]; });
			}

			//Const version
			{
				const Foo a{ 1 };
				const Foo b{ 2 };
				const Vector<Foo> vector{ a, b };
				Assert::AreEqual(a, vector[0]);
				Assert::AreEqual(b, vector[1]);
				Assert::ExpectException<out_of_range>([&vector]() { vector[2]; });
			}
		}

		TEST_METHOD(At)
		{
			//Non-const version
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Vector<Foo> vector{ a, b };
				Assert::AreEqual(a, vector.at(0));
				Assert::AreEqual(b, vector.at(1));
				Assert::ExpectException<out_of_range>([&vector]() { vector.at(2); });
			}

			//Const version
			{
				const Foo a{ 1 };
				const Foo b{ 2 };
				const Vector<Foo> vector{ a, b };
				Assert::AreEqual(a, vector.at(0));
				Assert::AreEqual(b, vector.at(1));
				Assert::ExpectException<out_of_range>([&vector]() { vector.at(2); });
			}
		}

		TEST_METHOD(IsEmpty)
		{
			Vector<Foo> vector;
			Assert::IsTrue(vector.IsEmpty());
			vector.PushBack(Foo{ 1 });
			Assert::IsFalse(vector.IsEmpty());
		}

		TEST_METHOD(Front)
		{
			//Non-const version
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Vector<Foo> vector;
				Assert::ExpectException<runtime_error>([&vector]() { auto front = vector.Front(); UNREFERENCED_LOCAL(front); });
				vector.PushBack(a);
				vector.PushBack(b);
				Assert::AreEqual(a, vector.Front());
			}

			//Const version
			{
				const Foo a{ 1 };
				const Foo b{ 2 };
				const Vector<Foo> vector{a, b};
				Assert::AreEqual(a, vector.Front());

				const Vector<Foo> emptyVector;
				Assert::ExpectException<runtime_error>([&emptyVector]() { auto front = emptyVector.Front(); UNREFERENCED_LOCAL(front); });
			}
		}

		TEST_METHOD(Back)
		{
			//Non-const version
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Vector<Foo> vector;
				Assert::ExpectException<runtime_error>([&vector]() { auto back = vector.Back(); UNREFERENCED_LOCAL(back); });
				vector.PushBack(a);
				vector.PushBack(b);
				Assert::AreEqual(b, vector.Back());
			}

			//Const version
			{
				const Foo a{ 1 };
				const Foo b{ 2 };
				const Vector<Foo> vector{ a, b };
				Assert::AreEqual(b, vector.Back());

				const Vector<Foo> emptyVector;
				Assert::ExpectException<runtime_error>([&emptyVector]() { auto back = emptyVector.Back(); UNREFERENCED_LOCAL(back); });
			}
		}

		TEST_METHOD(Clear)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			Foo c{ 3 };
			Vector<Foo> vector{a, b, c};

			Assert::AreEqual(a, vector.Front());
			Assert::AreEqual(c, vector.Back());
			Assert::AreEqual(size_t(3), vector.Size());
			Assert::IsTrue(vector.Capacity() >= vector.Size());

			vector.Clear();

			size_t originalCapacity = vector.Capacity();
			Assert::ExpectException<runtime_error>([&vector]() { auto front = vector.Front(); UNREFERENCED_LOCAL(front); });
			Assert::ExpectException<runtime_error>([&vector]() { auto back = vector.Back(); UNREFERENCED_LOCAL(back); });
			Assert::AreEqual(size_t(0), vector.Size());
			Assert::AreEqual(originalCapacity, vector.Capacity());
		}

		TEST_METHOD(ShrinkToFit)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			Foo c{ 3 };
			Vector<Foo> vector{a, b, c};
			Assert::AreNotEqual(vector.Size(), vector.Capacity());
			vector.ShrinkToFit();
			Assert::AreEqual(vector.Size(), vector.Capacity());
		}

		TEST_METHOD(Begin)
		{
			//Non-const version
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Vector<Foo> vector{ a, b, c };

				Vector<Foo>::Iterator it = vector.begin();
				Assert::AreEqual(a, *it);
			}

			//Const version
			{
				const Foo a{ 1 };
				const Foo b{ 2 };
				const Foo c{ 3 };
				const Vector<Foo> vector{ a, b, c };

				Vector<Foo>::ConstIterator it = vector.begin();
				Assert::AreEqual(a, *it);
			}

			//CBegin
			{
				const Foo a{ 1 };
				const Foo b{ 2 };
				const Foo c{ 3 };
				Vector<Foo> vector{ a, b, c };

				Vector<Foo>::ConstIterator it = vector.cbegin();
				Assert::AreEqual(a, *it);
			}
		}

		TEST_METHOD(End)
		{
			//Non-const version
			{
				Foo a{ 1 };
				Vector<Foo> vector{ a };

				Vector<Foo>::Iterator it = vector.begin();
				Assert::AreEqual(a, *it);
				Assert::AreEqual(++it, vector.end());
				Assert::ExpectException<runtime_error>([&it]() { *it; });
			}

			//Non-const version
			{
				const Foo a{ 1 };
				const Vector<Foo> vector{ a };

				Vector<Foo>::ConstIterator it = vector.begin();
				Assert::AreEqual(a, *it);
				Assert::AreEqual(++it, vector.end());
				Assert::ExpectException<runtime_error>([&it]() { *it; });
			}

			//CEnd
			{
				const Foo a{ 1 };
				Vector<Foo> vector{ a };

				Vector<Foo>::ConstIterator it = vector.cbegin();
				Assert::AreEqual(a, *it);
				Assert::AreEqual(++it, vector.cend());
				Assert::ExpectException<runtime_error>([&it]() { *it; });
			}
		}


		TEST_METHOD(ConstIteratorTypeCastConstructor)
		{
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			Vector<Foo> vector{ a, b, c };

			Vector<Foo>::Iterator it = vector.begin();
			Vector<Foo>::ConstIterator constIt{it};
			Assert::AreEqual(*it++, *constIt++);
			Assert::AreEqual(*it++, *constIt++);
			Assert::AreEqual(*it++, *constIt++);
		}

		TEST_METHOD(IteratorEqualityOperators)
		{
			//Iterator
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Vector<Foo> vector{ a, b, c };

				Vector<Foo>::Iterator lhs = vector.begin();
				Vector<Foo>::Iterator rhs = vector.begin();
				Vector<Foo>::Iterator defaultIt;

				Assert::AreEqual(lhs, rhs);
				Assert::AreNotEqual(defaultIt, lhs);
				++rhs;
				Assert::AreNotEqual(lhs, rhs);
				Assert::AreNotEqual(defaultIt, lhs);
			}

			//ConstIterator
			{
				const Foo a{ 1 };
				const Foo b{ 2 };
				const Foo c{ 3 };
				Vector<Foo> vector{ a, b, c };

				Vector<Foo>::ConstIterator lhs = vector.cbegin();
				Vector<Foo>::ConstIterator rhs = vector.cbegin();
				Vector<Foo>::ConstIterator defaultIt;

				Assert::AreEqual(lhs, rhs);
				Assert::AreNotEqual(defaultIt, lhs);
				++rhs;
				Assert::AreNotEqual(lhs, rhs);
				Assert::AreNotEqual(defaultIt, lhs);
			}
		}

		TEST_METHOD(IteratorDereferenceOperator)
		{
			//Iterator
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };

				Vector<Foo> vector{ a, b, c };

				Vector<Foo>::Iterator it = vector.begin();
				Assert::AreEqual(a, *it);

				Vector<Foo>::Iterator defaultIt;
				Assert::ExpectException<runtime_error>([&defaultIt]() {*defaultIt; });
			}

			//ConstIterator
			{
				const Foo a{ 1 };
				const Foo b{ 2 };
				const Foo c{ 3 };

				Vector<Foo> vector{ a, b, c };

				Vector<Foo>::ConstIterator it = vector.cbegin();
				Assert::AreEqual(a, *it);

				Vector<Foo>::Iterator defaultIt;
				Assert::ExpectException<runtime_error>([&defaultIt]() {*defaultIt; });
			}
		}

		TEST_METHOD(IteratorIncrementOperators)
		{
			//Iterator
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Vector<Foo> vector{ a, b, c };

				Vector<Foo>::Iterator it = ++vector.begin();
				Assert::AreEqual(b, *it++);
				Assert::AreEqual(c, *it++);

				//Get to the end of allocated memory for the vector
				for (size_t i = 0; i < (vector.Capacity() - vector.Size()); ++i)
					++it;
				Assert::ExpectException<runtime_error>([&it]() {++it; });

				Vector<Foo>::Iterator defaultIt;
				Assert::ExpectException<runtime_error>([&defaultIt]() {++defaultIt; });
				Assert::ExpectException<runtime_error>([&defaultIt]() {defaultIt++; });
			}

			//ConstIterator
			{
				const Foo a{ 1 };
				const Foo b{ 2 };
				const Foo c{ 3 };
				Vector<Foo> vector{ a, b, c };

				Vector<Foo>::ConstIterator it = ++vector.cbegin();
				Assert::AreEqual(b, *it++);
				Assert::AreEqual(c, *it++);

				//Get to the end of allocated memory for the vector
				for (size_t i = 0; i < (vector.Capacity() - vector.Size()); ++i)
					++it;
				Assert::ExpectException<runtime_error>([&it]() {++it; });

				Vector<Foo>::ConstIterator defaultIt;
				Assert::ExpectException<runtime_error>([&defaultIt]() {++defaultIt; });
				Assert::ExpectException<runtime_error>([&defaultIt]() {defaultIt++; });
			}
		}

		TEST_METHOD(ConstIteratorInequalityOperators)
		{
			const Foo a{ 1 };
			const Foo b{ 2 };
			const Foo c{ 3 };
			const Vector<Foo> vector{ a, b, c };

			Assert::IsFalse(vector.begin() > vector.end());
			Assert::IsFalse(vector.begin() > vector.Find(a));
			Assert::IsFalse(vector.begin() < vector.Find(a));
			Assert::IsTrue(vector.begin() < vector.end());
		}

		TEST_METHOD(Find)
		{
			//Non-const version
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Vector<Foo> vector{ a, b };
				Assert::AreEqual(vector.begin(), vector.Find(a));
				Assert::AreEqual(++vector.begin(), vector.Find(b));
			}

			//Const version
			{
				const Foo a{ 1 };
				const Foo b{ 2 };
				const Vector<Foo> vector{ a, b };
				Assert::AreEqual(vector.begin(), vector.Find(a));
				Assert::AreEqual(++vector.begin(), vector.Find(b));
			}
		}

		TEST_METHOD(Remove)
		{
			//Deleting element by value
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Foo d{ 4 };
				Vector<Foo> vector{ a, b, c, d };
				size_t originalCapacity = vector.Capacity();

				Assert::IsTrue(vector.Remove(b));
				Assert::AreEqual(size_t(3), vector.Size());
				Assert::AreEqual(originalCapacity, vector.Capacity());

				Assert::IsTrue(vector.Remove(d));
				Assert::AreEqual(vector.Find(c), ++vector.begin());
				Assert::IsFalse(vector.Remove(b));
				Assert::AreEqual(size_t(2), vector.Size());
				Assert::AreEqual(originalCapacity, vector.Capacity());
			}

			// Deleting all elements in a given range
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Foo d{ 4 };
				Vector<Foo> vector{ a, b, c, d };
				size_t originalCapacity = vector.Capacity();
				size_t originalSize = vector.Size();

				Assert::IsFalse(vector.Remove(Vector<Foo>::ConstIterator{}, vector.cend()));
				Assert::IsFalse(vector.Remove(vector.cend(), vector.cend()));
				Assert::IsFalse(vector.Remove(vector.cend(), vector.cbegin()));
				Assert::AreEqual(originalSize, vector.Size());
				Assert::AreEqual(originalCapacity, vector.Capacity());

				Assert::IsTrue(vector.Remove(Vector<Foo>::ConstIterator{ vector.Find(b) }, Vector<Foo>::ConstIterator{ vector.Find(d) }));
				Assert::AreEqual(a, vector.Front());
				Assert::AreEqual(d, vector.Back());
				Assert::IsTrue(vector.Remove(vector.cbegin(), vector.cend()));
				Assert::IsTrue(vector.IsEmpty());
				Assert::AreEqual(originalCapacity, vector.Capacity());
			}
		}

		TEST_METHOD(EmplaceBack)
		{
			Foo a{ 1 };
			Vector<Foo> vector;
			vector.EmplaceBack(0);
			vector.EmplaceBack(Foo{ 2 });
			Assert::AreEqual(Foo{ 2 }, vector.Back());
			Assert::AreEqual(Foo{ 0 }, vector.Front());
			vector.EmplaceBack(a);
			Assert::AreEqual(Foo{1}, vector.Back());
		}

		private:
			inline static _CrtMemState _startMemState;
	};
}