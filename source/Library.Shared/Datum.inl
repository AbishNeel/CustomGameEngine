#include "Datum.h"

namespace FieaGameEngine
{
	inline Datum::DatumTypes Datum::Type() const
	{
		return _type;
	}

	inline size_t Datum::Size() const
	{
		return _size;
	}

	inline size_t Datum::Capacity() const
	{
		return _capacity;
	}

	inline bool Datum::IsExternal() const
	{
		return _IsExternal;
	}

	template<typename T>
	inline T& Datum::Front()
	{
		throw std::runtime_error("Datum does not support this type.");
	}

	template<>
	inline int& Datum::Front()
	{
		ValidateType(DatumTypes::Integer);
		ValidateIndex(0);

		return _data.i[0];
	}

	template<>
	inline float& Datum::Front()
	{
		ValidateType(DatumTypes::Float);
		ValidateIndex(0);

		return _data.f[0];
	}

	template<>
	inline std::string& Datum::Front()
	{
		ValidateType(DatumTypes::String);
		ValidateIndex(0);

		return _data.s[0];
	}

	template<>
	inline glm::vec4& Datum::Front()
	{
		ValidateType(DatumTypes::Vector);
		ValidateIndex(0);

		return _data.v[0];
	}

	template<>
	inline glm::mat4& Datum::Front()
	{
		ValidateType(DatumTypes::Matrix);
		ValidateIndex(0);

		return _data.m[0];
	}

	template<>
	inline RTTI*& Datum::Front()
	{
		ValidateType(DatumTypes::Pointer);
		ValidateIndex(0);

		return _data.p[0];
	}

	template<>
	inline Scope*& Datum::Front()
	{
		ValidateType(DatumTypes::Table);
		ValidateIndex(0);

		return _data.t[0];
	}

	template<typename T>
	inline T& Datum::Back()
	{
		throw std::runtime_error("Datum does not support this type.");
	}

	template<>
	inline int& Datum::Back()
	{
		ValidateType(DatumTypes::Integer);
		ValidateIndex(0);

		return _data.i[_size - 1];
	}

	template<>
	inline float& Datum::Back()
	{
		ValidateType(DatumTypes::Float);
		ValidateIndex(0);

		return _data.f[_size - 1];
	}

	template<>
	inline std::string& Datum::Back()
	{
		ValidateType(DatumTypes::String);
		ValidateIndex(0);

		return _data.s[_size - 1];
	}

	template<>
	inline glm::vec4& Datum::Back()
	{
		ValidateType(DatumTypes::Vector);
		ValidateIndex(0);

		return _data.v[_size - 1];
	}

	template<>
	inline glm::mat4& Datum::Back()
	{
		ValidateType(DatumTypes::Matrix);
		ValidateIndex(0);

		return _data.m[_size - 1];
	}

	template<>
	inline RTTI*& Datum::Back()
	{
		ValidateType(DatumTypes::Pointer);
		ValidateIndex(0);

		return _data.p[_size - 1];
	}

	template<>
	inline Scope*& Datum::Back()
	{
		ValidateType(DatumTypes::Table);
		ValidateIndex(0);

		return _data.t[_size - 1];
	}

	template <typename T>
	inline T& Datum::Get(size_t)
	{
		throw std::runtime_error("Datum does not support this type.");
	}

	template<>
	inline int& Datum::Get(size_t index)
	{
		ValidateType(DatumTypes::Integer);
		ValidateIndex(index);

		return _data.i[index];
	}

	template<>
	inline float& Datum::Get(size_t index)
	{
		ValidateType(DatumTypes::Float);
		ValidateIndex(index);

		return _data.f[index];
	}

	template<>
	inline std::string& Datum::Get(size_t index)
	{
		ValidateType(DatumTypes::String);
		ValidateIndex(index);

		return _data.s[index];
	}

	template<>
	inline glm::vec4& Datum::Get(size_t index)
	{
		ValidateType(DatumTypes::Vector);
		ValidateIndex(index);

		return _data.v[index];
	}

	template<>
	inline glm::mat4& Datum::Get(size_t index)
	{
		ValidateType(DatumTypes::Matrix);
		ValidateIndex(index);

		return _data.m[index];
	}

	template<>
	inline RTTI*& Datum::Get(size_t index)
	{
		ValidateType(DatumTypes::Pointer);
		ValidateIndex(index);

		return _data.p[index];
	}

	template<>
	inline Scope*& Datum::Get(size_t index)
	{
		ValidateType(DatumTypes::Table);
		ValidateIndex(index);

		return _data.t[index];
	}


	template<typename T>
	inline const T& Datum::Front() const
	{
		throw std::runtime_error("Datum does not support this type.");
	}

	template<>
	inline const int& Datum::Front() const
	{
		ValidateType(DatumTypes::Integer);
		ValidateIndex(0);

		return _data.i[0];
	}

	template<>
	inline const float& Datum::Front() const
	{
		ValidateType(DatumTypes::Float);
		ValidateIndex(0);

		return _data.f[0];
	}

	template<>
	inline const std::string& Datum::Front() const
	{
		ValidateType(DatumTypes::String);
		ValidateIndex(0);

		return _data.s[0];
	}

	template<>
	inline const glm::vec4& Datum::Front() const
	{
		ValidateType(DatumTypes::Vector);
		ValidateIndex(0);

		return _data.v[0];
	}

	template<>
	inline const glm::mat4& Datum::Front() const
	{
		ValidateType(DatumTypes::Matrix);
		ValidateIndex(0);

		return _data.m[0];
	}

	template<>
	inline RTTI* const& Datum::Front() const
	{
		ValidateType(DatumTypes::Pointer);
		ValidateIndex(0);

		return _data.p[0];
	}

	template<>
	inline Scope* const& Datum::Front() const
	{
		ValidateType(DatumTypes::Table);
		ValidateIndex(0);

		return _data.t[0];
	}

	template<typename T>
	inline const T& Datum::Back() const
	{
		throw std::runtime_error("Datum does not support this type.");
	}

	template<>
	inline const int& Datum::Back() const
	{
		ValidateType(DatumTypes::Integer);
		ValidateIndex(0);

		return _data.i[_size - 1];
	}

	template<>
	inline const float& Datum::Back() const
	{
		ValidateType(DatumTypes::Float);
		ValidateIndex(0);

		return _data.f[_size - 1];
	}

	template<>
	inline const std::string& Datum::Back() const
	{
		ValidateType(DatumTypes::String);
		ValidateIndex(0);

		return _data.s[_size - 1];
	}

	template<>
	inline const glm::vec4& Datum::Back() const
	{
		ValidateType(DatumTypes::Vector);
		ValidateIndex(0);

		return _data.v[_size - 1];
	}

	template<>
	inline const glm::mat4& Datum::Back() const
	{
		ValidateType(DatumTypes::Matrix);
		ValidateIndex(0);

		return _data.m[_size - 1];
	}

	template<>
	inline RTTI* const& Datum::Back() const
	{
		ValidateType(DatumTypes::Pointer);
		ValidateIndex(0);

		return _data.p[_size - 1];
	}

	template<>
	inline Scope* const& Datum::Back() const
	{
		ValidateType(DatumTypes::Table);
		ValidateIndex(0);

		return _data.t[_size - 1];
	}

	template <typename T>
	inline const T& Datum::Get(size_t) const
	{
		throw std::runtime_error("Datum does not support this type.");
	}

	template<>
	inline const int& Datum::Get(size_t index) const
	{
		ValidateType(DatumTypes::Integer);
		ValidateIndex(index);

		return _data.i[index];
	}

	template<>
	inline const float& Datum::Get(size_t index) const
	{
		ValidateType(DatumTypes::Float);
		ValidateIndex(index);

		return _data.f[index];
	}

	template<>
	inline const std::string& Datum::Get(size_t index) const
	{
		ValidateType(DatumTypes::String);
		ValidateIndex(index);

		return _data.s[index];
	}

	template<>
	inline const glm::vec4& Datum::Get(size_t index) const
	{
		if (_type != DatumTypes::Vector)
			throw std::runtime_error("Type mismatch.");
		if (index >= _size)
			throw std::out_of_range("Index out of bounds.");

		return _data.v[index];
	}

	template<>
	inline const glm::mat4& Datum::Get(size_t index) const
	{
		ValidateType(DatumTypes::Matrix);
		ValidateIndex(index);

		return _data.m[index];
	}

	template<>
	inline RTTI* const& Datum::Get(size_t index) const
	{
		ValidateType(DatumTypes::Pointer);
		ValidateIndex(index);

		return _data.p[index];
	}

	template<>
	inline Scope* const& Datum::Get(size_t index) const
	{
		ValidateType(DatumTypes::Table);
		ValidateIndex(index);

		return _data.t[index];
	}
}