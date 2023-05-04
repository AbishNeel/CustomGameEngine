#include "pch.h"
#include "CppUnitTest.h"
#include "AttributedFoo.h"
#include "Datum.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTests;
using namespace std;

namespace UnitTestLibraryDesktop
{
	TEST_CLASS(AttributedFooTests)
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

		TEST_METHOD(Constructor)
		{
			AttributedFoo abFoo;
			Assert::AreEqual(size_t(13), abFoo.Size());
			Assert::IsTrue(abFoo["ExternalInteger"].Type() == Datum::DatumTypes::Integer);
			Assert::IsTrue(abFoo["ExternalFloat"].Type() == Datum::DatumTypes::Float);
			Assert::IsTrue(abFoo["ExternalString"].Type() == Datum::DatumTypes::String);
			Assert::IsTrue(abFoo["ExternalVector"].Type() == Datum::DatumTypes::Vector);
			Assert::IsTrue(abFoo["ExternalMatrix"].Type() == Datum::DatumTypes::Matrix);
			Assert::IsTrue(abFoo["ExternalIntegerArray"].Type() == Datum::DatumTypes::Integer);
			Assert::IsTrue(abFoo["ExternalFloatArray"].Type() == Datum::DatumTypes::Float);
			Assert::IsTrue(abFoo["ExternalStringArray"].Type() == Datum::DatumTypes::String);
			Assert::IsTrue(abFoo["ExternalVectorArray"].Type() == Datum::DatumTypes::Vector);
			Assert::IsTrue(abFoo["ExternalMatrixArray"].Type() == Datum::DatumTypes::Matrix);
			Assert::IsTrue(abFoo["NestedScope"].Type() == Datum::DatumTypes::Table);
			Assert::IsTrue(abFoo["NestedScopeArray"].Type() == Datum::DatumTypes::Table);
		}

		TEST_METHOD(CopySemantics)
		{
			//Copy constructor
			{
				AttributedFoo abFoo;
				AttributedFoo copy{ abFoo };
				Assert::IsTrue(copy.Equals(&abFoo));
			}

			//Copy assignment operator
			{
				AttributedFoo abFoo;
				AttributedFoo copy;
				copy.ExternalFloat = 6.9f;
				copy = abFoo;
				Assert::IsTrue(copy.Equals(&abFoo));
			}
		}

		TEST_METHOD(MoveSemantics)
		{
			//Move constructor
			{
				AttributedFoo abFoo;
				AttributedFoo ref{ abFoo };
				AttributedFoo copy{ move(abFoo) };
				Assert::IsTrue(copy.Equals(&ref));
			}

			//Move assignment operator
			{
				AttributedFoo abFoo;
				AttributedFoo ref{ abFoo };
				AttributedFoo copy;
				copy.ExternalFloat = 6.9f;
				copy = move(abFoo);
				Assert::IsTrue(copy.Equals(&ref));
			}
		}

		TEST_METHOD(IsAttribute)
		{
			AttributedFoo abFoo;
			abFoo.AppendAuxiliaryAttribute("Auxiliary"s);

			//IsAttribute()
			{
				Assert::IsTrue(abFoo.IsAttribute("this"s));
				Assert::IsTrue(abFoo.IsAttribute("ExternalInteger"s));
				Assert::IsTrue(abFoo.IsAttribute("ExternalFloat"s));
				Assert::IsTrue(abFoo.IsAttribute("ExternalString"s));
				Assert::IsTrue(abFoo.IsAttribute("ExternalVector"s));
				Assert::IsTrue(abFoo.IsAttribute("ExternalMatrix"s));
				Assert::IsTrue(abFoo.IsAttribute("ExternalIntegerArray"s));
				Assert::IsTrue(abFoo.IsAttribute("ExternalFloatArray"s));
				Assert::IsTrue(abFoo.IsAttribute("ExternalStringArray"s));
				Assert::IsTrue(abFoo.IsAttribute("ExternalVectorArray"s));
				Assert::IsTrue(abFoo.IsAttribute("ExternalMatrixArray"s));
				Assert::IsTrue(abFoo.IsAttribute("NestedScope"s));
				Assert::IsTrue(abFoo.IsAttribute("NestedScopeArray"s));
				Assert::IsTrue(abFoo.IsAttribute("Auxiliary"s));
				Assert::IsFalse(abFoo.IsAttribute("Random"s));
			}

			//IsPrescribedAttribute()
			{
				Assert::IsFalse(abFoo.IsPrescribedAttribute("this"s));
				Assert::IsTrue(abFoo.IsPrescribedAttribute("ExternalInteger"s));
				Assert::IsTrue(abFoo.IsPrescribedAttribute("ExternalFloat"s));
				Assert::IsTrue(abFoo.IsPrescribedAttribute("ExternalString"s));
				Assert::IsTrue(abFoo.IsPrescribedAttribute("ExternalVector"s));
				Assert::IsTrue(abFoo.IsPrescribedAttribute("ExternalMatrix"s));
				Assert::IsTrue(abFoo.IsPrescribedAttribute("ExternalIntegerArray"s));
				Assert::IsTrue(abFoo.IsPrescribedAttribute("ExternalFloatArray"s));
				Assert::IsTrue(abFoo.IsPrescribedAttribute("ExternalStringArray"s));
				Assert::IsTrue(abFoo.IsPrescribedAttribute("ExternalVectorArray"s));
				Assert::IsTrue(abFoo.IsPrescribedAttribute("ExternalMatrixArray"s));
				Assert::IsTrue(abFoo.IsPrescribedAttribute("NestedScope"s));
				Assert::IsTrue(abFoo.IsPrescribedAttribute("NestedScopeArray"s));
				Assert::IsFalse(abFoo.IsPrescribedAttribute("Auxiliary"s));
			}

			//IsAuxiliaryAttribute()
			{
				Assert::IsFalse(abFoo.IsAuxiliaryAttribute("this"s));
				Assert::IsFalse(abFoo.IsAuxiliaryAttribute("ExternalInteger"s));
				Assert::IsFalse(abFoo.IsAuxiliaryAttribute("ExternalFloat"s));
				Assert::IsFalse(abFoo.IsAuxiliaryAttribute("ExternalString"s));
				Assert::IsFalse(abFoo.IsAuxiliaryAttribute("ExternalVector"s));
				Assert::IsFalse(abFoo.IsAuxiliaryAttribute("ExternalMatrix"s));
				Assert::IsFalse(abFoo.IsAuxiliaryAttribute("ExternalIntegerArray"s));
				Assert::IsFalse(abFoo.IsAuxiliaryAttribute("ExternalFloatArray"s));
				Assert::IsFalse(abFoo.IsAuxiliaryAttribute("ExternalStringArray"s));
				Assert::IsFalse(abFoo.IsAuxiliaryAttribute("ExternalVectorArray"s));
				Assert::IsFalse(abFoo.IsAuxiliaryAttribute("ExternalMatrixArray"s));
				Assert::IsFalse(abFoo.IsAuxiliaryAttribute("NestedScope"s));
				Assert::IsFalse(abFoo.IsAuxiliaryAttribute("NestedScopeArray"s));
				Assert::IsTrue(abFoo.IsAuxiliaryAttribute("Auxiliary"s));
			}
		}

		TEST_METHOD(AttributeAccessors)
		{
			AttributedFoo abFoo;
			abFoo.AppendAuxiliaryAttribute("Auxiliary"s);

			//All attributes
			{
				const Vector<string>& attributes = abFoo.Attributes();
				Assert::AreEqual(size_t(14), attributes.Size());
			}

			//Prescribed attributes
			{
				const Vector<string>& attributes = abFoo.PrescribedAttributes();
				Assert::AreEqual(size_t(12), attributes.Size());
			}

			//All attributes
			{
				const Vector<string>& attributes = abFoo.AuxiliaryAttributes();
				Assert::AreEqual(size_t(1), attributes.Size());
			}
		}

	private:
		inline static _CrtMemState _startMemState;
	};
}