#include "pch.h"
#include "CppUnitTest.h"
#include "Foo.h"
#include "ToStringSpecializations.h"
#include "HashMap.h"
#include "DefaultHash.h"
#include "DefaultEquality.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std;
using namespace UnitTests;

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	std::wstring ToString<HashMap<Foo, Foo>::Iterator>(const HashMap<Foo, Foo>::Iterator& t)
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
	std::wstring ToString<HashMap<Foo, Foo>::ConstIterator>(const HashMap<Foo, Foo>::ConstIterator& t)
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
	TEST_CLASS(HashMapTests)
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
			//Default constructor
			{
				HashMap<Foo, Foo> map;
				Assert::AreEqual(size_t(11), map.Capacity());
				Assert::AreEqual(size_t(0), map.Size());
				Assert::AreEqual(size_t(0), map.LoadFactor());
			}

			//Initializer list constructor
			{
				const Foo a{ 1 }; 
				const Foo b{ 2 }; 
				Foo x{ 10 };
				Foo y{ 20 };
				pair p1 = make_pair(a, x);
				pair p2 = make_pair(b, y);
				HashMap<const Foo, Foo> map{ {p1, p2}, 2, FooHash{} };
				Assert::AreEqual(size_t(2), map.Size());
			}
		}

		TEST_METHOD(CopySemantics)
		{
			//Copy constructor
			{
				const Foo a{ 1 };
				const Foo b{ 2 };
				Foo x{ 10 };
				Foo y{ 20 };
				pair p1 = make_pair(a, x);
				pair p2 = make_pair(b, y);
				HashMap<const Foo, Foo> map{ {p1, p2}, 2, FooHash{} };

				HashMap<const Foo, Foo> newMap{ map };
				Assert::IsTrue(std::equal(map.begin(), map.end(), newMap.begin(), newMap.end()));
			}

			//Copy assignment operator
			{
				const Foo a{ 1 };
				const Foo b{ 2 };
				Foo x{ 10 };
				Foo y{ 20 };
				pair p1 = make_pair(a, x);
				pair p2 = make_pair(b, y);
				HashMap<const Foo, Foo> map{ {p1, p2}, 2, FooHash{} };

				HashMap<const Foo, Foo> newMap;
				newMap = map;
				Assert::IsTrue(std::equal(map.begin(), map.end(), newMap.begin(), newMap.end()));
			}
		}

		TEST_METHOD(MoveSemantics)
		{
			//Move constructor
			{
				const Foo a{ 1 };
				const Foo b{ 2 };
				Foo x{ 10 };
				Foo y{ 20 };
				pair p1 = make_pair(a, x);
				pair p2 = make_pair(b, y);
				HashMap<const Foo, Foo> map{ {p1, p2}, 2, FooHash{} };
				HashMap<const Foo, Foo> refMap{ map };

				HashMap<const Foo, Foo> newMap{ std::move(map) };
				Assert::IsTrue(std::equal(refMap.begin(), refMap.end(), newMap.begin(), newMap.end()));
			}

			//Move assignment operator
			{
				const Foo a{ 1 };
				const Foo b{ 2 };
				Foo x{ 10 };
				Foo y{ 20 };
				pair p1 = make_pair(a, x);
				pair p2 = make_pair(b, y);
				HashMap<const Foo, Foo> map{ {p1, p2}, 2, FooHash{} };
				HashMap<const Foo, Foo> refMap{ map };

				HashMap<const Foo, Foo> newMap;
				newMap = std::move(map);
				Assert::IsTrue(std::equal(refMap.begin(), refMap.end(), newMap.begin(), newMap.end()));
			}
		}

		TEST_METHOD(Insert)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			Foo x { 10 };
			Foo y{ 20 };
			HashMap<Foo, Foo> map{ 10, FooHash{} };

			pair<HashMap<Foo, Foo>::Iterator, bool> pair = map.Insert(make_pair(a, x));
			
			Assert::IsTrue(pair.second);
			HashMap<Foo, Foo>::Iterator it = pair.first;
			Assert::AreEqual(x, (*it).second);

			pair = map.Insert(make_pair(a, y));
			Assert::IsFalse(pair.second);

			pair = map.Insert(make_pair(b, y));
			it = pair.first;
			Assert::IsTrue(pair.second);
			Assert::AreEqual(y, (*it).second);
		}

		TEST_METHOD(Find)
		{
			//Non-const version
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo x{ 10 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };

				HashMap<Foo, Foo>::Iterator it = map.Insert(make_pair(a, x)).first;
				Assert::AreEqual((*it).first, (*map.Find(a)).first);
				Assert::AreEqual((*it).second, (*map.Find(a)).second);

				it = map.Find(b);
				Assert::AreEqual(it, map.end());
			}

			//Const version
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo x{ 10 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };
				map.Insert(make_pair(a, x)).first;
				const HashMap<Foo, Foo> constMap{ map };
				HashMap<Foo, Foo>::ConstIterator it = constMap.Find(a);

				Assert::AreEqual(a, (*it).first);
				Assert::AreEqual(x, (*it).second);

				it = constMap.Find(b);
				Assert::AreEqual(it, constMap.end());
			}
		}

		TEST_METHOD(At)
		{
			//Non-const version
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Foo x{ 10 };
				Foo y{ 20 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };

				map.Insert(make_pair(a, x));
				map.Insert(make_pair(b, y));
				Assert::AreEqual(x, map.At(a));
				Assert::AreEqual(y, map.At(b));

				Assert::ExpectException<runtime_error>([&map, &c]() { map.At(c); });
			}

			//Const version
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Foo x{ 10 };
				Foo y{ 20 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };
				map.Insert(make_pair(a, x));
				map.Insert(make_pair(b, y));
				const HashMap<Foo, Foo> constMap{ map };
				
				Assert::AreEqual(x, constMap.At(a));
				Assert::AreEqual(y, constMap.At(b));

				Assert::ExpectException<runtime_error>([&constMap, &c]() { constMap.At(c); });
			}
		}

		TEST_METHOD(ContainsKey)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			Foo x{ 10 };
			HashMap<Foo, Foo> map{ 10, FooHash{} };

			map.Insert(make_pair(a, x));
			Assert::IsFalse(map.ContainsKey(b));
			Assert::IsTrue(map.ContainsKey(a));
		}

		TEST_METHOD(BracketOperator)
		{
			Foo a{ 1 };
			Foo b{ 2 };

			Foo x{ 10 };
			HashMap<Foo, Foo> map{ 10, FooHash{} };

			HashMap<Foo, Foo>::Iterator it = map.Insert(make_pair(a, x)).first;

			Assert::AreEqual((*it).second, map[a]);
			Assert::AreEqual(Foo{}, map[b]);
		}

		TEST_METHOD(Remove)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			Foo c{ 3 };
			Foo x{ 10 };
			Foo y{ 20 };
			HashMap<Foo, Foo> map{ 10, FooHash{} };

			map.Insert(make_pair(a, x));
			map.Insert(make_pair(b, y));

			Assert::AreEqual(size_t(2), map.Size());
			Assert::IsFalse(map.Remove(c));
			Assert::IsTrue(map.ContainsKey(b));
			Assert::IsTrue(map.Remove(b));
			Assert::IsFalse(map.ContainsKey(b));
			Assert::IsFalse(map.Remove(b));
			Assert::IsTrue(map.ContainsKey(a));
			Assert::AreEqual(size_t(1), map.Size());
		}

		TEST_METHOD(Resize)
		{
			Foo a{ 1 };
			Foo b{ 2 };
			Foo x{ 10 };
			Foo y{ 20 };
			HashMap<Foo, Foo> map{ 10, FooHash{} };

			map.Insert(make_pair(a, x));
			map.Insert(make_pair(b, y));
			size_t originalCapacity = map.Capacity();
			size_t originalSize = map.Size();
			size_t originalLoadFactor = map.LoadFactor();

			map.Resize(map.Capacity());
			Assert::AreEqual(originalSize, map.Size());
			Assert::AreEqual(originalCapacity, map.Capacity());
			Assert::IsTrue(map.LoadFactor() <= originalLoadFactor);

			map.Resize(map.Capacity() + 10);
			Assert::AreEqual(originalSize, map.Size());
			Assert::IsTrue(map.LoadFactor() <= originalLoadFactor);
			Assert::IsTrue(map.Capacity() > originalCapacity);
		}

		TEST_METHOD(Clear)
		{
			const Foo a{ 1 };
			const Foo b{ 2 };
			Foo x{ 10 };
			Foo y{ 20 };
			pair p1 = make_pair(a, x);
			pair p2 = make_pair(b, y);

			HashMap<const Foo, Foo> map{ {p1, p2}, 2, FooHash{} };
			Assert::AreEqual(size_t(2), map.Size());
			size_t originalCapacity = map.Capacity();

			map.Clear();
			Assert::AreEqual(size_t(0), map.Size());
			Assert::AreEqual(originalCapacity, map.Capacity());
			Assert::AreEqual(size_t(0), map.LoadFactor());

		}

		TEST_METHOD(Begin)
		{
			//Non-const version
			{
				Foo a{ 1 };
				Foo x{ 10 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };
				Assert::AreEqual(map.begin(), map.end());
				map.Insert(make_pair(a, x));

				Assert::AreEqual(map.Find(a), map.begin());
			}

			//Const version
			{
				Foo a{ 1 };
				Foo x{ 10 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };
				map.Insert(make_pair(a, x));
				const HashMap<Foo, Foo> constMap{ map };

				Assert::AreEqual(constMap.Find(a), constMap.begin());

				const HashMap<Foo, Foo> emptyMap{10};
				Assert::AreEqual(emptyMap.begin(), emptyMap.end());
			}

			//CBegin
			{
				Foo a{ 1 };
				Foo x{ 10 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };
				Assert::AreEqual(map.cbegin(), map.cend());
				map.Insert(make_pair(a, x));

				Assert::AreEqual(x, (*map.cbegin()).second);
			}
		}

		TEST_METHOD(End)
		{
			//Non-const version
			{
				Foo a{ 1 };
				Foo x{ 10 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };
				map.Insert(make_pair(a, x));
				HashMap<Foo, Foo>::Iterator it = map.begin();
				++it;

				Assert::AreEqual(it, map.end());
				Assert::ExpectException<runtime_error>([&it]() { *it; });
			}

			//Const version
			{
				Foo a{ 1 };
				Foo x{ 10 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };
				map.Insert(make_pair(a, x));
				const HashMap<Foo, Foo> constMap{ map };
				HashMap<Foo, Foo>::ConstIterator it = constMap.begin();
				++it;

				Assert::AreEqual(it, constMap.end());
				Assert::ExpectException<runtime_error>([&it]() { *it; });
			}

			//CEnd
			{
				Foo a{ 1 };
				Foo x{ 10 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };
				map.Insert(make_pair(a, x));
				HashMap<Foo, Foo>::ConstIterator it = map.cbegin();
				++it;

				Assert::AreEqual(it, map.cend());
				Assert::ExpectException<runtime_error>([&it]() { *it; });
			}
		}

		TEST_METHOD(ConstIteratorTypecastConstructor)
		{
			Foo a{ 1 };
			Foo x{ 10 };
			HashMap<Foo, Foo> map{ 10, FooHash{} };
			HashMap<Foo, Foo>::Iterator it = map.Insert(make_pair(a, x)).first;

			Assert::AreEqual(it, map.begin());
			HashMap<Foo, Foo>::ConstIterator cit{ it };
			Assert::AreEqual(cit, map.cbegin());
		}

		TEST_METHOD(IteratorIncrementOperators)
		{
			//Prefix version
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo x{ 10 };
				Foo y{ 20 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };

				map.Insert(make_pair(a, x));
				map.Insert(make_pair(b, y));

				HashMap<Foo, Foo>::Iterator it = map.begin();
				Assert::AreEqual(a, (*it).first);
				Assert::AreEqual(x, (*it).second);
				++it;
				Assert::AreEqual(b, (*it).first);
				Assert::AreEqual(y, (*it).second);
			}

			//Postfix version
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo x{ 10 };
				Foo y{ 20 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };

				map.Insert(make_pair(a, x));
				map.Insert(make_pair(b, y));

				HashMap<Foo, Foo>::Iterator it = map.begin();
				Assert::AreEqual(a, (*it).first);
				Assert::AreEqual(x, (*it).second);
				it++;
				Assert::AreEqual(b, (*it).first);
				Assert::AreEqual(y, (*it).second);
			}
		}

		TEST_METHOD(ConstIteratorIncrementOperators)
		{
			//Prefix version
			{
				const Foo a{ 1 };
				const Foo b{ 2 };
				const Foo x{ 10 };
				const Foo y{ 20 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };

				map.Insert(make_pair(a, x));
				map.Insert(make_pair(b, y));

				HashMap<Foo, Foo>::ConstIterator it = map.cbegin();
				Assert::AreEqual(a, (*it).first);
				Assert::AreEqual(x, (*it).second);
				++it;
				Assert::AreEqual(b, (*it).first);
				Assert::AreEqual(y, (*it).second);
			}

			//Postfix version
			{
				const Foo a{ 1 };
				const Foo b{ 2 };
				const Foo x{ 10 };
				const Foo y{ 20 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };

				map.Insert(make_pair(a, x));
				map.Insert(make_pair(b, y));

				HashMap<Foo, Foo>::ConstIterator it = map.cbegin();
				Assert::AreEqual(a, (*it).first);
				Assert::AreEqual(x, (*it).second);
				it++;
				Assert::AreEqual(b, (*it).first);
				Assert::AreEqual(y, (*it).second);
			}
		}

		TEST_METHOD(IteratorDereferenceOperators)
		{
			//Iterator
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo x{ 10 };
				Foo y{ 20 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };

				map.Insert(make_pair(a, x));
				map.Insert(make_pair(b, y));

				HashMap<Foo, Foo>::Iterator it = map.begin();
				Assert::AreEqual(a, (*it).first);
				Assert::AreEqual(x, (*it).second);
				it++;
				Assert::AreEqual(b, (*it).first);
				Assert::AreEqual(y, (*it).second);
			}

			//ConstIterator
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo x{ 10 };
				Foo y{ 20 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };

				map.Insert(make_pair(a, x));
				map.Insert(make_pair(b, y));

				HashMap<Foo, Foo>::ConstIterator it = map.cbegin();
				Assert::AreEqual(a, (*it).first);
				Assert::AreEqual(x, (*it).second);
				it++;
				Assert::AreEqual(b, (*it).first);
				Assert::AreEqual(y, (*it).second);
			}
		}

		TEST_METHOD(IteratorArrowOperator)
		{
			//Iterator
			{
				Foo a{ 1 };
				Foo x{ 10 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };

				HashMap<Foo, Foo>::Iterator it = map.Insert(make_pair(a, x)).first;

				Assert::AreEqual(a, it->first);
				Assert::AreEqual(x, it->second);
			}

			//ConstIterator
			{
				Foo a{ 1 };
				Foo x{ 10 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };

				HashMap<Foo, Foo>::ConstIterator it = map.Insert(make_pair(a, x)).first;

				Assert::AreEqual(a, it->first);
				Assert::AreEqual(x, it->second);
			}
		}

		TEST_METHOD(IteratorEqualityOperators)
		{
			//Iterator
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo x{ 10 };
				Foo y{ 20 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };

				map.Insert(make_pair(a, x));
				map.Insert(make_pair(b, y));

				Assert::IsTrue(map.begin() == map.Find(a));
				Assert::IsTrue(map.begin() != map.Find(b));
			}

			//ConstIterator
			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo x{ 10 };
				Foo y{ 20 };
				HashMap<Foo, Foo> map{ 10, FooHash{} };
				map.Insert(make_pair(a, x));
				map.Insert(make_pair(b, y));

				const HashMap < Foo, Foo> constMap{ map };

				Assert::IsTrue(constMap.begin() == constMap.Find(a));
				Assert::IsTrue(constMap.begin() != constMap.Find(b));
			}
		}

	private:
		inline static _CrtMemState _startMemState;
	};
}