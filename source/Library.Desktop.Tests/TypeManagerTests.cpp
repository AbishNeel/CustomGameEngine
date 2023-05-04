#include "pch.h"
#include "CppUnitTest.h"
#include "AttributedFoo.h"
#include "AttributedBar.h"
#include "Datum.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;
using namespace std;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(TypeManagerTests)
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

		TEST_METHOD(CreateInstance)
		{
			TypeManager::CreateInstance();
			Assert::IsNotNull(TypeManager::GetInstance());
		}

		TEST_METHOD(RegisterType)
		{
			TypeManager::GetInstance()->RegisterType<AttributedFoo, Attributed>(AttributedFoo::Signatures());
			TypeManager::GetInstance()->RegisterType<AttributedBar, AttributedFoo>(AttributedBar::Signatures());

			const Vector<Signature>& signatures = TypeManager::GetInstance()->_signatureMap.Find(AttributedBar::TypeIdClass())->second;
			Assert::AreEqual(size_t(15), signatures.Size());
		}

	private:
		inline static _CrtMemState _startMemState;
	};
}