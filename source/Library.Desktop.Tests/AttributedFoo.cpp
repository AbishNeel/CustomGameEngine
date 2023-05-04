#include "pch.h"
#include "AttributedFoo.h"

using namespace FieaGameEngine;
using namespace std;

namespace UnitTests
{
	RTTI_DEFINITIONS(AttributedFoo);

	AttributedFoo::AttributedFoo()
		: Attributed(AttributedFoo::TypeIdClass())
	{

	}

	AttributedFoo::AttributedFoo(IdType typeID)
		: Attributed(typeID)
	{

	}

	Vector<Signature> AttributedFoo::Signatures()
	{
		return Vector<Signature>
		{
			{ "ExternalInteger", Datum::DatumTypes::Integer, 1, offsetof(AttributedFoo, ExternalInteger)},
			{ "ExternalFloat", Datum::DatumTypes::Float, 1, offsetof(AttributedFoo, ExternalFloat)},
			{ "ExternalString", Datum::DatumTypes::String, 1, offsetof(AttributedFoo, ExternalString)},
			{ "ExternalVector", Datum::DatumTypes::Vector, 1, offsetof(AttributedFoo, ExternalVector)},
			{ "ExternalMatrix", Datum::DatumTypes::Matrix, 1, offsetof(AttributedFoo, ExternalMatrix)},
			{ "ExternalIntegerArray", Datum::DatumTypes::Integer, ArraySize, offsetof(AttributedFoo, ExternalIntegerArray) },
			{ "ExternalFloatArray", Datum::DatumTypes::Float, ArraySize, offsetof(AttributedFoo, ExternalFloatArray) },
			{ "ExternalStringArray", Datum::DatumTypes::String, ArraySize, offsetof(AttributedFoo, ExternalStringArray) },
			{ "ExternalVectorArray", Datum::DatumTypes::Vector, ArraySize, offsetof(AttributedFoo, ExternalVectorArray) },
			{ "ExternalMatrixArray", Datum::DatumTypes::Matrix, ArraySize, offsetof(AttributedFoo, ExternalMatrixArray) },
			{ "NestedScope", Datum::DatumTypes::Table, 0, 0},
			{ "NestedScopeArray", Datum::DatumTypes::Table, ArraySize, 0}
		};
	}

	AttributedFoo* AttributedFoo::Clone() const
	{
		return new AttributedFoo{ *this };
	}

	bool AttributedFoo::Equals(const RTTI* rhs) const
	{
		if (rhs == nullptr)
			return false;

		const AttributedFoo* other = rhs->As<AttributedFoo>();

		return ExternalInteger == other->ExternalInteger
			&& ExternalFloat == other->ExternalFloat
			&& ExternalString == other->ExternalString
			&& ExternalVector == other->ExternalVector
			&& ExternalMatrix == other->ExternalMatrix
			&& std::equal(std::begin(ExternalIntegerArray), std::end(ExternalIntegerArray), std::begin(other->ExternalIntegerArray), std::end(other->ExternalIntegerArray))
			&& std::equal(std::begin(ExternalFloatArray), std::end(ExternalFloatArray), std::begin(other->ExternalFloatArray), std::end(other->ExternalFloatArray))
			&& std::equal(std::begin(ExternalStringArray), std::end(ExternalStringArray), std::begin(other->ExternalStringArray), std::end(other->ExternalStringArray))
			&& std::equal(std::begin(ExternalVectorArray), std::end(ExternalVectorArray), std::begin(other->ExternalVectorArray), std::end(other->ExternalVectorArray))
			&& std::equal(std::begin(ExternalMatrixArray), std::end(ExternalMatrixArray), std::begin(other->ExternalMatrixArray), std::end(other->ExternalMatrixArray));
	}
}