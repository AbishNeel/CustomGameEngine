#pragma once

#include "CppUnitTest.h"
#include "Foo.h"

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<>
	inline std::wstring ToString<UnitTests::Foo>(const UnitTests::Foo& t)
	{
		RETURN_WIDE_STRING(t.Data());
	}

	template<>
	inline std::wstring ToString<UnitTests::Foo>(const UnitTests::Foo* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<UnitTests::Foo>(UnitTests::Foo* t)
	{
		RETURN_WIDE_STRING(t);
	}

	template<>
	inline std::wstring ToString<std::pair<const UnitTests::Foo, UnitTests::Foo>>(const std::pair<const UnitTests::Foo, UnitTests::Foo>& t)
	{
		std::wstring s = ToString(t.first) + ToString(t.second);
		RETURN_WIDE_STRING(s);
	}
}