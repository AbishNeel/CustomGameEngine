#include "pch.h"
#include "Foo.h"

using namespace std;

namespace UnitTests
{
	RTTI_DEFINITIONS(Foo);

	Foo::Foo(int32_t data) : _data{ new int32_t(data) }
	{

	}

	Foo::~Foo()
	{
		delete(_data);
	}

	Foo::Foo(const Foo& other) : _data{ new int32_t(*other._data) }
	{

	}

	Foo::Foo(Foo&& other) noexcept : _data{ other._data }
	{
		other._data = nullptr;
	}

	Foo& Foo::operator=(const Foo& rhs)
	{
		if (this != &rhs)
			*_data = *rhs._data;

		return *this;
	}

	Foo& Foo::operator=(Foo&& rhs) noexcept
	{
		if (this != &rhs)
		{
			delete(_data);
			_data = rhs._data;
			rhs._data = nullptr;
		}

		return *this;
	}

	bool Foo::operator==(const Foo& rhs) const
	{
		return *_data == *rhs._data;
	}

	bool Foo::operator!=(const Foo& rhs) const
	{
		return !operator==(rhs);
	}

	bool Foo::Equals(const RTTI* rhs) const
	{
		if (rhs == nullptr)
			return false;

		const Foo* other = rhs->As<Foo>();
		return (other != nullptr ? *this == *other : false);
	}

	string Foo::ToString() const
	{
		assert(_data != nullptr);
		return to_string(*_data);
	}

	int32_t Foo::Data() const
	{
		return *_data;
	}

	void Foo::SetData(int32_t data)
	{
		*_data = data;
	}
}