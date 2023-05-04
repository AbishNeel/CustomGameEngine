#include "pch.h"
#include "AttributedBar.h"

using namespace FieaGameEngine;
using namespace std;

namespace UnitTests
{
	RTTI_DEFINITIONS(AttributedBar);

	AttributedBar::AttributedBar()
		: AttributedFoo(AttributedBar::TypeIdClass())
	{

	}

	Vector<Signature> AttributedBar::Signatures()
	{
		return Vector<Signature>
		{
			{ "ExternalInteger", Datum::DatumTypes::Integer, 1, offsetof(AttributedFoo, ExternalInteger)},
			{ "ExternalFloat", Datum::DatumTypes::Float, 1, offsetof(AttributedFoo, ExternalFloat) },
			{ "ExternalString", Datum::DatumTypes::String, 1, offsetof(AttributedFoo, ExternalString) }
		};
	}

	AttributedBar* AttributedBar::Clone() const
	{
		return new AttributedBar{ *this };
	}

	bool AttributedBar::Equals(const RTTI* rhs) const
	{
		if (rhs == nullptr)
			return false;

		const AttributedBar* other = rhs->As<AttributedBar>();

		return ExternalInteger == other->ExternalInteger
			&& ExternalFloat == other->ExternalFloat
			&& ExternalString == other->ExternalString;
	}
}