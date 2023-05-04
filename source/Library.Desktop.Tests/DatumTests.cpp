#include "pch.h"
#include "CppUnitTest.h"
#include "Datum.h"
#include "Foo.h"
#include <glm/glm.hpp>
#include "Foo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace std;
using namespace UnitTests;

namespace LibraryDesktopTests
{
	TEST_CLASS(DatumTests)
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
			{
				Datum d {Datum::DatumTypes::Integer};
				Assert::AreEqual(size_t(0), d.Size());
				Assert::AreEqual(size_t(0), d.Capacity());
				Assert::IsTrue(d.Type() == Datum::DatumTypes::Integer);
			}

			{
				Datum d{ Datum::DatumTypes::Float};
				Assert::AreEqual(size_t(0), d.Size());
				Assert::AreEqual(size_t(0), d.Capacity());
				Assert::IsTrue(d.Type() == Datum::DatumTypes::Float);
			}

			{
				Datum d{ Datum::DatumTypes::String};
				Assert::AreEqual(size_t(0), d.Size());
				Assert::AreEqual(size_t(0), d.Capacity());
				Assert::IsTrue(d.Type() == Datum::DatumTypes::String);
			}

			{
				Datum d{ Datum::DatumTypes::Vector};
				Assert::AreEqual(size_t(0), d.Size());
				Assert::AreEqual(size_t(0), d.Capacity());
				Assert::IsTrue(d.Type() == Datum::DatumTypes::Vector);
			}

			{
				Datum d{ Datum::DatumTypes::Matrix};
				Assert::AreEqual(size_t(0), d.Size());
				Assert::AreEqual(size_t(0), d.Capacity());
				Assert::IsTrue(d.Type() == Datum::DatumTypes::Matrix);
			}

			{
				Datum d{ Datum::DatumTypes::Pointer};
				Assert::AreEqual(size_t(0), d.Size());
				Assert::AreEqual(size_t(0), d.Capacity());
				Assert::IsTrue(d.Type() == Datum::DatumTypes::Pointer);
			}
		}

		TEST_METHOD(InitializerListConstructor)
		{
			{
				int a = 1;
				int b = 2;
				int c = 3;
				Datum datum{ a, b, c };

				Assert::AreEqual(a, datum.Front<int>());
				Assert::AreEqual(c, datum.Back<int>());
				Assert::AreEqual(size_t(3), datum.Size());
				Assert::AreEqual(size_t(3), datum.Capacity());
				Assert::IsTrue(Datum::DatumTypes::Integer == datum.Type());
			}

			{
				float a = 1.5;
				float b = 2.5;
				float c = 3.5;
				Datum datum{ a, b, c };

				Assert::AreEqual(a, datum.Front<float>());
				Assert::AreEqual(c, datum.Back<float>());
				Assert::AreEqual(size_t(3), datum.Size());
				Assert::AreEqual(size_t(3), datum.Capacity());
				Assert::IsTrue(Datum::DatumTypes::Float == datum.Type());
			}

			{
				string a = "hello"s;
				string b = "bye"s;
				string c = "string"s;
				Datum datum{ a, b, c };

				Assert::AreEqual(a, datum.Front<string>());
				Assert::AreEqual(c, datum.Back<string>());
				Assert::AreEqual(size_t(3), datum.Size());
				Assert::AreEqual(size_t(3), datum.Capacity());
				Assert::IsTrue(Datum::DatumTypes::String == datum.Type());
			}

			{
				glm::vec4 a { 1.5 };
				glm::vec4 b { 2.5 };
				glm::vec4 c{ 3.5 };
				Datum datum{ a, b, c };

				Assert::IsTrue(a == datum.Front<glm::vec4>());
				Assert::IsTrue(c == datum.Back<glm::vec4>());
				Assert::AreEqual(size_t(3), datum.Size());
				Assert::AreEqual(size_t(3), datum.Capacity());
				Assert::IsTrue(Datum::DatumTypes::Vector == datum.Type());
			}

			{
				glm::mat4 a{ 1.5 };
				glm::mat4 b{ 2.5 };
				glm::mat4 c{ 3.5 };
				Datum datum{ a, b, c };

				Assert::IsTrue(a == datum.Front<glm::mat4>());
				Assert::IsTrue(c == datum.Back<glm::mat4>());
				Assert::AreEqual(size_t(3), datum.Size());
				Assert::AreEqual(size_t(3), datum.Capacity());
				Assert::IsTrue(Datum::DatumTypes::Matrix == datum.Type());
			}

			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Datum datum{ &a, &b, &c };

				Assert::IsTrue(&a == datum.Front<RTTI*>());
				Assert::IsTrue(&c == datum.Back<RTTI*>());
				Assert::AreEqual(size_t(3), datum.Size());
				Assert::AreEqual(size_t(3), datum.Capacity());
				Assert::IsTrue(Datum::DatumTypes::Pointer == datum.Type());
			}
		}

		TEST_METHOD(ScalarConstructor)
		{
			{
				int a = 5;
				Datum d = a;
				Assert::AreEqual(a, d.Front<int>());
				Assert::AreEqual(a, d.Back<int>());
				Assert::IsTrue(Datum::DatumTypes::Integer == d.Type());
				Assert::AreEqual(size_t(1), d.Size());
			}

			{
				float a = 5.5f;
				Datum d = a;
				Assert::AreEqual(a, d.Front<float>());
				Assert::AreEqual(a, d.Back<float>());
				Assert::IsTrue(Datum::DatumTypes::Float == d.Type());
				Assert::AreEqual(size_t(1), d.Size());
			}

			{
				string a = "string"s;
				Datum d = a;
				Assert::AreEqual(a, d.Front<string>());
				Assert::AreEqual(a, d.Back<string>());
				Assert::IsTrue(Datum::DatumTypes::String == d.Type());
				Assert::AreEqual(size_t(1), d.Size());
			}

			{
				glm::vec4 a = glm::vec4{ 5.5f };
				Datum d = a;
				Assert::IsTrue(a == d.Front<glm::vec4>());
				Assert::IsTrue(a == d.Back<glm::vec4>());
				Assert::IsTrue(Datum::DatumTypes::Vector == d.Type());
				Assert::AreEqual(size_t(1), d.Size());
			}

			{
				glm::mat4 a = glm::mat4{ 5.5f };
				Datum d = a;
				Assert::IsTrue(a == d.Front<glm::mat4>());
				Assert::IsTrue(a == d.Back<glm::mat4>());
				Assert::IsTrue(Datum::DatumTypes::Matrix == d.Type());
				Assert::AreEqual(size_t(1), d.Size());
			}

			{
				Foo f1{ 5 };
				Datum d = &f1;
				Assert::IsTrue(&f1 == d.Front<RTTI*>());
				Assert::IsTrue(&f1 == d.Back<RTTI*>());
				Assert::IsTrue(Datum::DatumTypes::Pointer == d.Type());
				Assert::AreEqual(size_t(1), d.Size());
			}
		}

		TEST_METHOD(CopySemantics)
		{
			//Copy constructor
			{
				{
					//Internal rhs
					{
						int a = 1;
						int b = 2;
						int c = 3;
						Datum datum{ a, b, c };

						Datum newDatum{ datum };
						Assert::IsTrue(datum == newDatum);
					}

					{
						float a = 1.5f;
						float b = 2.5f;
						float c = 3.5f;
						Datum datum{ a, b, c };

						Datum newDatum{ datum };
						Assert::IsTrue(datum == newDatum);
					}

					{
						string a = "hello"s;
						string b = "bye"s;
						string c = "string"s;
						Datum datum{ a, b, c };

						Datum newDatum{ datum };
						Assert::IsTrue(datum == newDatum);
					}

					{
						glm::vec4 a{ 1.5f };
						glm::vec4 b{ 2.5f };
						glm::vec4 c{ 3.5f };
						Datum datum{ a, b, c };

						Datum newDatum{ datum };
						Assert::IsTrue(datum == newDatum);
					}

					{
						glm::mat4 a{ 1.5f };
						glm::mat4 b{ 2.5f };
						glm::mat4 c{ 3.5f };
						Datum datum{ a, b, c };

						Datum newDatum{ datum };
						Assert::IsTrue(datum == newDatum);
					}

					{
						Foo a{ 1 };
						Foo b{ 2 };
						Foo c{ 3 };
						Datum datum{ &a, &b, &c };

						Datum newDatum{ datum };
						Assert::IsTrue(datum == newDatum);
					}
				}

				//External rhs
				{
					{
						int a[] = { 3, 4, 5 };
						Datum datum;
						datum.SetStorage(a, size(a));

						Datum newDatum { datum };
						Assert::IsTrue(datum == newDatum);
					}

					{
						float a[] = { 3.5f, 4.5f, 5.5f };
						Datum datum;
						datum.SetStorage(a, size(a));

						Datum newDatum{ datum };
						Assert::IsTrue(datum == newDatum);
					}

					{
						string a[] = { "hello"s, "bye"s, "string"s };
						Datum datum;
						datum.SetStorage(a, size(a));

						Datum newDatum{ datum };
						Assert::IsTrue(datum == newDatum);
					}

					{
						glm::vec4 a[] = { glm::vec4{3.5f}, glm::vec4{4.5f}, glm::vec4{5.5f} };
						Datum datum;
						datum.SetStorage(a, size(a));

						Datum newDatum{ datum };
						Assert::IsTrue(datum == newDatum);
					}

					{
						glm::mat4 a[] = { glm::mat4{3.5f}, glm::mat4{4.5f}, glm::mat4{5.5f} };
						Datum datum;
						datum.SetStorage(a, size(a));

						Datum newDatum{ datum };
						Assert::IsTrue(datum == newDatum);
					}

					{
						Foo f1{ 1 };
						Foo f2{ 2 };
						Foo f3{ 3 };
						RTTI* a[] = { &f1, &f2, &f3 };
						Datum datum;
						datum.SetStorage(a, size(a));

						Datum newDatum{ datum };
						Assert::IsTrue(datum == newDatum);
					}
				}
			}

			//Copy assignment operator
			{
				//Internal rhs
				{
					//Internal lhs
					{
						{
							int a = 1;
							int b = 2;
							int c = 3;
							Datum datum{ a, b, c };

							Datum newDatum{ c, a, b };
							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							float a = 1.5f;
							float b = 2.5f;
							float c = 3.5f;
							Datum datum{ a, b, c };

							Datum newDatum{ c, a, b };
							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							string a = "hello"s;
							string b = "bye"s;
							string c = "string"s;
							Datum datum{ a, b, c };

							Datum newDatum{ c, a, b };
							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							glm::vec4 a{ 1.5f };
							glm::vec4 b{ 2.5f };
							glm::vec4 c{ 3.5f };
							Datum datum{ a, b, c };

							Datum newDatum{ c, a, b };
							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							glm::mat4 a{ 1.5f };
							glm::mat4 b{ 2.5f };
							glm::mat4 c{ 3.5f };
							Datum datum{ a, b, c };

							Datum newDatum{ c, a, b };
							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							Foo a{ 1 };
							Foo b{ 2 };
							Foo c{ 3 };
							Datum datum{ &a, &b, &c };

							Datum newDatum{ &c, &a, &b };
							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}
					}

					//External lhs
					{
						{
							Datum datum{ 1, 2, 3 };

							int a[] = { 3, 4, 5 };
							Datum newDatum;
							newDatum.SetStorage(a, size(a));

							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							Datum datum{ 7.5f, 8.5f, 9.5f };

							float a[] = { 3.5f, 4.5f, 5.5f };
							Datum newDatum;
							newDatum.SetStorage(a, size(a));

							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							Datum datum{ "abc"s, "cab"s, "cba"s };

							string a[] = { "hello"s, "bye"s, "string"s };
							Datum newDatum;
							newDatum.SetStorage(a, size(a));

							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							Datum datum{ glm::vec4{1.5f}, glm::vec4{2.5f}, glm::vec4{3.5f} };

							glm::vec4 a[] = { glm::vec4{3.5f}, glm::vec4{4.5f}, glm::vec4{5.5f} };
							Datum newDatum;
							newDatum.SetStorage(a, size(a));

							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							Datum datum{ glm::mat4{1.5f}, glm::mat4{2.5f}, glm::mat4{3.5f} };

							glm::mat4 a[] = { glm::mat4{3.5f}, glm::mat4{4.5f}, glm::mat4{5.5f} };
							Datum newDatum;
							newDatum.SetStorage(a, size(a));

							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							Foo f1{ 1 };
							Foo f2{ 2 };
							Foo f3{ 3 };
							Datum datum{ &f3, &f1, &f2 };

							RTTI* a[] = { &f1, &f2, &f3 };
							Datum newDatum;
							newDatum.SetStorage(a, size(a));

							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}
					}
				}

				//External rhs
				{
					//Internal lhs
					{
						{
							int a[] = { 3, 4, 5 };
							Datum datum;
							datum.SetStorage(a, size(a));

							Datum newDatum{ 1, 2, 3 };
							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							float a[] = { 3.5f, 4.5f, 5.5f };
							Datum datum;
							datum.SetStorage(a, size(a));

							Datum newDatum{ 1.5f, 2.5f, 3.5f };
							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							string a[] = { "hello"s, "bye"s, "string"s };
							Datum datum;
							datum.SetStorage(a, size(a));

							Datum newDatum{ "abc"s, "cab"s, "cba"s };
							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							glm::vec4 a[] = { glm::vec4{ 3.5f }, glm::vec4{ 4.5f }, glm::vec4 { 5.5f } };
							Datum datum;
							datum.SetStorage(a, size(a));

							Datum newDatum{ glm::vec4{ 1.5f }, glm::vec4{ 2.5f }, glm::vec4{ 3.5f } };
							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							glm::mat4 a[] = { glm::mat4{ 3.5f }, glm::mat4{ 4.5f }, glm::mat4 { 5.5f } };
							Datum datum;
							datum.SetStorage(a, size(a));

							Datum newDatum{ glm::mat4{ 1.5f }, glm::mat4{ 2.5f }, glm::mat4{ 3.5f } };
							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}
						
						{
							Foo f1{ 1 };
							Foo f2{ 2 };
							Foo f3{ 3 };
							RTTI* a[] = { &f1, &f2, &f3 };
							Datum datum;
							datum.SetStorage(a, size(a));

							Datum newDatum { &f2, &f3, &f1 };
							Assert::IsFalse(newDatum == datum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}
					}

					//External lhs
					{
						{
							int a[] = { 3, 4, 5 };
							int b[] = { 7, 8, 9 };

							Datum datum;
							datum.SetStorage(a, size(a));

							Datum newDatum;
							newDatum.SetStorage(b, size(b));

							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							float a[] = { 3.5f, 4.5f, 5.5f };
							float b[] = { 6.5f, 7.5f, 9.5f };

							Datum datum;
							datum.SetStorage(a, size(a));

							Datum newDatum;
							newDatum.SetStorage(b, size(b));

							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							string a[] = { "hello"s, "bye"s, "string"s };
							string b[] = { "abc"s, "cab"s, "cba"s };

							Datum datum;
							datum.SetStorage(a, size(a));

							Datum newDatum;
							newDatum.SetStorage(b, size(b));

							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							glm::vec4 a[] = { glm::vec4{ 3.5f }, glm::vec4{ 4.5f }, glm::vec4 { 5.5f } };
							glm::vec4 b[] = { glm::vec4{ 6.5f }, glm::vec4{ 7.5f }, glm::vec4 { 8.5f } };
							
							Datum datum;
							datum.SetStorage(a, size(a));

							Datum newDatum;
							newDatum.SetStorage(b, size(b));

							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							glm::mat4 a[] = { glm::mat4{ 3.5f }, glm::mat4{ 4.5f }, glm::mat4 { 5.5f } };
							glm::mat4 b[] = { glm::mat4{ 6.5f }, glm::mat4{ 7.5f }, glm::mat4 { 8.5f } };
							
							Datum datum;
							datum.SetStorage(a, size(a));

							Datum newDatum;
							newDatum.SetStorage(b, size(b));

							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}

						{
							Foo f1{ 1 };
							Foo f2{ 2 };
							Foo f3{ 3 };

							RTTI* a[] = { &f1, &f2, &f3 };
							RTTI* b[] = { &f2, &f3, &f1 };
							
							Datum datum;
							datum.SetStorage(a, size(a));

							Datum newDatum;
							newDatum.SetStorage(b, size(b));

							Assert::IsFalse(datum == newDatum);
							newDatum = datum;
							Assert::IsTrue(datum == newDatum);
						}
					}
				}
			}
		}

		TEST_METHOD(MoveSemantics)
		{
			//Move constructor
			{
				//Internal rhs
				{
					{
						int a = 1;
						int b = 2;
						int c = 3;
						Datum datum{ a, b, c };
						Datum ref{ datum };

						Datum newDatum{ move(datum) };
						Assert::IsTrue(newDatum == ref);
					}

					{
						float a = 1.5f;
						float b = 2.5f;
						float c = 3.5f;
						Datum datum{ a, b, c };
						Datum ref{ datum };

						Datum newDatum{ move(datum) };
						Assert::IsTrue(newDatum == ref);
					}

					{
						string a = "hello"s;
						string b = "bye"s;
						string c = "string"s;
						Datum datum{ a, b, c };
						Datum ref{ datum };

						Datum newDatum{ move(datum) };
						Assert::IsTrue(newDatum == ref);
					}

					{
						glm::vec4 a{ 1.5f };
						glm::vec4 b{ 2.5f };
						glm::vec4 c{ 3.5f };
						Datum datum{ a, b, c };
						Datum ref{ datum };

						Datum newDatum{ move(datum) };
						Assert::IsTrue(newDatum == ref);
					}

					{
						glm::mat4 a{ 1.5f };
						glm::mat4 b{ 2.5f };
						glm::mat4 c{ 3.5f };
						Datum datum{ a, b, c };
						Datum ref{ datum };

						Datum newDatum{ move(datum) };
						Assert::IsTrue(newDatum == ref);
					}

					{
						Foo a{ 1 };
						Foo b{ 2 };
						Foo c{ 3 };
						Datum datum{ &a, &b, &c };
						Datum ref{ datum };

						Datum newDatum{ move(datum) };
						Assert::IsTrue(newDatum == ref);
					}
				}

				//External rhs
				{
					{
						int a[] = { 3, 4, 5 };
						Datum datum;
						datum.SetStorage(a, size(a));
						Datum ref{ datum };

						Datum newDatum{ move(datum) };
						Assert::IsTrue(ref == newDatum);
					}

					{
						float a[] = { 3.5f, 4.5f, 5.5f };
						Datum datum;
						datum.SetStorage(a, size(a));
						Datum ref{ datum };

						Datum newDatum{ move(datum) };
						Assert::IsTrue(ref == newDatum);
					}

					{
						string a[] = { "hello"s, "bye"s, "string"s };
						Datum datum;
						datum.SetStorage(a, size(a));
						Datum ref{ datum };

						Datum newDatum{ move(datum) };
						Assert::IsTrue(ref == newDatum);
					}

					{
						glm::vec4 a[] = { glm::vec4{3.5f}, glm::vec4{4.5f}, glm::vec4{5.5f} };
						Datum datum;
						datum.SetStorage(a, size(a));
						Datum ref{ datum };

						Datum newDatum{ move(datum) };
						Assert::IsTrue(ref == newDatum);
					}

					{
						glm::mat4 a[] = { glm::mat4{3.5f}, glm::mat4{4.5f}, glm::mat4{5.5f} };
						Datum datum;
						datum.SetStorage(a, size(a));
						Datum ref{ datum };

						Datum newDatum{ move(datum) };
						Assert::IsTrue(ref == newDatum);
					}

					{
						Foo f1{ 1 };
						Foo f2{ 2 };
						Foo f3{ 3 };
						RTTI* a[] = { &f1, &f2, &f3 };
						Datum datum;
						datum.SetStorage(a, size(a));
						Datum ref{ datum };

						Datum newDatum{ move(datum) };
						Assert::IsTrue(ref == newDatum);
					}
				}
			}

			//Move assignment operator
			{
			//Internal rhs
				{
					//Internal lhs
					{
						{
							int a = 1;
							int b = 2;
							int c = 3;
							Datum datum{ a, b, c };
							Datum ref{ datum };

							Datum newDatum{ c, a, b };
							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							float a = 1.5f;
							float b = 2.5f;
							float c = 3.5f;
							Datum datum{ a, b, c };
							Datum ref{ datum };

							Datum newDatum{ c, a, b };
							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							string a = "hello"s;
							string b = "bye"s;
							string c = "string"s;
							Datum datum{ a, b, c };
							Datum ref{ datum };

							Datum newDatum{ c, a, b };
							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							glm::vec4 a{ 1.5f };
							glm::vec4 b{ 2.5f };
							glm::vec4 c{ 3.5f };
							Datum datum{ a, b, c };
							Datum ref{ datum };

							Datum newDatum{ c, a, b };
							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							glm::mat4 a{ 1.5f };
							glm::mat4 b{ 2.5f };
							glm::mat4 c{ 3.5f };
							Datum datum{ a, b, c };
							Datum ref{ datum };

							Datum newDatum{ c, a, b };
							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							Foo a{ 1 };
							Foo b{ 2 };
							Foo c{ 3 };
							Datum datum{ &a, &b, &c };
							Datum ref{ datum };

							Datum newDatum{ &c, &a, &b };
							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}
					}

					//External lhs
					{
						{
							Datum datum{ 1, 2, 3 };
							Datum ref{ datum };

							int a[] = { 3, 4, 5 };
							Datum newDatum;
							newDatum.SetStorage(a, size(a));

							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							Datum datum{ 7.5f, 8.5f, 9.5f };
							Datum ref{ datum };

							float a[] = { 3.5f, 4.5f, 5.5f };
							Datum newDatum;
							newDatum.SetStorage(a, size(a));

							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							Datum datum{ "abc"s, "cab"s, "cba"s };
							Datum ref{ datum };

							string a[] = { "hello"s, "bye"s, "string"s };
							Datum newDatum;
							newDatum.SetStorage(a, size(a));

							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							Datum datum{ glm::vec4{1.5f}, glm::vec4{2.5f}, glm::vec4{3.5f} };
							Datum ref{ datum };

							glm::vec4 a[] = { glm::vec4{3.5f}, glm::vec4{4.5f}, glm::vec4{5.5f} };
							Datum newDatum;
							newDatum.SetStorage(a, size(a));

							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							Datum datum{ glm::mat4{1.5f}, glm::mat4{2.5f}, glm::mat4{3.5f} };
							Datum ref{ datum };

							glm::mat4 a[] = { glm::mat4{3.5f}, glm::mat4{4.5f}, glm::mat4{5.5f} };
							Datum newDatum;
							newDatum.SetStorage(a, size(a));

							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							Foo f1{ 1 };
							Foo f2{ 2 };
							Foo f3{ 3 };
							Datum datum{ &f3, &f1, &f2 };
							Datum ref{ datum };

							RTTI* a[] = { &f1, &f2, &f3 };
							Datum newDatum;
							newDatum.SetStorage(a, size(a));

							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}
					}
				}

				//External rhs
				{
					//Internal lhs
					{
						{
							int a[] = { 3, 4, 5 };
							Datum datum;
							datum.SetStorage(a, size(a));
							Datum ref{ datum };

							Datum newDatum{ 1, 2, 3 };
							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							float a[] = { 3.5f, 4.5f, 5.5f };
							Datum datum;
							datum.SetStorage(a, size(a));
							Datum ref{ datum };

							Datum newDatum{ 1, 2, 3 };
							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							string a[] = { "hello"s, "bye"s, "string"s };
							Datum datum;
							datum.SetStorage(a, size(a));
							Datum ref{ datum };

							Datum newDatum{ 1, 2, 3 };
							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							glm::vec4 a[] = { glm::vec4{ 3.5f }, glm::vec4{ 4.5f }, glm::vec4 { 5.5f } };
							Datum datum;
							datum.SetStorage(a, size(a));
							Datum ref{ datum };

							Datum newDatum{ 1, 2, 3 };
							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							glm::mat4 a[] = { glm::mat4{ 3.5f }, glm::mat4{ 4.5f }, glm::mat4 { 5.5f } };
							Datum datum;
							datum.SetStorage(a, size(a));
							Datum ref{ datum };

							Datum newDatum{ 1, 2, 3 };
							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							Foo f1{ 1 };
							Foo f2{ 2 };
							Foo f3{ 3 };
							RTTI* a[] = { &f1, &f2, &f3 };
							Datum datum;
							datum.SetStorage(a, size(a));
							Datum ref{ datum };

							Datum newDatum{ 1, 2, 3 };
							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}
					}

					//External lhs
					{
						{
							int a[] = { 3, 4, 5 };
							int b[] = { 7, 8, 9 };

							Datum datum;
							datum.SetStorage(a, size(a));
							Datum ref{ datum };

							Datum newDatum;
							newDatum.SetStorage(b, size(b));

							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							float a[] = { 3.5f, 4.5f, 5.5f };
							float b[] = { 6.5f, 7.5f, 9.5f };

							Datum datum;
							datum.SetStorage(a, size(a));
							Datum ref{ datum };

							Datum newDatum;
							newDatum.SetStorage(b, size(b));

							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							string a[] = { "hello"s, "bye"s, "string"s };
							string b[] = { "abc"s, "cab"s, "cba"s };

							Datum datum;
							datum.SetStorage(a, size(a));
							Datum ref{ datum };

							Datum newDatum;
							newDatum.SetStorage(b, size(b));

							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							glm::vec4 a[] = { glm::vec4{ 3.5f }, glm::vec4{ 4.5f }, glm::vec4 { 5.5f } };
							glm::vec4 b[] = { glm::vec4{ 6.5f }, glm::vec4{ 7.5f }, glm::vec4 { 8.5f } };

							Datum datum;
							datum.SetStorage(a, size(a));
							Datum ref{ datum };

							Datum newDatum;
							newDatum.SetStorage(b, size(b));

							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							glm::mat4 a[] = { glm::mat4{ 3.5f }, glm::mat4{ 4.5f }, glm::mat4 { 5.5f } };
							glm::mat4 b[] = { glm::mat4{ 6.5f }, glm::mat4{ 7.5f }, glm::mat4 { 8.5f } };

							Datum datum;
							datum.SetStorage(a, size(a));
							Datum ref{ datum };

							Datum newDatum;
							newDatum.SetStorage(b, size(b));

							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}

						{
							Foo f1{ 1 };
							Foo f2{ 2 };
							Foo f3{ 3 };

							RTTI* a[] = { &f1, &f2, &f3 };
							RTTI* b[] = { &f2, &f3, &f1 };

							Datum datum;
							datum.SetStorage(a, size(a));
							Datum ref{ datum };

							Datum newDatum;
							newDatum.SetStorage(b, size(b));

							Assert::IsFalse(datum == newDatum);
							newDatum = move(datum);
							Assert::IsTrue(ref == newDatum);
						}
					}
				}
			}
		}

		TEST_METHOD(AssignmentOperators)
		{
			{
				Datum d;
				
				d = 5;
				Assert::AreEqual(size_t(1), d.Size());
				Assert::AreEqual(5, d.Front<int>());
				Assert::ExpectException<runtime_error>([&d]() { d = 7.5f; });
				
				d.PushBack(10);
				Assert::AreEqual(5, d.Front<int>());
				Assert::AreEqual(10, d.Back<int>());

				d = 20;
				Assert::AreEqual(20, d.Front<int>());
				Assert::AreEqual(10, d.Back<int>());
			}

			{
				Datum d;

				d = 5.5f;
				Assert::AreEqual(size_t(1), d.Size());
				Assert::AreEqual(5.5f, d.Front<float>());
				Assert::ExpectException<runtime_error>([&d]() { d = "string"s; });

				d.PushBack(10.5f);
				Assert::AreEqual(5.5f, d.Front<float>());
				Assert::AreEqual(10.5f, d.Back<float>());

				d = 20.5f;
				Assert::AreEqual(20.5f, d.Front<float>());
				Assert::AreEqual(10.5f, d.Back<float>());
			}

			{
				Datum d;

				d = "string"s;
				Assert::AreEqual(size_t(1), d.Size());
				Assert::AreEqual("string"s, d.Front<string>());
				Assert::ExpectException<runtime_error>([&d]() { d = 5.5f; });

				d.PushBack("hello"s);
				Assert::AreEqual("string"s, d.Front<string>());
				Assert::AreEqual("hello"s, d.Back<string>());

				d = "bye"s;
				Assert::AreEqual("bye"s, d.Front<string>());
				Assert::AreEqual("hello"s, d.Back<string>());
			}

			{
				Datum d;

				d = glm::vec4{ 5.5f };
				Assert::AreEqual(size_t(1), d.Size());
				Assert::IsTrue(glm::vec4{ 5.5f } == d.Front<glm::vec4>());
				Assert::ExpectException<runtime_error>([&d]() { d = "string"s; });

				d.PushBack(glm::vec4{ 10.5f });
				Assert::IsTrue(glm::vec4{ 5.5f } == d.Front<glm::vec4>());
				Assert::IsTrue(glm::vec4{ 10.5f } == d.Back<glm::vec4>());

				d = glm::vec4{ 20.5f };
				Assert::IsTrue(glm::vec4{ 20.5f } == d.Front<glm::vec4>());
				Assert::IsTrue(glm::vec4{ 10.5f } == d.Back<glm::vec4>());
			}

			{
				Datum d;

				d = glm::mat4{ 5.5f };
				Assert::AreEqual(size_t(1), d.Size());
				Assert::IsTrue(glm::mat4{ 5.5f } == d.Front<glm::mat4>());
				Assert::ExpectException<runtime_error>([&d]() { d = "string"s; });

				d.PushBack(glm::mat4{ 10.5f });
				Assert::IsTrue(glm::mat4{ 5.5f } == d.Front<glm::mat4>());
				Assert::IsTrue(glm::mat4{ 10.5f } == d.Back<glm::mat4>());

				d = glm::mat4{ 20.5f };
				Assert::IsTrue(glm::mat4{ 20.5f } == d.Front<glm::mat4>());
				Assert::IsTrue(glm::mat4{ 10.5f } == d.Back<glm::mat4>());
			}

			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Datum d;

				d = &a;
				Assert::AreEqual(size_t(1), d.Size());
				Assert::IsTrue(&a == d.Front<RTTI*>());
				Assert::ExpectException<runtime_error>([&d]() { d = 7.5f; });

				d.PushBack(&b);
				Assert::IsTrue(&a == d.Front<RTTI*>());
				Assert::IsTrue(&b == d.Back<RTTI*>());

				d = &c;
				Assert::IsTrue(&c == d.Front<RTTI*>());
				Assert::IsTrue(&b == d.Back<RTTI*>());
			}
		}

		TEST_METHOD(PushBack)
		{
			{
				Datum d;
				Assert::IsTrue(d.Type() == Datum::DatumTypes::Unknown);

				d.PushBack(1);
				Assert::AreEqual(size_t(1), d.Size());
				Assert::AreEqual(size_t(1), d.Capacity());
				Assert::IsTrue(d.Type() == Datum::DatumTypes::Integer);
				Assert::AreEqual(1, d.Front<int>());
				Assert::AreEqual(1, d.Back<int>());
				Assert::ExpectException<runtime_error>([&d]() { d.PushBack(1.7f); });
			}

			{
				Datum d;
				Assert::IsTrue(d.Type() == Datum::DatumTypes::Unknown);

				d.PushBack(1.5f);
				Assert::AreEqual(size_t(1), d.Size());
				Assert::AreEqual(size_t(1), d.Capacity());
				Assert::IsTrue(d.Type() == Datum::DatumTypes::Float);
				Assert::AreEqual(1.5f, d.Front<float>());
				Assert::AreEqual(1.5f, d.Back<float>());
				Assert::ExpectException<runtime_error>([&d]() { d.PushBack("string"s); });
			}

			{
				Datum d;
				Assert::IsTrue(d.Type() == Datum::DatumTypes::Unknown);
				const std::string s = "hello"s;

				d.PushBack(s);
				Assert::AreEqual(size_t(1), d.Size());
				Assert::AreEqual(size_t(1), d.Capacity());
				Assert::IsTrue(d.Type() == Datum::DatumTypes::String);
				Assert::AreEqual("hello"s, d.Front<string>());
				Assert::AreEqual("hello"s, d.Back<string>());
				Assert::ExpectException<runtime_error>([&d]() { d.PushBack(glm::vec4{7.5f}); });
			}

			{
				Datum d;
				Assert::IsTrue(d.Type() == Datum::DatumTypes::Unknown);
				glm::vec4 vec{ .5f };

				d.PushBack(vec);
				Assert::AreEqual(size_t(1), d.Size());
				Assert::AreEqual(size_t(1), d.Capacity());
				Assert::IsTrue(d.Type() == Datum::DatumTypes::Vector);
				Assert::IsTrue(vec == d.Front<glm::vec4>());
				Assert::IsTrue(vec == d.Back<glm::vec4>());
				Assert::ExpectException<runtime_error>([&d]() { d.PushBack(glm::mat4{1.3f}); });
			}

			{
				Datum d;
				Assert::IsTrue(d.Type() == Datum::DatumTypes::Unknown);
				glm::mat4 mat{ .5f };

				d.PushBack(mat);
				Assert::AreEqual(size_t(1), d.Size());
				Assert::AreEqual(size_t(1), d.Capacity());
				Assert::IsTrue(d.Type() == Datum::DatumTypes::Matrix);
				Assert::IsTrue(mat == d.Front<glm::mat4>());
				Assert::IsTrue(mat == d.Back<glm::mat4>());

				Foo foo{ 1 };
				Assert::ExpectException<runtime_error>([&d, &foo]() { d.PushBack(&foo); });
			}

			{
				Datum d;
				Assert::IsTrue(d.Type() == Datum::DatumTypes::Unknown);
				Foo a{ 1 };

				d.PushBack(&a);
				Assert::AreEqual(size_t(1), d.Size());
				Assert::AreEqual(size_t(1), d.Capacity());
				Assert::IsTrue(d.Type() == Datum::DatumTypes::Pointer);
				Assert::IsTrue(&a == d.Front<RTTI*>());
				Assert::IsTrue(&a == d.Back<RTTI*>());
				Assert::ExpectException<runtime_error>([&d]() { d.PushBack(5); });
			}
		}

		TEST_METHOD(PopBack)
		{
			{
				int a = 1;
				int b = 2;
				int c = 3;
				Datum datum{ a, b, c };

				Assert::AreEqual(size_t(3), datum.Size());
				Assert::AreEqual(c, datum.Back<int>());
				datum.PopBack();
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::AreEqual(b, datum.Back<int>());
				datum.PopBack();
				Assert::AreEqual(size_t(1), datum.Size());
				Assert::AreEqual(a, datum.Back<int>());
				datum.PopBack();
				Assert::ExpectException<out_of_range>([&datum]() { datum.Back<int>(); });
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::ExpectException<runtime_error>([&datum]() { datum.PopBack(); });
				Assert::AreEqual(size_t(0), datum.Size());

			}

			{
				float a = 1.5;
				float b = 2.5;
				float c = 3.5;
				Datum datum{ a, b, c };

				Assert::AreEqual(size_t(3), datum.Size());
				Assert::AreEqual(c, datum.Back<float>());
				datum.PopBack();
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::AreEqual(b, datum.Back<float>());
				datum.PopBack();
				Assert::AreEqual(size_t(1), datum.Size());
				Assert::AreEqual(a, datum.Back<float>());
				datum.PopBack();
				Assert::ExpectException<out_of_range>([&datum]() { datum.Back<float>(); });
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::ExpectException<runtime_error>([&datum]() { datum.PopBack(); });
				Assert::AreEqual(size_t(0), datum.Size());
			}

			{
				string a = "hello"s;
				string b = "bye"s;
				string c = "string"s;
				Datum datum{ a, b, c };

				Assert::AreEqual(size_t(3), datum.Size());
				Assert::AreEqual(c, datum.Back<string>());
				datum.PopBack();
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::AreEqual(b, datum.Back<string>());
				datum.PopBack();
				Assert::AreEqual(size_t(1), datum.Size());
				Assert::AreEqual(a, datum.Back<string>());
				datum.PopBack();
				Assert::ExpectException<out_of_range>([&datum]() { datum.Back<string>(); });
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::ExpectException<runtime_error>([&datum]() { datum.PopBack(); });
				Assert::AreEqual(size_t(0), datum.Size());
			}

			{
				glm::vec4 a{ 1.5 };
				glm::vec4 b{ 2.5 };
				glm::vec4 c{ 3.5 };
				Datum datum{ a, b, c };

				Assert::AreEqual(size_t(3), datum.Size());
				Assert::IsTrue(c == datum.Back<glm::vec4>());
				datum.PopBack();
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::IsTrue(b == datum.Back<glm::vec4>());
				datum.PopBack();
				Assert::AreEqual(size_t(1), datum.Size());
				Assert::IsTrue(a == datum.Back<glm::vec4>());
				datum.PopBack();
				Assert::ExpectException<out_of_range>([&datum]() { datum.Back<glm::vec4>(); });
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::ExpectException<runtime_error>([&datum]() { datum.PopBack(); });
				Assert::AreEqual(size_t(0), datum.Size());
			}

			{
				glm::mat4 a{ 1.5 };
				glm::mat4 b{ 2.5 };
				glm::mat4 c{ 3.5 };
				Datum datum{ a, b, c };

				Assert::AreEqual(size_t(3), datum.Size());
				Assert::IsTrue(c == datum.Back<glm::mat4>());
				datum.PopBack();
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::IsTrue(b == datum.Back<glm::mat4>());
				datum.PopBack();
				Assert::AreEqual(size_t(1), datum.Size());
				Assert::IsTrue(a == datum.Back<glm::mat4>());
				datum.PopBack();
				Assert::ExpectException<out_of_range>([&datum]() { datum.Back<glm::mat4>(); });
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::ExpectException<runtime_error>([&datum]() { datum.PopBack(); });
				Assert::AreEqual(size_t(0), datum.Size());
			}

			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Datum datum{ &a, &b, &c };

				Assert::AreEqual(size_t(3), datum.Size());
				Assert::IsTrue(&c == datum.Back<RTTI*>());
				datum.PopBack();
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::IsTrue(&b == datum.Back<RTTI*>());
				datum.PopBack();
				Assert::AreEqual(size_t(1), datum.Size());
				Assert::IsTrue(&a == datum.Back<RTTI*>());
				datum.PopBack();
				Assert::ExpectException<out_of_range>([&datum]() { datum.Back<RTTI*>(); });
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::ExpectException<runtime_error>([&datum]() { datum.PopBack(); });
				Assert::AreEqual(size_t(0), datum.Size());
			}
		}

		TEST_METHOD(Reserve)
		{
			{
				Datum datum;
				datum.Reserve(10);
				Assert::AreEqual(size_t(0), datum.Capacity());
				datum.SetType(Datum::DatumTypes::Integer);
				datum.Reserve(10);
				Assert::AreEqual(size_t(10), datum.Capacity());
			}

			{
				Datum datum;
				datum.Reserve(10);
				Assert::AreEqual(size_t(0), datum.Capacity());
				datum.SetType(Datum::DatumTypes::Float);
				datum.Reserve(10);
				Assert::AreEqual(size_t(10), datum.Capacity());
			}

			{
				Datum datum;
				datum.Reserve(10);
				Assert::AreEqual(size_t(0), datum.Capacity());
				datum.SetType(Datum::DatumTypes::String);
				datum.Reserve(10);
				Assert::AreEqual(size_t(10), datum.Capacity());
			}

			{
				Datum datum;
				datum.Reserve(10);
				Assert::AreEqual(size_t(0), datum.Capacity());
				datum.SetType(Datum::DatumTypes::Vector);
				datum.Reserve(10);
				Assert::AreEqual(size_t(10), datum.Capacity());
			}

			{
				Datum datum;
				datum.Reserve(10);
				Assert::AreEqual(size_t(0), datum.Capacity());
				datum.SetType(Datum::DatumTypes::Matrix);
				datum.Reserve(10);
				Assert::AreEqual(size_t(10), datum.Capacity());
			}

			{
				Datum datum;
				datum.Reserve(10);
				Assert::AreEqual(size_t(0), datum.Capacity());
				datum.SetType(Datum::DatumTypes::Pointer);
				datum.Reserve(10);
				Assert::AreEqual(size_t(10), datum.Capacity());
			}

		}

		TEST_METHOD(SetStorage)
		{
			int x[] = { 6, 7, 8 };
			float y[] = { 7.5f, 8.5f, 9.5f };
			string z[] = { "abc"s, "cba"s, "cab"s };

			{
				int a[] = { 3, 4, 5 };
				Datum datum{ 5, 6, 7 };
				datum.SetStorage(a, size(a));

				Assert::ExpectException<runtime_error>([&datum, &y]() { datum.SetStorage(y, size(y)); });

				Assert::AreEqual(3, datum.Front<int>());
				Assert::AreEqual(5, datum.Back<int>());
				Assert::AreEqual(size_t(3), datum.Size());
				Assert::AreEqual(size_t(3), datum.Capacity());
				Assert::IsTrue(datum.Type() == Datum::DatumTypes::Integer);

				datum.SetStorage(x, size(x));
				Assert::AreEqual(6, datum.Front<int>());
				Assert::AreEqual(8, datum.Back<int>());
			}

			{
				float a[] = { 3.5f, 4.5f, 5.5f };
				Datum datum { 5.5f, 3.5f, 1.5f};
				datum.SetStorage(a, size(a));

				Assert::ExpectException<runtime_error>([&datum, &x]() { datum.SetStorage(x, size(x)); });

				Assert::AreEqual(3.5f, datum.Front<float>());
				Assert::AreEqual(5.5f, datum.Back<float>());
				Assert::AreEqual(size_t(3), datum.Size());
				Assert::AreEqual(size_t(3), datum.Capacity());
				Assert::IsTrue(datum.Type() == Datum::DatumTypes::Float);

				datum.SetStorage(y, size(y));
				Assert::AreEqual(7.5f, datum.Front<float>());
				Assert::AreEqual(9.5f, datum.Back<float>());
			}

			{
				string a[] = { "hello"s, "bye"s, "string"s};
				Datum datum{ "abc"s, "cab"s, "cba"s };
				datum.SetStorage(a, size(a));
				
				glm::vec4 vecs[] = { glm::vec4 {5.5f}, glm::vec4{1.5f}, glm::vec4{7.5f} };
				Assert::ExpectException<runtime_error>([&datum, &vecs]() { datum.SetStorage(vecs, size(vecs)); });

				Assert::AreEqual("hello"s, datum.Front<string>());
				Assert::AreEqual("string"s, datum.Back<string>());
				Assert::AreEqual(size_t(3), datum.Size());
				Assert::AreEqual(size_t(3), datum.Capacity());
				Assert::IsTrue(datum.Type() == Datum::DatumTypes::String);

				datum.SetStorage(z, size(z));
				Assert::AreEqual("abc"s, datum.Front<string>());
				Assert::AreEqual("cab"s, datum.Back<string>());
			}

			{
				glm::vec4 a[] = { glm::vec4{3.5f}, glm::vec4{4.5f}, glm::vec4{5.5f} };
				Datum datum{ glm::vec4{5.5f}, glm::vec4{6.5f}, glm::vec4{7.5f} };
				datum.SetStorage(a, size(a));

				glm::mat4 mats[] = { glm::mat4 {5.5f}, glm::mat4{1.5f}, glm::mat4{7.5f} };
				Assert::ExpectException<runtime_error>([&datum, &mats]() { datum.SetStorage(mats, size(mats)); });

				Assert::IsTrue(glm::vec4{ 3.5f } == datum.Front<glm::vec4>());
				Assert::IsTrue(glm::vec4{ 5.5f } == datum.Back<glm::vec4>());
				Assert::AreEqual(size_t(3), datum.Size());
				Assert::AreEqual(size_t(3), datum.Capacity());
				Assert::IsTrue(datum.Type() == Datum::DatumTypes::Vector);
			}

			{
				glm::mat4 a[] = { glm::mat4{3.5f}, glm::mat4{4.5f}, glm::mat4{5.5f} };
				Datum datum{ glm::mat4{5.5f}, glm::mat4{6.5f}, glm::mat4{7.5f} };
				datum.SetStorage(a, size(a));

				Foo f1{ 1 };
				Foo f2{ 2 };
				Foo f3{ 3 };
				RTTI* foos[] = { &f1, &f2, &f3 };
				Assert::ExpectException<runtime_error>([&datum, &foos]() { datum.SetStorage(foos, size(foos)); });

				Assert::IsTrue(glm::mat4{ 3.5f } == datum.Front<glm::mat4>());
				Assert::IsTrue(glm::mat4{ 5.5f } == datum.Back<glm::mat4>());
				Assert::AreEqual(size_t(3), datum.Size());
				Assert::AreEqual(size_t(3), datum.Capacity());
				Assert::IsTrue(datum.Type() == Datum::DatumTypes::Matrix);
			}

			{
				Foo f1{ 1 };
				Foo f2{ 2 };
				Foo f3{ 3 };
				RTTI* a[] = { &f1, &f2, &f3 };
				Datum datum { &f2, &f3, &f1 };
				datum.SetStorage(a, size(a));

				Assert::ExpectException<runtime_error>([&datum, &z]() { datum.SetStorage(z, size(z)); });

				Assert::IsTrue(&f1 == datum.Front<RTTI*>());
				Assert::IsTrue(&f3 == datum.Back<RTTI*>());
				Assert::AreEqual(size_t(3), datum.Size());
				Assert::AreEqual(size_t(3), datum.Capacity());
				Assert::IsTrue(datum.Type() == Datum::DatumTypes::Pointer);
			}
		}

		TEST_METHOD(Front)
		{
			//Non-const version
			{
				{
					int a = 1;
					int b = 2;
					int c = 3;
					Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<float>(); });
					Assert::AreEqual(a, datum.Front<int>());
					datum.PopBack();
					datum.PopBack();
					datum.PopBack();
					Assert::ExpectException<out_of_range>([&datum]() { datum.Front<int>(); });
				}

				{
					float a = 1.5;
					float b = 2.5;
					float c = 3.5;
					Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<int>(); });
					Assert::AreEqual(a, datum.Front<float>());
					datum.PopBack();
					datum.PopBack();
					datum.PopBack();
					Assert::ExpectException<out_of_range>([&datum]() { datum.Front<float>(); });
				}

				{
					string a = "hello"s;
					string b = "bye"s;
					string c = "string"s;
					Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<glm::vec4>(); });
					Assert::AreEqual(a, datum.Front<string>());
					datum.PopBack();
					datum.PopBack();
					datum.PopBack();
					Assert::ExpectException<out_of_range>([&datum]() { datum.Front<string>(); });
				}

				{
					glm::vec4 a{ 1.5 };
					glm::vec4 b{ 2.5 };
					glm::vec4 c{ 3.5 };
					Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<glm::mat4>(); });
					Assert::IsTrue(a == datum.Front<glm::vec4>());
					datum.PopBack();
					datum.PopBack();
					datum.PopBack();
					Assert::ExpectException<out_of_range>([&datum]() { datum.Front<glm::vec4>(); });
				}

				{
					glm::mat4 a{ 1.5 };
					glm::mat4 b{ 2.5 };
					glm::mat4 c{ 3.5 };
					Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<RTTI*>(); });
					Assert::IsTrue(a == datum.Front<glm::mat4>());
					datum.PopBack();
					datum.PopBack();
					datum.PopBack();
					Assert::ExpectException<out_of_range>([&datum]() { datum.Front<glm::mat4>(); });
				}

				{
					Foo a{ 1 };
					Foo b{ 2 };
					Foo c{ 3 };
					Datum datum{ &a, &b, &c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<string>(); });
					Assert::IsTrue(&a == datum.Front<RTTI*>());
					datum.PopBack();
					datum.PopBack();
					datum.PopBack();
					Assert::ExpectException<out_of_range>([&datum]() { datum.Front<RTTI*>(); });
				}
			}

			//Const version
			{
				{
					int a = 1;
					int b = 2;
					int c = 3;
					const Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<float>(); });
					Assert::AreEqual(a, datum.Front<int>());
					
					const Datum emptyDatum{Datum::DatumTypes::Integer};
					Assert::ExpectException<out_of_range>([&emptyDatum]() { emptyDatum.Front<int>(); });
				}

				{
					float a = 1.5;
					float b = 2.5;
					float c = 3.5;
					const Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<int>(); });
					Assert::AreEqual(a, datum.Front<float>());
					
					const Datum emptyDatum{ Datum::DatumTypes::Float };
					Assert::ExpectException<out_of_range>([&emptyDatum]() { emptyDatum.Front<float>(); });
				}

				{
					string a = "hello"s;
					string b = "bye"s;
					string c = "string"s;
					const Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<glm::vec4>(); });
					Assert::AreEqual(a, datum.Front<string>());
					
					const Datum emptyDatum{ Datum::DatumTypes::String };
					Assert::ExpectException<out_of_range>([&emptyDatum]() { emptyDatum.Front<string>(); });
				}

				{
					glm::vec4 a{ 1.5 };
					glm::vec4 b{ 2.5 };
					glm::vec4 c{ 3.5 };
					const Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<glm::mat4>(); });
					Assert::IsTrue(a == datum.Front<glm::vec4>());
					
					const Datum emptyDatum{ Datum::DatumTypes::Vector };
					Assert::ExpectException<out_of_range>([&emptyDatum]() { emptyDatum.Front <glm::vec4> (); });
				}

				{
					glm::mat4 a{ 1.5 };
					glm::mat4 b{ 2.5 };
					glm::mat4 c{ 3.5 };
					const Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<RTTI*>(); });
					Assert::IsTrue(a == datum.Front<glm::mat4>());
					
					const Datum emptyDatum{ Datum::DatumTypes::Matrix };
					Assert::ExpectException<out_of_range>([&emptyDatum]() { emptyDatum.Front <glm::mat4>(); });
				}

				{
					Foo a{ 1 };
					Foo b{ 2 };
					Foo c{ 3 };
					const Datum datum{ &a, &b, &c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Front<string>(); });
					Assert::IsTrue(&a == datum.Front<RTTI*>());

					const Datum emptyDatum{Datum::DatumTypes::Pointer};
					Assert::ExpectException<out_of_range>([&emptyDatum]() { emptyDatum.Front<RTTI*>(); });
				}
			}
		}

		TEST_METHOD(Back)
		{
			//Non-const version
			{
				{
					int a = 1;
					int b = 2;
					int c = 3;
					Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<float>(); });
					Assert::AreEqual(c, datum.Back<int>());
					datum.PopBack();
					Assert::AreEqual(b, datum.Back<int>());
					datum.PopBack();
					Assert::AreEqual(a, datum.Back<int>());
					datum.PopBack();
					Assert::ExpectException<out_of_range>([&datum]() { datum.Back<int>(); });
				}

				{
					float a = 1.5;
					float b = 2.5;
					float c = 3.5;
					Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<int>(); });
					Assert::AreEqual(c, datum.Back<float>());
					datum.PopBack();
					Assert::AreEqual(b, datum.Back<float>());
					datum.PopBack();
					Assert::AreEqual(a, datum.Back<float>());
					datum.PopBack();
					Assert::ExpectException<out_of_range>([&datum]() { datum.Back<float>(); });
				}

				{
					string a = "hello"s;
					string b = "bye"s;
					string c = "string"s;
					Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<glm::vec4>(); });
					Assert::AreEqual(c, datum.Back<string>());
					datum.PopBack();
					Assert::AreEqual(b, datum.Back<string>());
					datum.PopBack();
					Assert::AreEqual(a, datum.Back<string>());
					datum.PopBack();
					Assert::ExpectException<out_of_range>([&datum]() { datum.Back<string>(); });
				}

				{
					glm::vec4 a{ 1.5 };
					glm::vec4 b{ 2.5 };
					glm::vec4 c{ 3.5 };
					Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<glm::mat4>(); });
					Assert::IsTrue(c == datum.Back<glm::vec4>());
					datum.PopBack();
					Assert::IsTrue(b == datum.Back<glm::vec4>());
					datum.PopBack();
					Assert::IsTrue(a == datum.Back<glm::vec4>());
					datum.PopBack();
					Assert::ExpectException<out_of_range>([&datum]() { datum.Back<glm::vec4>(); });
				}

				{
					glm::mat4 a{ 1.5 };
					glm::mat4 b{ 2.5 };
					glm::mat4 c{ 3.5 };
					Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<RTTI*>(); });
					Assert::IsTrue(c == datum.Back<glm::mat4>());
					datum.PopBack();
					Assert::IsTrue(b == datum.Back<glm::mat4>());
					datum.PopBack();
					Assert::IsTrue(a == datum.Back<glm::mat4>());
					datum.PopBack();
					Assert::ExpectException<out_of_range>([&datum]() { datum.Back<glm::mat4>(); });
				}

				{
					Foo a{ 1 };
					Foo b{ 2 };
					Foo c{ 3 };
					Datum datum{ &a, &b, &c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<string>(); });
					Assert::IsTrue(&c == datum.Back<RTTI*>());
					datum.PopBack();
					Assert::IsTrue(&b == datum.Back<RTTI*>());
					datum.PopBack();
					Assert::IsTrue(&a == datum.Back<RTTI*>());
					datum.PopBack();
					Assert::ExpectException<out_of_range>([&datum]() { datum.Back<RTTI*>(); });
				}
			}


			//Const version
			{
				{
					int a = 1;
					int b = 2;
					int c = 3;
					const Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<float>(); });
					Assert::AreEqual(c, datum.Back<int>());
					
					const Datum emptyDatum{ Datum::DatumTypes::Integer };
					Assert::ExpectException<out_of_range>([&emptyDatum]() { emptyDatum.Back<int>(); });
				}

				{
					float a = 1.5;
					float b = 2.5;
					float c = 3.5;
					const Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<int>(); });
					Assert::AreEqual(c, datum.Back<float>());
					
					const Datum emptyDatum{ Datum::DatumTypes::Float };
					Assert::ExpectException<out_of_range>([&emptyDatum]() { emptyDatum.Back<float>(); });
				}

				{
					string a = "hello"s;
					string b = "bye"s;
					string c = "string"s;
					const Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<glm::vec4>(); });
					Assert::AreEqual(c, datum.Back<string>());
					
					const Datum emptyDatum{ Datum::DatumTypes::String };
					Assert::ExpectException<out_of_range>([&emptyDatum]() { emptyDatum.Back<string>(); });
				}

				{
					glm::vec4 a{ 1.5 };
					glm::vec4 b{ 2.5 };
					glm::vec4 c{ 3.5 };
					const Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<glm::mat4>(); });
					Assert::IsTrue(c == datum.Back<glm::vec4>());

					const Datum emptyDatum{ Datum::DatumTypes::Vector };
					Assert::ExpectException<out_of_range>([&emptyDatum]() { emptyDatum.Back<glm::vec4>(); });
				}

				{
					glm::mat4 a{ 1.5 };
					glm::mat4 b{ 2.5 };
					glm::mat4 c{ 3.5 };
					const Datum datum{ a, b, c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<RTTI*>(); });
					Assert::IsTrue(c == datum.Back<glm::mat4>());

					const Datum emptyDatum{ Datum::DatumTypes::Matrix };
					Assert::ExpectException<out_of_range>([&emptyDatum]() { emptyDatum.Back<glm::mat4>(); });
				}

				{
					Foo a{ 1 };
					Foo b{ 2 };
					Foo c{ 3 };
					const Datum datum{ &a, &b, &c };

					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<Foo>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Back<string>(); });
					Assert::IsTrue(&c == datum.Back<RTTI*>());

					const Datum emptyDatum{ Datum::DatumTypes::Pointer };
					Assert::ExpectException<out_of_range>([&emptyDatum]() { emptyDatum.Back<RTTI*>(); });
				}
			}
		}

		TEST_METHOD(Get)
		{
			//Non-const version
			{
				{
					int a = 1;
					int b = 2;
					int c = 3;
					Datum datum{ a, b, c };

					Assert::AreEqual(a, datum.Get<int>());
					Assert::AreEqual(b, datum.Get<int>(1));
					Assert::AreEqual(c, datum.Get<int>(2));

					Assert::ExpectException<out_of_range>([&datum]() { datum.Get<int>(3); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Get<float>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Get<Foo>(); });
				}

				{
					float a = 1.5;
					float b = 2.5;
					float c = 3.5;
					Datum datum{ a, b, c };

					Assert::AreEqual(a, datum.Get<float>());
					Assert::AreEqual(b, datum.Get<float>(1));
					Assert::AreEqual(c, datum.Get<float>(2));

					Assert::ExpectException<out_of_range>([&datum]() { datum.Get<float>(3); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Get<int>(); });

				}

				{
					string a = "hello"s;
					string b = "bye"s;
					string c = "string"s;
					Datum datum{ a, b, c };

					Assert::AreEqual(a, datum.Get<string>());
					Assert::AreEqual(b, datum.Get<string>(1));
					Assert::AreEqual(c, datum.Get<string>(2));

					Assert::ExpectException<out_of_range>([&datum]() { datum.Get<string>(3); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Get<glm::vec4>(); });
				}

				{
					glm::vec4 a{ 1.5 };
					glm::vec4 b{ 2.5 };
					glm::vec4 c{ 3.5 };
					Datum datum{ a, b, c };

					Assert::IsTrue(a == datum.Get<glm::vec4>());
					Assert::IsTrue(b == datum.Get<glm::vec4>(1));
					Assert::IsTrue(c == datum.Get<glm::vec4>(2));

					Assert::ExpectException<out_of_range>([&datum]() { datum.Get<glm::vec4>(3); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Get<glm::mat4>(); });
				}

				{
					glm::mat4 a{ 1.5 };
					glm::mat4 b{ 2.5 };
					glm::mat4 c{ 3.5 };
					Datum datum{ a, b, c };

					Assert::IsTrue(a == datum.Get<glm::mat4>());
					Assert::IsTrue(b == datum.Get<glm::mat4>(1));
					Assert::IsTrue(c == datum.Get<glm::mat4>(2));

					Assert::ExpectException<out_of_range>([&datum]() { datum.Get<glm::mat4>(3); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Get<RTTI*>(); });
				}

				{
					Foo a{ 1 };
					Foo b{ 2 };
					Foo c{ 3 };
					Datum datum{ &a, &b, &c };

					Assert::IsTrue(&a == datum.Get<RTTI*>());
					Assert::IsTrue(&b == datum.Get<RTTI*>(1));
					Assert::IsTrue(&c == datum.Get<RTTI*>(2));

					Assert::ExpectException<out_of_range>([&datum]() { datum.Get<RTTI*>(3); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Get<string>(); });
				}
			}

			//Const version
			{
				{
					int a = 1;
					int b = 2;
					int c = 3;
					const Datum datum{ a, b, c };

					Assert::AreEqual(a, datum.Get<int>());
					Assert::AreEqual(b, datum.Get<int>(1));
					Assert::AreEqual(c, datum.Get<int>(2));

					Assert::ExpectException<out_of_range>([&datum]() { datum.Get<int>(3); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Get<float>(); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Get<Foo>(); });
				}

				{
					float a = 1.5;
					float b = 2.5;
					float c = 3.5;
					const Datum datum{ a, b, c };

					Assert::AreEqual(a, datum.Get<float>());
					Assert::AreEqual(b, datum.Get<float>(1));
					Assert::AreEqual(c, datum.Get<float>(2));

					Assert::ExpectException<out_of_range>([&datum]() { datum.Get<float>(3); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Get<int>(); });

				}

				{
					string a = "hello"s;
					string b = "bye"s;
					string c = "string"s;
					const Datum datum{ a, b, c };

					Assert::AreEqual(a, datum.Get<string>());
					Assert::AreEqual(b, datum.Get<string>(1));
					Assert::AreEqual(c, datum.Get<string>(2));

					Assert::ExpectException<out_of_range>([&datum]() { datum.Get<string>(3); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Get<glm::vec4>(); });
				}

				{
					glm::vec4 a{ 1.5 };
					glm::vec4 b{ 2.5 };
					glm::vec4 c{ 3.5 };
					const Datum datum{ a, b, c };

					Assert::IsTrue(a == datum.Get<glm::vec4>());
					Assert::IsTrue(b == datum.Get<glm::vec4>(1));
					Assert::IsTrue(c == datum.Get<glm::vec4>(2));

					Assert::ExpectException<out_of_range>([&datum]() { datum.Get<glm::vec4>(3); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Get<glm::mat4>(); });
				}

				{
					glm::mat4 a{ 1.5 };
					glm::mat4 b{ 2.5 };
					glm::mat4 c{ 3.5 };
					const Datum datum{ a, b, c };

					Assert::IsTrue(a == datum.Get<glm::mat4>());
					Assert::IsTrue(b == datum.Get<glm::mat4>(1));
					Assert::IsTrue(c == datum.Get<glm::mat4>(2));

					Assert::ExpectException<out_of_range>([&datum]() { datum.Get<glm::mat4>(3); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Get<RTTI*>(); });
				}

				{
					Foo a{ 1 };
					Foo b{ 2 };
					Foo c{ 3 };
					const Datum datum{ &a, &b, &c };

					Assert::IsTrue(&a == datum.Get<RTTI*>());
					Assert::IsTrue(&b == datum.Get<RTTI*>(1));
					Assert::IsTrue(&c == datum.Get<RTTI*>(2));

					Assert::ExpectException<out_of_range>([&datum]() { datum.Get<RTTI*>(3); });
					Assert::ExpectException<runtime_error>([&datum]() { datum.Get<string>(); });
				}
			}
		}

		//TODO: Figure out if Set should work on external storage
		TEST_METHOD(Set)
		{
			int z = 10;
			{
				int a = 1;
				int b = 2;
				int c = 3;
				Datum datum{ a, b, c };

				Assert::AreEqual(a, datum.Front<int>());
				Assert::AreEqual(c, datum.Back<int>());
				datum.Set(b, 0);
				datum.Set(a, 2);
				Assert::AreEqual(b, datum.Front<int>());
				Assert::AreEqual(a, datum.Back<int>());
				Assert::ExpectException<out_of_range>([&datum, &c]() { datum.Set(c, 3); });
				Assert::ExpectException<runtime_error>([&datum]() { datum.Set(7.5f, 1); });
			}

			{
				float a = 1.5;
				float b = 2.5;
				float c = 3.5;
				Datum datum{ a, b, c };

				Assert::AreEqual(a, datum.Front<float>());
				Assert::AreEqual(c, datum.Back<float>());
				datum.Set(b, 0);
				datum.Set(a, 2);
				Assert::AreEqual(b, datum.Front<float>());
				Assert::AreEqual(a, datum.Back<float>());
				Assert::ExpectException<out_of_range>([&datum, &c]() { datum.Set(c, 3); });
				Assert::ExpectException<runtime_error>([&datum, &z]() { datum.Set(z, 1); });
			}

			{
				string a = "hello"s;
				string b = "bye"s;
				string c = "string"s;
				Datum datum{ a, b, c };

				Assert::AreEqual(a, datum.Front<string>());
				Assert::AreEqual(c, datum.Back<string>());
				datum.Set(b, 0);
				datum.Set(a, 2);
				Assert::AreEqual(b, datum.Front<string>());
				Assert::AreEqual(a, datum.Back<string>());
				Assert::ExpectException<out_of_range>([&datum, &c]() { datum.Set(c, 3); });
				Assert::ExpectException<runtime_error>([&datum]() { datum.Set(glm::vec4{5.5f}, 1); });
			}

			{
				glm::vec4 a{ 1.5 };
				glm::vec4 b{ 2.5 };
				glm::vec4 c{ 3.5 };
				Datum datum{ a, b, c };

				Assert::IsTrue(a == datum.Front<glm::vec4>());
				Assert::IsTrue(c == datum.Back<glm::vec4>());
				datum.Set(b, 0);
				datum.Set(a, 2);
				Assert::IsTrue(b == datum.Front<glm::vec4>());
				Assert::IsTrue(a == datum.Back<glm::vec4>());
				Assert::ExpectException<out_of_range>([&datum, &c]() { datum.Set(c, 3); });
				Assert::ExpectException<runtime_error>([&datum]() { datum.Set(glm::mat4{ 5.5f }, 1); });
			}

			{
				glm::mat4 a{ 1.5 };
				glm::mat4 b{ 2.5 };
				glm::mat4 c{ 3.5 };
				Datum datum{ a, b, c };

				Assert::IsTrue(a == datum.Front<glm::mat4>());
				Assert::IsTrue(c == datum.Back<glm::mat4>());
				datum.Set(b, 0);
				datum.Set(a, 2);
				Assert::IsTrue(b == datum.Front<glm::mat4>());
				Assert::IsTrue(a == datum.Back<glm::mat4>());
				Assert::ExpectException<out_of_range>([&datum, &c]() { datum.Set(c, 3); });

				Foo foo{ 5 };
				Assert::ExpectException<runtime_error>([&datum, &foo]() { datum.Set(&foo, 1); });
			}

			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Datum datum{ &a, &b, &c };

				Assert::IsTrue(&a == datum.Front<RTTI*>());
				Assert::IsTrue(&c == datum.Back<RTTI*>());
				datum.Set(&b, 0);
				datum.Set(&a, 2);
				Assert::IsTrue(&b == datum.Front<RTTI*>());
				Assert::IsTrue(&a == datum.Back<RTTI*>());
				Assert::ExpectException<out_of_range>([&datum, &c]() { datum.Set(&c, 3); });
				Assert::ExpectException<runtime_error>([&datum, &z]() { datum.Set("string"s, 1); });
			}
		}

		TEST_METHOD(Find)
		{
			int z = 10;
			{
				int a = 1;
				int b = 2;
				int c = 3;
				int d = 4;
				Datum datum{ a, b, c };

				Assert::AreEqual(size_t(1), datum.Find(b));
				Assert::AreEqual(datum.Size(), datum.Find(d));
				Assert::ExpectException<runtime_error>([&datum]() { datum.Find(7.5f); });
			}

			{

				float a = 1.5;
				float b = 2.5;
				float c = 3.5;
				float d = 4.5;
				Datum datum{ a, b, c };

				Assert::AreEqual(size_t(1), datum.Find(b));
				Assert::AreEqual(datum.Size(), datum.Find(d));
				Assert::ExpectException<runtime_error>([&datum, &z]() { datum.Find(z); });
			}

			{
				string a = "hello"s;
				string b = "bye"s;
				string c = "string"s;
				string d = "bogus"s;
				Datum datum{ a, b, c };

				Assert::AreEqual(size_t(1), datum.Find(b));
				Assert::AreEqual(datum.Size(), datum.Find(d));
				Assert::ExpectException<runtime_error>([&datum]() { datum.Find(glm::vec4{5.5f}); });
			}

			{
				glm::vec4 a{ 1.5 };
				glm::vec4 b{ 2.5 };
				glm::vec4 c{ 3.5 };
				glm::vec4 d{ 4.5 };
				Datum datum{ a, b, c };

				Assert::AreEqual(size_t(1), datum.Find(b));
				Assert::AreEqual(datum.Size(), datum.Find(d));
				Assert::ExpectException<runtime_error>([&datum]() { datum.Find(glm::mat4{ 5.5f }); });
			}

			{
				glm::mat4 a{ 1.5 };
				glm::mat4 b{ 2.5 };
				glm::mat4 c{ 3.5 };
				glm::mat4 d{ 4.5 };
				Datum datum{ a, b, c };

				Assert::AreEqual(size_t(1), datum.Find(b));
				Assert::AreEqual(datum.Size(), datum.Find(d));

				Foo foo{ 5 };
				Assert::ExpectException<runtime_error>([&datum, &foo]() { datum.Find(&foo); });
			}

			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Foo d{ 4 };
				Datum datum{ &a, &b, &c };

				Assert::AreEqual(size_t(1), datum.Find(&b));
				Assert::AreEqual(datum.Size(), datum.Find(&d));
				Assert::ExpectException<runtime_error>([&datum]() { datum.Find("hello"s); });
			}
		}

		TEST_METHOD(Remove)
		{
			{
				int a = 1;
				int b = 2;
				int c = 3;
				int d = 4;
				Datum datum{ a, b, c };

				Assert::IsTrue(datum.Remove(b));
				Assert::AreEqual(datum.Size(), datum.Find(b));
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::AreEqual(a, datum.Front<int>());
				Assert::AreEqual(c, datum.Back<int>());
				Assert::ExpectException<out_of_range>([&datum, &d]() { datum.Remove(d); });

				Datum newDatum;
				Assert::ExpectException<runtime_error>([&newDatum, &a]() { newDatum.Remove(a); });
			}

			{
				float a = 1.5;
				float b = 2.5;
				float c = 3.5;
				float d = 4.5;
				Datum datum{ a, b, c };

				Assert::IsTrue(datum.Remove(b));
				Assert::AreEqual(datum.Size(), datum.Find(b));
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::AreEqual(a, datum.Front<float>());
				Assert::AreEqual(c, datum.Back<float>());
				Assert::ExpectException<out_of_range>([&datum, &d]() { datum.Remove(d); });

				Datum newDatum;
				Assert::ExpectException<runtime_error>([&newDatum, &a]() { newDatum.Remove(a); });
			}

			{
				string a = "hello"s;
				string b = "bye"s;
				string c = "string"s;
				string d = "bogus"s;
				Datum datum{ a, b, c };

				Assert::IsTrue(datum.Remove(b));
				Assert::AreEqual(datum.Size(), datum.Find(b));
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::AreEqual(a, datum.Front<std::string>());
				Assert::AreEqual(c, datum.Back<std::string>());
				Assert::ExpectException<out_of_range>([&datum, &d]() { datum.Remove(d); });

				Datum newDatum;
				Assert::ExpectException<runtime_error>([&newDatum, &a]() { newDatum.Remove(a); });
			}

			{
				glm::vec4 a{ 1.5 };
				glm::vec4 b{ 2.5 };
				glm::vec4 c{ 3.5 };
				glm::vec4 d{ 4.5 };
				Datum datum{ a, b, c };

				Assert::IsTrue(datum.Remove(b));
				Assert::AreEqual(datum.Size(), datum.Find(b));
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::IsTrue(a == datum.Front<glm::vec4>());
				Assert::IsTrue(c == datum.Back<glm::vec4>());
				Assert::ExpectException<out_of_range>([&datum, &d]() { datum.Remove(d); });

				Datum newDatum;
				Assert::ExpectException<runtime_error>([&newDatum, &a]() { newDatum.Remove(a); });
			}

			{
				glm::mat4 a{ 1.5 };
				glm::mat4 b{ 2.5 };
				glm::mat4 c{ 3.5 };
				glm::mat4 d{ 4.5 };
				Datum datum{ a, b, c };

				Assert::IsTrue(datum.Remove(b));
				Assert::AreEqual(datum.Size(), datum.Find(b));
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::IsTrue(a == datum.Front<glm::mat4>());
				Assert::IsTrue(c == datum.Back<glm::mat4>());
				Assert::ExpectException<out_of_range>([&datum, &d]() { datum.Remove(d); });

				Datum newDatum;
				Assert::ExpectException<runtime_error>([&newDatum, &a]() { newDatum.Remove(a); });
			}

			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Foo d{ 4 };
				Datum datum{ &a, &b, &c };

				Assert::IsTrue(datum.Remove(&b));
				Assert::AreEqual(datum.Size(), datum.Find(&b));
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::IsTrue(&a == datum.Front<RTTI*>());
				Assert::IsTrue(&c == datum.Back<RTTI*>());
				Assert::ExpectException<out_of_range>([&datum, &d]() { datum.Remove(&d); });

				Datum newDatum;
				Assert::ExpectException<runtime_error>([&newDatum, &a]() { newDatum.Remove(&a); });
			}
		}

		TEST_METHOD(RemoveAt)
		{
			{
				int a = 1;
				int b = 2;
				int c = 3;
				Datum datum{ a, b, c };

				Assert::IsTrue(datum.RemoveAt(1));
				Assert::AreEqual(datum.Size(), datum.Find(b));
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::AreEqual(a, datum.Front<int>());
				Assert::AreEqual(c, datum.Back<int>());
				Assert::ExpectException<out_of_range>([&datum]() { datum.RemoveAt(3); });
			}

			{
				float a = 1.5;
				float b = 2.5;
				float c = 3.5;
				Datum datum{ a, b, c };

				Assert::IsTrue(datum.RemoveAt(1));
				Assert::AreEqual(datum.Size(), datum.Find(b));
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::AreEqual(a, datum.Front<float>());
				Assert::AreEqual(c, datum.Back<float>());
				Assert::ExpectException<out_of_range>([&datum]() { datum.RemoveAt(3); });
			}

			{
				string a = "hello"s;
				string b = "bye"s;
				string c = "string"s;
				Datum datum{ a, b, c };

				Assert::IsTrue(datum.RemoveAt(1));
				Assert::AreEqual(datum.Size(), datum.Find(b));
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::AreEqual(a, datum.Front<string>());
				Assert::AreEqual(c, datum.Back<string>());
				Assert::ExpectException<out_of_range>([&datum]() { datum.RemoveAt(3); });
			}

			{
				glm::vec4 a{ 1.5 };
				glm::vec4 b{ 2.5 };
				glm::vec4 c{ 3.5 };
				Datum datum{ a, b, c };

				Assert::IsTrue(datum.RemoveAt(1));
				Assert::AreEqual(datum.Size(), datum.Find(b));
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::IsTrue(a == datum.Front<glm::vec4>());
				Assert::IsTrue(c == datum.Back<glm::vec4>());
				Assert::ExpectException<out_of_range>([&datum]() { datum.RemoveAt(3); });
			}

			{
				glm::mat4 a{ 1.5 };
				glm::mat4 b{ 2.5 };
				glm::mat4 c{ 3.5 };
				Datum datum{ a, b, c };

				Assert::IsTrue(datum.RemoveAt(1));
				Assert::AreEqual(datum.Size(), datum.Find(b));
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::IsTrue(a == datum.Front<glm::mat4>());
				Assert::IsTrue(c == datum.Back<glm::mat4>());
				Assert::ExpectException<out_of_range>([&datum]() { datum.RemoveAt(3); });
			}

			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Datum datum{ &a, &b, &c };

				Assert::IsTrue(datum.RemoveAt(1));
				Assert::AreEqual(datum.Size(), datum.Find(&b));
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::IsTrue(&a == datum.Front<RTTI*>());
				Assert::IsTrue(&c == datum.Back<RTTI*>());
				Assert::ExpectException<out_of_range>([&datum]() { datum.RemoveAt(3); });
			}
			Datum datum;
			Assert::ExpectException<runtime_error>([&datum]() { datum.RemoveAt(0); });
		}

		//TODO: Test against external
		TEST_METHOD(Clear)
		{
			{
				int a = 1;
				int b = 2;
				int c = 3;
				Datum datum{ a, b, c };
				size_t originalCapacity = datum.Capacity();

				datum.Clear();
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::AreEqual(originalCapacity, datum.Capacity());
			}

			{
				float a = 1.5;
				float b = 2.5;
				float c = 3.5;
				Datum datum{ a, b, c };
				size_t originalCapacity = datum.Capacity();

				datum.Clear();
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::AreEqual(originalCapacity, datum.Capacity());
			}

			{
				string a = "hello"s;
				string b = "bye"s;
				string c = "string"s;
				Datum datum{ a, b, c };
				size_t originalCapacity = datum.Capacity();

				datum.Clear();
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::AreEqual(originalCapacity, datum.Capacity());
			}

			{
				glm::vec4 a{ 1.5 };
				glm::vec4 b{ 2.5 };
				glm::vec4 c{ 3.5 };
				Datum datum{ a, b, c };
				size_t originalCapacity = datum.Capacity();

				datum.Clear();
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::AreEqual(originalCapacity, datum.Capacity());
			}

			{
				glm::mat4 a{ 1.5 };
				glm::mat4 b{ 2.5 };
				glm::mat4 c{ 3.5 };
				Datum datum{ a, b, c };
				size_t originalCapacity = datum.Capacity();

				datum.Clear();
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::AreEqual(originalCapacity, datum.Capacity());
			}

			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Datum datum{ &a, &b, &c };
				size_t originalCapacity = datum.Capacity();

				datum.Clear();
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::AreEqual(originalCapacity, datum.Capacity());
			}
		}

		TEST_METHOD(Resize)
		{
			{
				int a = 1;
				int b = 2;
				int c = 3;
				Datum datum{ a, b, c };

				
				datum.Resize(4);
				Assert::AreEqual(int{}, datum.Back<int>());
				Assert::AreEqual(size_t(4), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());

				datum.Resize(2);
				Assert::AreEqual(b, datum.Back<int>());
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());

				datum.Resize(0);
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());
			}

			{
				float a = 1.5;
				float b = 2.5;
				float c = 3.5;
				Datum datum{ a, b, c };

				datum.Resize(4);
				Assert::AreEqual(float{}, datum.Back<float>());
				Assert::AreEqual(size_t(4), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());

				datum.Resize(2);
				Assert::AreEqual(b, datum.Back<float>());
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());

				datum.Resize(0);
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());
			}

			{
				string a = "hello"s;
				string b = "bye"s;
				string c = "string"s;
				Datum datum{ a, b, c };

				datum.Resize(4);
				Assert::AreEqual(string{}, datum.Back<string>());
				Assert::AreEqual(size_t(4), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());

				datum.Resize(2);
				Assert::AreEqual(b, datum.Back<string>());
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());

				datum.Resize(0);
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());
			}

			{
				glm::vec4 a{ 1.5 };
				glm::vec4 b{ 2.5 };
				glm::vec4 c{ 3.5 };
				Datum datum{ a, b, c };

				datum.Resize(4);
				Assert::IsTrue(glm::vec4{} == datum.Back<glm::vec4>());
				Assert::AreEqual(size_t(4), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());

				datum.Resize(2);
				Assert::IsTrue(b == datum.Back<glm::vec4>());
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());

				datum.Resize(0);
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());
			}

			{
				glm::mat4 a{ 1.5 };
				glm::mat4 b{ 2.5 };
				glm::mat4 c{ 3.5 };
				Datum datum{ a, b, c };

				datum.Resize(4);
				Assert::IsTrue(glm::mat4{} == datum.Back<glm::mat4>());
				Assert::AreEqual(size_t(4), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());

				datum.Resize(2);
				Assert::IsTrue(b == datum.Back<glm::mat4>());
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());

				datum.Resize(0);
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());
			}

			{
				Foo a{ 1 };
				Foo b{ 2 };
				Foo c{ 3 };
				Datum datum{ &a, &b, &c };

				datum.Resize(4);
				Assert::IsTrue(nullptr == datum.Back<RTTI*>());
				Assert::AreEqual(size_t(4), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());

				datum.Resize(2);
				Assert::IsTrue(&b == datum.Back<RTTI*>());
				Assert::AreEqual(size_t(2), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());

				datum.Resize(0);
				Assert::AreEqual(size_t(0), datum.Size());
				Assert::AreEqual(datum.Capacity(), datum.Size());
			}

			Datum datum;
			Assert::ExpectException<runtime_error>([&datum]() { datum.Resize(10); });
		}

		TEST_METHOD(ToString)
		{
			{
				Datum d = 5;
				Assert::AreEqual("5"s, d.ToString());
			}

			{
				Datum d = 5.5f;
				Assert::AreEqual("5.50"s, d.ToString());
			}

			{
				Datum d = "hello"s;
				Assert::AreEqual("hello"s, d.ToString());
			}

			{
				Datum d = glm::vec4{ 1.5f, 2.5f, 3.5f, 4.5f };
				Assert::AreEqual("vec4(1.50, 2.50, 3.50, 4.50)"s, d.ToString());
			}

			{
				glm::vec4 vec1{ 1.5f, 2.5f, 3.5f, 4.5f };
				glm::vec4 vec2{ 5.5f, 6.5f, 7.5f, 8.5f };
				glm::vec4 vec3{ 9.5f, 10.5f, 11.5f, 12.5f };
				glm::vec4 vec4{ 13.5f, 14.5f, 15.5f, 16.5f };
				Datum d = glm::mat4{ vec1, vec2, vec3, vec4 };

				Assert::AreEqual("mat4(1.50, 2.50, 3.50, 4.50\n 5.50, 6.50, 7.50, 8.50\n 9.50, 10.50, 11.50, 12.50\n 13.50, 14.50, 15.50, 16.50)"s, d.ToString());
			}

			{
				Foo f1{ 5 };
				Datum d = &f1;
				Assert::AreEqual("5"s, d.ToString());
			}

			Datum d{ Datum::DatumTypes::Integer };
			Assert::ExpectException<out_of_range>([&d]() {d.ToString(); });
		}

		TEST_METHOD(SetFromString)
		{
			{
				Datum d = 1;
				d.Reserve(3);
				d.SetIntFromString("5"s);
				Assert::AreEqual(5, d.Front<int>());
			}

			{
				Datum d = 1.5f;
				d.Reserve(3);
				d.SetFloatFromString("5.50"s);
				Assert::AreEqual(5.5f, d.Front<float>());
			}

			{
				Datum d = glm:: vec4{ 1.5f };
				d.Reserve(3);
				d.SetVecFromString("vec4(5.50, 6.50, 7.50, 8.50)"s);
				Assert::IsTrue(glm::vec4{ 5.5f, 6.5f, 7.5f, 8.5f} == d.Front<glm::vec4>());
			}

			{
				Datum d = glm::mat4{ 0.5f };
				d.Reserve(3);
				d.SetMatFromString("mat4(1.50, 2.50, 3.50, 4.50\n 5.50, 6.50, 7.50, 8.50\n 9.50, 10.50, 11.50, 12.50\n 13.50, 14.50, 15.50, 16.50)"s);
				Assert::IsTrue(glm::mat4{ glm::vec4{1.50, 2.50, 3.50, 4.50}, glm::vec4{5.50, 6.50, 7.50, 8.50}, glm::vec4{9.50, 10.50, 11.50, 12.50}, glm::vec4{13.50, 14.50, 15.50, 16.50} } == d.Front<glm::mat4>());
			}
		}

		TEST_METHOD(EqualsOperators)
		{
			{
				Datum d = 5;
				
				Assert::IsFalse(d == 10);
				Assert::IsFalse(d == 10.5f);
				Assert::IsTrue(d == 5);

				d.PushBack(10);
				Assert::IsFalse(d == 5);
				Assert::IsFalse(d == 10);
			}

			{
				Datum d = 5.5f;

				Assert::IsFalse(d == 10.5f);
				Assert::IsFalse(d == "string"s);
				Assert::IsTrue(d == 5.5f);

				d.PushBack(10.5f);
				Assert::IsFalse(d == 5.5f);
				Assert::IsFalse(d == 10.5f);
			}

			{
				Datum d = "string"s;

				Assert::IsFalse(d == "hello"s);
				Assert::IsFalse(d == 10);
				Assert::IsTrue(d == "string"s);

				d.PushBack("hello"s);
				Assert::IsFalse(d == "string"s);
				Assert::IsFalse(d == "hello"s);
			}

			{
				Datum d = glm::vec4{ 5.5f };

				Assert::IsFalse(d == glm::vec4{ 10.5f });
				Assert::IsFalse(d == "string"s);
				Assert::IsTrue(d == glm::vec4{ 5.5f });

				d.PushBack(glm::vec4{ 10.5f });
				Assert::IsFalse(d == glm::vec4{ 5.5f });
				Assert::IsFalse(d == glm::vec4{ 10.5f });
			}

			{
				Datum d = glm::mat4{ 5.5f };

				Assert::IsFalse(d == glm::mat4{ 10.5f });
				Assert::IsFalse(d == "string"s);
				Assert::IsTrue(d == glm::mat4{ 5.5f });

				d.PushBack(glm::mat4{ 10.5f });
				Assert::IsFalse(d == glm::mat4{ 5.5f });
				Assert::IsFalse(d == glm::mat4{ 10.5f });
			}

			{
				Foo a{ 1 };
				Foo b{ 2 };
				Datum d = &a;

				Assert::IsFalse(d == &b);
				Assert::IsFalse(d == "string"s);
				Assert::IsTrue(d == &a);

				d.PushBack(&b);
				Assert::IsFalse(d == &a);
				Assert::IsFalse(d == &b);
			}
		}

	private:
		inline static _CrtMemState _startMemState;
	};
}