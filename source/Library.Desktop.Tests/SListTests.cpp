#include "pch.h"
#include "CppUnitTest.h"
#include "SList.h"
#include "ToStringSpecializations.h"
#include "Foo.h"
#include "DefaultEquality.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std;
using namespace UnitTests;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	std::wstring ToString<SList<Foo>::Iterator>(const SList<Foo>::Iterator& t)
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
	std::wstring ToString<SList<Foo>::ConstIterator>(const SList<Foo>::ConstIterator& t)
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
	TEST_CLASS(SListTests)
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
		TEST_METHOD(Front)
		{
			SList<Foo> list;
			list.PushBack(Foo{ 2 });
			list.PushBack(Foo{ 5 });
			Assert::AreEqual(Foo{ 2 }, list.Front());
		}

		TEST_METHOD(Back)
		{
			SList<Foo> list;
			list.PushBack(Foo{ 2 });
			list.PushBack(Foo{ 5 });
			Assert::AreEqual(Foo{ 5 }, list.Back());
		}

		TEST_METHOD(PushBack)
		{
			SList<Foo> list;
			list.PushBack(Foo{ 3 });
			list.PushBack(Foo{ 4 });
			Assert::AreEqual(Foo{ 3 }, list.Front());
			Assert::AreEqual(Foo{ 4 }, list.Back());
		}

		TEST_METHOD(PushFront)
		{
			SList<Foo> list;
			list.PushFront(Foo{ 1 });
			list.PushFront(Foo{ 2 });
			Assert::AreEqual(Foo{ 1 }, list.Back());
			Assert::AreEqual(Foo{ 2 }, list.Front());
		}

		TEST_METHOD(PopFront)
		{
			SList<Foo> list;
			Assert::ExpectException<std::runtime_error>([&list]() { list.PopFront(); });

			list.PushBack(Foo{ 1 });
			list.PushBack(Foo{ 2 });
			Assert::AreEqual(size_t(2), list.Size());
			Assert::AreEqual(Foo{ 1 }, list.Front());
			
			list.PopFront();
			Assert::AreEqual(size_t(1), list.Size());
			Assert::AreEqual(Foo{ 2 }, list.Front());
			
			list.PopFront();
			Assert::AreEqual(size_t(0), list.Size());
			Assert::ExpectException<runtime_error>([&list]() { auto& front = list.Front(); UNREFERENCED_LOCAL(front); });
			Assert::ExpectException<runtime_error>([&list]() { auto& back = list.Back(); UNREFERENCED_LOCAL(back); });
			Assert::ExpectException<std::runtime_error>([&list]() { list.PopFront(); });
		}

		TEST_METHOD(PopBack)
		{
			SList<Foo> list;
			Assert::ExpectException<std::runtime_error>([&list]() { list.PopBack();});

			list.PushBack(Foo{ 1 });
			list.PushBack(Foo{ 2 });
			Assert::AreEqual(size_t(2), list.Size());
			Assert::AreEqual(Foo{ 2 }, list.Back());
			
			list.PopBack();
			Assert::AreEqual(size_t(1), list.Size());
			Assert::AreEqual(Foo{ 1 }, list.Back());

			list.PopBack();
			Assert::AreEqual(size_t(0), list.Size());
			Assert::ExpectException<runtime_error>([&list]() { auto& front = list.Front(); UNREFERENCED_LOCAL(front); });
			Assert::ExpectException<runtime_error>([&list]() { auto& back = list.Back(); UNREFERENCED_LOCAL(back); });
			Assert::ExpectException<std::runtime_error>([&list]() { list.PopBack(); });
		}

		TEST_METHOD(IsEmpty)
		{
			SList<Foo> list;
			Assert::IsTrue(list.IsEmpty());
			list.PushBack(Foo{ 3 });
			Assert::IsFalse(list.IsEmpty());
		}

		TEST_METHOD(Size)
		{
			SList<Foo> list;
			list.PushBack(Foo{ 2 });
			list.PushBack(Foo{ 5 });
			Assert::AreEqual(size_t(2), list.Size());
		}

		TEST_METHOD(Constructor)
		{
			SList<Foo> list;

			Assert::AreEqual(size_t(0), list.Size());
			Assert::ExpectException<runtime_error>([&list]() { auto& front = list.Front(); UNREFERENCED_LOCAL(front); });
			Assert::ExpectException<runtime_error>([&list]() { auto& back = list.Back(); UNREFERENCED_LOCAL(back); });
		}

		TEST_METHOD(CopySemantics)
		{
			SList<Foo> rhs;
			rhs.PushBack(Foo{ 1 });
			rhs.PushBack(Foo{ 2 });
			rhs.PushBack(Foo{ 3 });

			SList<Foo> lhs{ rhs };

			Assert::AreEqual(rhs.Size(), lhs.Size());
			Assert::AreEqual(rhs.Front(), lhs.Front());
			lhs.PopFront();
			rhs.PopFront();
			Assert::AreEqual(rhs.Front(), lhs.Front());
			lhs.PopFront();
			rhs.PopFront();
			Assert::AreEqual(rhs.Front(), lhs.Front());
			lhs.PopFront();
			rhs.PopFront();

			lhs.Clear();
			rhs.PushBack(Foo{ 1 });
			rhs.PushBack(Foo{ 2 });
			rhs.PushBack(Foo{ 3 });

			lhs = rhs;

			Assert::AreEqual(rhs.Size(), lhs.Size());
			Assert::AreEqual(rhs.Front(), lhs.Front());
			lhs.PopFront();
			rhs.PopFront();
			Assert::AreEqual(rhs.Front(), lhs.Front());
			lhs.PopFront();
			rhs.PopFront();
			Assert::AreEqual(rhs.Front(), lhs.Front());
			lhs.PopFront();
			rhs.PopFront();
		}

		TEST_METHOD(Clear)
		{
			SList<Foo> list;
			list.PushBack(Foo{ 2 });
			list.PushBack(Foo{ 5 });
			list.PushBack(Foo{ 8 });
			list.Clear();
			Assert::AreEqual(size_t(0), list.Size());
			Assert::ExpectException<runtime_error>([&list]() { auto& front = list.Front(); UNREFERENCED_LOCAL(front); });
			Assert::ExpectException<runtime_error>([&list]() { auto& back = list.Back(); UNREFERENCED_LOCAL(back); });
		}

		TEST_METHOD(Const)
		{
			SList<Foo> list;

			list.PushBack(Foo{ 2 });
			list.PushBack(Foo{ 5 });
			list.PushBack(Foo{ 6 });

			const SList<Foo> constList = list;

			Assert::AreEqual(Foo{ 2 }, constList.Front());
			Assert::AreEqual(Foo{ 6 }, constList.Back());
			Assert::AreEqual(size_t(3), list.Size());
			Assert::IsFalse(list.IsEmpty());

			const SList<Foo> emptyConstList;
			Assert::ExpectException<runtime_error>([&emptyConstList]() { auto& front = emptyConstList.Front(); UNREFERENCED_LOCAL(front); });
			Assert::ExpectException<runtime_error>([&emptyConstList]() { auto& back = emptyConstList.Back(); UNREFERENCED_LOCAL(back); });
		}

		TEST_METHOD(IteratorConstructor)
		{
			SList<Foo>::Iterator defaultIt;
			Assert::ExpectException<runtime_error>([&defaultIt]() { *defaultIt; });
			Assert::ExpectException<runtime_error>([&defaultIt]() { ++defaultIt; });

			Foo a{ 1 };
			Foo b{ 2 };
			SList<Foo> list{ a, b };
			SList<Foo>::Iterator it = list.begin();
			Assert::AreEqual(list.begin(), it++);
			Assert::AreEqual(list.Find(b), it++);
		}

		TEST_METHOD(ConstIteratorConstructor)
		{
			SList<Foo>::ConstIterator defaultIt;
			Assert::ExpectException<runtime_error>([&defaultIt]() { *defaultIt; });
			Assert::ExpectException<runtime_error>([&defaultIt]() { ++defaultIt; });

			Foo a{ 1 };
			Foo b{ 2 };
			SList<Foo> list{ a, b };
			SList<Foo>::ConstIterator it = list.cbegin();
			Assert::AreEqual(list.cbegin(), it++);
			Assert::AreEqual(SList<Foo>::ConstIterator{ list.Find(b) }, it++);
		}

		TEST_METHOD(TypecastConstructor)
		{
			Foo a{ 1 };
			SList<Foo> list{ a };
			SList<Foo>::ConstIterator it = SList<Foo>::ConstIterator{ list.begin() };
			Assert::AreEqual(list.cbegin(), it);
		}

		TEST_METHOD(IteratorEquals)
		{
			Foo a{ 1 };
			Foo b{ 2 };

			SList<Foo> list{ a, b};
			SList<Foo>::Iterator it = list.begin();
			Assert::AreNotEqual(list.end(), it);
			++it;
			++it;
			Assert::AreEqual(list.end(), it);
			Assert::IsTrue(it != list.begin());
		}

		TEST_METHOD(IteratorIncrement)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			Foo c{ 3 };
			SList<Foo> list{ a, b, c };
			SList<Foo>::Iterator it = list.begin();
			Assert::AreEqual(a, *it);
			++it;
			Assert::AreEqual(b, *it);
			it++;
			Assert::AreEqual(c, *it);

			it = list.end();

			Assert::ExpectException<out_of_range>([&it]() { ++it; });
			Assert::ExpectException<out_of_range>([&it]() { it++; });

			SList<Foo>::Iterator defaultIterator;
			Assert::ExpectException<runtime_error>([&defaultIterator]() { ++defaultIterator; });
			Assert::ExpectException<runtime_error>([&defaultIterator]() { defaultIterator++; });
		}

		TEST_METHOD(IteratorDereference)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			Foo c{ 3 };

			SList<Foo> list;
			Assert::ExpectException<std::runtime_error>([&list]() { *list.begin(); });
			Assert::ExpectException<std::runtime_error>([&list]() { *list.end(); });

			list.PushBack(a);
			list.PushBack(b);
			list.PushBack(b);
			Assert::AreEqual(a, *list.begin());
			Assert::ExpectException<std::runtime_error>([&list]() { *list.end(); });

			const SList<Foo> constList{list};
			Assert::AreEqual(a, *constList.begin());
			
			const SList<Foo> emptyConstList;
			Assert::ExpectException<std::runtime_error>([&emptyConstList]() { *emptyConstList.begin(); });
			Assert::ExpectException<std::runtime_error>([&emptyConstList]() { *emptyConstList.end(); });
		}

		TEST_METHOD(ConstIteratorEquals)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			Foo c{ 3 };

			SList<Foo> list{ a, b, c };
			SList<Foo>::ConstIterator it = list.cbegin();
			Assert::AreNotEqual(list.cend(), it);
			++it;
			++it;
			++it;
			Assert::AreEqual(list.cend(), it);
			Assert::IsTrue(it != list.cbegin());
		}

		TEST_METHOD(ConstIteratorIncrement)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			Foo c{ 3 };

			SList<Foo> list{ a, b, c };
			const SList<Foo> constList{ list };
			SList<Foo>::ConstIterator it = constList.begin();
			++it;
			Assert::AreEqual(b, *it);
			it++;
			Assert::AreEqual(c, *it);

			it = constList.end();

			Assert::ExpectException<out_of_range>([&it]() { ++it; });
			Assert::ExpectException<out_of_range>([&it]() { it++; });

			SList<Foo>::ConstIterator defaultIterator;
			Assert::ExpectException<runtime_error>([&defaultIterator]() { ++defaultIterator; });
			Assert::ExpectException<runtime_error>([&defaultIterator]() { defaultIterator++; });
			
		}

		TEST_METHOD(ConstIteratorDereference)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			Foo c{ 3 };

			SList<Foo> list;
			Assert::ExpectException<std::runtime_error>([&list]() { *list.cbegin(); });
			Assert::ExpectException<std::runtime_error>([&list]() { *list.cend(); });

			list.PushBack(a);
			list.PushBack(b);
			list.PushBack(b);
			Assert::AreEqual(a, *list.cbegin());
			Assert::ExpectException<std::runtime_error>([&list]() { *list.cend(); });
		}

		TEST_METHOD(Begin)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			SList<Foo> list;
			Assert::ExpectException<std::runtime_error>([&list]() { *list.begin(); });
			list.PushBack(a);
			list.PushBack(b);
			Assert::AreEqual(a, *list.begin());
			list.PopFront();
			Assert::AreEqual(b, *list.begin());

			const SList<Foo> constList{ a, b };
			Assert::AreEqual(a, *constList.begin());
		}

		TEST_METHOD(CBegin)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			SList<Foo> list;
			Assert::ExpectException<std::runtime_error>([&list]() { *list.cbegin(); });
			list.PushBack(a);
			list.PushBack(b);
			Assert::AreEqual(a, *list.cbegin());
			list.PopFront();
			Assert::AreEqual(b, *list.cbegin());

			const SList<Foo> constList{ a, b };
			Assert::AreEqual(a, *constList.cbegin());
		}

		TEST_METHOD(End)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			SList<Foo> list;
			Assert::ExpectException<std::runtime_error>([&list]() { *list.end(); });
			const SList<Foo> constList{ list };
			Assert::ExpectException<std::runtime_error>([&constList]() { *constList.end(); });
		}

		TEST_METHOD(CEnd)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			SList<Foo> list;
			Assert::ExpectException<std::runtime_error>([&list]() { *list.cend(); });
			const SList<Foo> constList{ list };
			Assert::ExpectException<std::runtime_error>([&constList]() { *constList.cend(); });
		}

		TEST_METHOD(InsertAfter)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			Foo c{ 3 };

			//InsertAfter that accepts and returns an Iterator
			{
				SList<Foo> list;

				SList<Foo>::Iterator it;
				Assert::ExpectException<runtime_error>([&list, &it, &a]() { list.InsertAfter(it, a); });
				it = list.InsertAfter(list.end(), a);
				SList<Foo>::Iterator expectedIt = list.begin();
				Assert::AreEqual(expectedIt, it);
				Assert::AreEqual(size_t(1), list.Size());

				it = list.InsertAfter(expectedIt, b);
				++expectedIt;
				Assert::AreEqual(expectedIt, it);
				Assert::AreEqual(size_t(2), list.Size());

				it = list.InsertAfter(expectedIt, c);
				++expectedIt;
				Assert::AreEqual(expectedIt, it);
				Assert::AreEqual(size_t(3), list.Size());

				Assert::ExpectException<runtime_error>([&list, &a]() { list.InsertAfter(list.end(), a); });
			}

			//InsertAfter that accepts and returns a ConstIterator
			{
				SList<Foo> list;

				SList<Foo>::ConstIterator it;
				Assert::ExpectException<runtime_error>([&list, &it, &a]() { list.InsertAfter(it, a); });
				it = list.InsertAfter(list.cend(), a);
				SList<Foo>::ConstIterator expectedIt = list.cbegin();
				Assert::AreEqual(expectedIt, it);
				Assert::AreEqual(size_t(1), list.Size());

				it = list.InsertAfter(expectedIt, b);
				++expectedIt;
				Assert::AreEqual(expectedIt, it);
				Assert::AreEqual(size_t(2), list.Size());

				it = list.InsertAfter(expectedIt, c);
				++expectedIt;
				Assert::AreEqual(expectedIt, it);
				Assert::AreEqual(size_t(3), list.Size());

				Assert::ExpectException<runtime_error>([&list, &a]() { list.InsertAfter(list.cend(), a); });
			}
		}

		TEST_METHOD(Find)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			Foo c{ 3 };
			Foo d{ 4 };
			Foo e{ 5 };
			Foo f{ 6 };

			//Non-const version
			{
				SList<Foo> list{ a, b, c, d, e };
				SList<Foo>::Iterator it = list.begin();

				Assert::AreEqual(it++, list.Find(a));
				Assert::AreEqual(a, *list.Find(a));
				Assert::AreEqual(it++, list.Find(b));
				Assert::AreEqual(b, *list.Find(b));
				Assert::AreEqual(it++, list.Find(c));
				Assert::AreEqual(c, *list.Find(c));
				Assert::AreEqual(it++, list.Find(d));
				Assert::AreEqual(d, *list.Find(d));
				Assert::AreEqual(it++, list.Find(e));
				Assert::AreEqual(e, *list.Find(e));

				Assert::AreEqual(list.end(), list.Find(f));
				Assert::ExpectException<runtime_error>([&list, &f]() { *list.Find(f); });
			}

			//Const version
			{
				const SList<Foo> list{ a, b, c, d, e };
				SList<Foo>::ConstIterator it = list.begin();

				Assert::AreEqual(it++, list.Find(a));
				Assert::AreEqual(a, *list.Find(a));
				Assert::AreEqual(it++, list.Find(b));
				Assert::AreEqual(b, *list.Find(b));
				Assert::AreEqual(it++, list.Find(c));
				Assert::AreEqual(c, *list.Find(c));
				Assert::AreEqual(it++, list.Find(d));
				Assert::AreEqual(d, *list.Find(d));
				Assert::AreEqual(it++, list.Find(e));
				Assert::AreEqual(e, *list.Find(e));

				Assert::AreEqual(list.end(), list.Find(f));
				Assert::ExpectException<runtime_error>([&list, &f]() { *list.Find(f); });
			}
		}

		TEST_METHOD(Remove)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			Foo c{ 3 };
			Foo d{ 4 };
			Foo e{ 5 };
			Foo f{ 6 };
			SList<Foo> list{ a, b, c, d, e };
			Assert::IsFalse(list.Remove(f));
			Assert::AreEqual(size_t(5), list.Size());
			Assert::IsTrue(list.Remove(a));
			Assert::AreEqual(size_t(4), list.Size());
			Assert::AreEqual(list.Find(b), list.begin());
			Assert::IsTrue(list.Remove(e));
			Assert::AreEqual(size_t(3), list.Size());
		}

		private:
			inline static _CrtMemState _startMemState;
	};
}
