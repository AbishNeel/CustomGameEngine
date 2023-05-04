#pragma once
#include "pch.h"
#include "Datum.h"
#include "Scope.h"

namespace FieaGameEngine
{
	Datum::Datum(DatumTypes type)
		: _type{ type }
	{
		_data.vp = nullptr;
	}

	Datum::Datum(int value)
		: Datum(DatumTypes::Integer)
	{
		Reserve(1);
		PushBack(value);
	}

	Datum::Datum(float value)
		: Datum(DatumTypes::Float)
	{
		Reserve(1);
		PushBack(value);
	}

	Datum::Datum(const std::string& value)
		: Datum(DatumTypes::String)
	{
		Reserve(1);
		PushBack(value);
	}

	Datum::Datum(const glm::vec4& value)
		: Datum(DatumTypes::Vector)
	{
		Reserve(1);
		PushBack(value);
	}

	Datum::Datum(const glm::mat4& value)
		: Datum(DatumTypes::Matrix)
	{
		Reserve(1);
		PushBack(value);
	}

	Datum::Datum(RTTI* value)
		: Datum(DatumTypes::Pointer)
	{
		Reserve(1);
		PushBack(value);
	}

	Datum::Datum(std::initializer_list<int> list)
		: Datum(DatumTypes::Integer)
	{
		Reserve(list.size());
		for (auto value : list)
			PushBack(value);
	}

	Datum::Datum(std::initializer_list<float> list)
		: Datum(DatumTypes::Float)
	{
		Reserve(list.size());
		for (auto value : list)
			PushBack(value);
	}

	Datum::Datum(std::initializer_list<std::string> list)
		: Datum(DatumTypes::String)
	{
		Reserve(list.size());
		for (auto& value : list)
			PushBack(value);
	}

	Datum::Datum(std::initializer_list<glm::vec4> list)
		: Datum(DatumTypes::Vector)
	{
		Reserve(list.size());
		for (auto& value : list)
			PushBack(value);
	}

	Datum::Datum(std::initializer_list<glm::mat4> list)
		: Datum(DatumTypes::Matrix)
	{
		Reserve(list.size());
		for (auto& value : list)
			PushBack(value);
	}

	Datum::Datum(std::initializer_list<RTTI*> list)
		: Datum(DatumTypes::Pointer)
	{
		Reserve(list.size());
		for (auto value : list)
			PushBack(value);
	}

	Datum::Datum(const Datum& other)
		: Datum(other._type)
	{
		if (!other._IsExternal)
		{
			Reserve(other._size);
			if (_type == DatumTypes::String)
			{
				for (size_t i = 0; i < other._size; ++i)
					PushBack(other._data.s[i]);
			}
			else if(other.Size() > 0)
			{
				size_t size = DatumTypeSizes[static_cast<int>(_type)];
				void* data = memcpy(_data.vp, other._data.vp, other._size * size);
				assert(data != nullptr);
				_data.vp = data;
			}
		}
		else
		{
			_data = other._data;
			_IsExternal = true;
		}
		_size = other._size;
	}

	Datum& Datum::operator=(const Datum& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			if (!_IsExternal)
				free(_data.vp);
		
			_data.vp = nullptr;
			_capacity = 0;

			SetType(rhs._type);
			if (!rhs._IsExternal)
			{
				_IsExternal = false;
				Reserve(rhs._size);

				if (rhs._type == DatumTypes::String)
				{
					for (size_t i = 0; i < rhs._size; ++i)
						PushBack(rhs._data.s[i]);
				}
				else if (rhs.Size() > 0)
				{
					size_t size = DatumTypeSizes[static_cast<int>(_type)];
					void* data = memmove(_data.vp, rhs._data.vp, size * rhs._size);
					assert(data != nullptr);
					_data.vp = data;
				}
			}
			else
			{
				_IsExternal = true;
				_data = rhs._data;
				_capacity = rhs._capacity;
			}

			_size = rhs._size;
		}
		return *this;
	}

	Datum::Datum(Datum&& other) noexcept
		: _data{ other._data }, _size{ other._size }, _capacity{ other._capacity }, _type{ other._type }, _IsExternal{ other._IsExternal }
	{
		other._data.vp = nullptr;
		other._size = 0;
		other._capacity = 0;
	}

	Datum& Datum::operator=(Datum&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Clear();
			free(_data.vp);

			_data = rhs._data;
			_size = rhs._size;
			_capacity = rhs._capacity;
			_type = rhs._type;
			_IsExternal = rhs._IsExternal;

			rhs._data.vp = nullptr;
			rhs._size = 0;
			rhs._capacity = 0;
		}

		return *this;
	}

	Datum::~Datum()
	{
		if (!_IsExternal)
		{
			Clear();
			free(_data.vp);
		}
	}

	void Datum::SetType(DatumTypes type)
	{
		if (_type != DatumTypes::Unknown || _type == type)
			return;
		_type = type;
	}

	void Datum::ValidateType(DatumTypes type) const
	{
		if(_type != DatumTypes::Unknown && _type != type)
			throw std::runtime_error("Type mismatch.");
	}

	void Datum::ValidateIndex(size_t index) const
	{
		if(index >= _size)
			throw std::out_of_range("Index out of range.");
	}

	void Datum::Reserve(size_t capacity)
	{
		assert(!_IsExternal);
		if (_type == DatumTypes::Unknown)
			return;

		if (capacity > _capacity)
		{
			size_t size = DatumTypeSizes[static_cast<int>(_type)];
			void* data = realloc(_data.vp, capacity * size);
			assert(data != nullptr);

			_data.vp = data;
			_capacity = capacity;
		}
	}

	void Datum::PushBack(int value)
	{
		assert(!_IsExternal);
		ValidateType(DatumTypes::Integer);

		SetType(DatumTypes::Integer);

		if (_size == _capacity)
			Reserve(std::max(_size * 2, size_t(1)));
		new (_data.i + _size) int(value);
		++_size;
	}

	void Datum::PushBack(float value)
	{
		assert(!_IsExternal);
		ValidateType(DatumTypes::Float);

		SetType(DatumTypes::Float);

		if (_size == _capacity)
			Reserve(std::max(_size * 2, size_t(1)));
		_data.f[_size] = value;
		++_size;
	}

	void Datum::PushBack(const std::string& value)
	{
		assert(!_IsExternal);
		ValidateType(DatumTypes::String);

		SetType(DatumTypes::String);

		if (_size == _capacity)
			Reserve(std::max(_size * 2, size_t(1)));
		new (_data.s + _size) std::string(value);
		++_size;
	}

	void Datum::PushBack(const glm::vec4& value)
	{
		assert(!_IsExternal);
		ValidateType(DatumTypes::Vector);

		SetType(DatumTypes::Vector);

		if (_size == _capacity)
			Reserve(std::max(_size * 2, size_t(1)));
		new (_data.v + _size) glm::vec4(value);
		++_size;
	}

	void Datum::PushBack(const glm::mat4& value)
	{
		assert(!_IsExternal);
		ValidateType(DatumTypes::Matrix);

		SetType(DatumTypes::Matrix);

		if (_size == _capacity)
			Reserve(std::max(_size * 2, size_t(1)));
		new (_data.m + _size) glm::mat4(value);
		++_size;
	}

	void Datum::PushBack(RTTI* value)
	{
		assert(!_IsExternal);
		ValidateType(DatumTypes::Pointer);

		SetType(DatumTypes::Pointer);

		if (_size == _capacity)
			Reserve(std::max(_size * 2, size_t(1)));
		new (_data.p + _size) RTTI* (value);
		++_size;
	}

	void Datum::PushBackScope(Scope* value)
	{
		assert(!_IsExternal);
		ValidateType(DatumTypes::Table);

		SetType(DatumTypes::Table);

		if (_size == _capacity)
			Reserve(std::max(_size * 2, size_t(1)));
		new (_data.t + _size) Scope* (value);
		++_size;
	}

	void Datum::SetStorage(int* array, size_t size)
	{
		ValidateType(DatumTypes::Integer);

		SetType(DatumTypes::Integer);
		if (_size > 0 && !_IsExternal)
		{
			Clear();
			free(_data.vp);
		}

		_IsExternal = true;
		_data.i = array;
		_size = size;
		_capacity = size;
	}

	void Datum::SetStorage(float* array, size_t size)
	{
		ValidateType(DatumTypes::Float);

		SetType(DatumTypes::Float);
		if (_size > 0 && !_IsExternal)
		{
			Clear();
			free(_data.vp);
		}

		_IsExternal = true;
		_data.f = array;
		_size = size;
		_capacity = size;
	}

	void Datum::SetStorage(std::string* array, size_t size)
	{
		ValidateType(DatumTypes::String);

		SetType(DatumTypes::String);
		if (_size > 0 && !_IsExternal)
		{
			Clear();
			free(_data.vp);
		}

		_IsExternal = true;
		_data.s = array;
		_size = size;
		_capacity = size;
	}

	void Datum::SetStorage(glm::vec4* array, size_t size)
	{
		ValidateType(DatumTypes::Vector);

		SetType(DatumTypes::Vector);
		if (_size > 0 && !_IsExternal)
		{
			Clear();
			free(_data.vp);
		}

		_IsExternal = true;
		_data.v = array;
		_size = size;
		_capacity = size;
	}

	void Datum::SetStorage(glm::mat4* array, size_t size)
	{
		ValidateType(DatumTypes::Matrix);

		SetType(DatumTypes::Matrix);
		if (_size > 0 && !_IsExternal)
		{
			Clear();
			free(_data.vp);
		}

		_IsExternal = true;
		_data.m = array;
		_size = size;
		_capacity = size;
	}

	void Datum::SetStorage(RTTI** array, size_t size)
	{
		ValidateType(DatumTypes::Pointer);

		SetType(DatumTypes::Pointer);
		if (_size > 0 && !_IsExternal)
		{
			Clear();
			free(_data.vp);
		}

		_IsExternal = true;
		_data.p = array;
		_size = size;
		_capacity = size;
	}

	void Datum::SetStorage(void* array, size_t size, DatumTypes type)
	{
		switch (type)
		{
		case DatumTypes::Integer:
			SetStorage(reinterpret_cast<int*>(array), size);
			break;

		case DatumTypes::Float:
			SetStorage(reinterpret_cast<float*>(array), size);
			break;

		case DatumTypes::String:
			SetStorage(reinterpret_cast<std::string*>(array), size);
			break;

		case DatumTypes::Vector:
			SetStorage(reinterpret_cast<glm::vec4*>(array), size);
			break;

		case DatumTypes::Matrix:
			SetStorage(reinterpret_cast<glm::mat4*>(array), size);
			break;

		case DatumTypes::Pointer:
			SetStorage(reinterpret_cast<RTTI**>(array), size);
			break;
		}
	}

	void Datum::Set(int value, size_t index)
	{
		ValidateType(DatumTypes::Integer);
		ValidateIndex(index);

		SetType(DatumTypes::Integer);
		_data.i[index] = value;
	}

	void Datum::Set(float value, size_t index)
	{
		ValidateType(DatumTypes::Float);
		ValidateIndex(index);

		SetType(DatumTypes::Float);
		_data.f[index] = value;
	}

	void Datum::Set(const std::string& value, size_t index)
	{
		ValidateType(DatumTypes::String);
		ValidateIndex(index);

		SetType(DatumTypes::String);
		_data.s[index] = value;
	}

	void Datum::Set(const glm::vec4& value, size_t index)
	{
		ValidateType(DatumTypes::Vector);
		ValidateIndex(index);

		SetType(DatumTypes::Vector);
		_data.v[index] = value;
	}

	void Datum::Set(const glm::mat4& value, size_t index)
	{
		ValidateType(DatumTypes::Matrix);
		ValidateIndex(index);

		SetType(DatumTypes::Matrix);
		_data.m[index] = value;
	}

	void Datum::Set(RTTI* value, size_t index)
	{
		ValidateType(DatumTypes::Pointer);
		ValidateIndex(index);

		SetType(DatumTypes::Pointer);
		_data.p[index] = value;
	}

	void Datum::Set(Scope* value, size_t index)
	{
		ValidateType(DatumTypes::Table);
		ValidateIndex(index);

		SetType(DatumTypes::Table);
		_data.t[index] = value;
	}

	size_t Datum::Find(int value) const
	{
		ValidateType(DatumTypes::Integer);
		
		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.i[i] == value)
				return i;
		}

		return _size;
	}

	size_t Datum::Find(float value) const 
	{
		ValidateType(DatumTypes::Float);

		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.f[i] == value)
				return i;
		}

		return _size;
	}

	size_t Datum::Find(const std::string& value) const
	{
		ValidateType(DatumTypes::String);

		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.s[i] == value)
				return i;
		}

		return _size;
	}

	size_t Datum::Find(const glm::vec4& value) const
	{
		ValidateType(DatumTypes::Vector);

		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.v[i] == value)
				return i;
		}

		return _size;
	}

	size_t Datum::Find(const glm::mat4& value) const
	{
		ValidateType(DatumTypes::Matrix);

		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.m[i] == value)
				return i;
		}

		return _size;
	}

	size_t Datum::Find(const RTTI* value) const
	{
		ValidateType(DatumTypes::Pointer);

		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.p[i]->Equals(value))
				return i;
		}

		return _size;
	}

	size_t Datum::Find(const Scope* value) const
	{
		ValidateType(DatumTypes::Table);

		for (size_t i = 0; i < _size; ++i)
		{
			if (_data.t[i]->Equals(value))
				return i;
		}

		return _size;
	}

	bool Datum::Remove(int value)
	{
		ValidateType(DatumTypes::Integer);
		return RemoveAt(Find(value));
	}

	bool Datum::Remove(float value)
	{
		ValidateType(DatumTypes::Float);
		return RemoveAt(Find(value));
	}

	bool Datum::Remove(const std::string& value)
	{
		ValidateType(DatumTypes::String);
		return RemoveAt(Find(value));
	}

	bool Datum::Remove(const glm::vec4& value)
	{
		ValidateType(DatumTypes::Vector);
		return RemoveAt(Find(value));
	}

	bool Datum::Remove(const glm::mat4& value)
	{
		ValidateType(DatumTypes::Matrix);
		return RemoveAt(Find(value));
	}

	bool Datum::Remove(const RTTI* value)
	{
		ValidateType(DatumTypes::Pointer);
		return RemoveAt(Find(value));
	}

	bool Datum::Remove(const Scope* value)
	{
		ValidateType(DatumTypes::Table);
		return RemoveAt(Find(value));
	}


	bool Datum::RemoveAt(size_t index)
	{
		if (_type == DatumTypes::Unknown)
			throw std::runtime_error("Datum type undefined.");
		
		ValidateIndex(index);

		size_t size = DatumTypeSizes[static_cast<int>(_type)];
		switch (_type)
		{
		case DatumTypes::Integer:
			memmove(_data.i + index, _data.i + index + 1, size * (_size - index - 1));
			break;

		case DatumTypes::Float:
			memmove(_data.f + index, _data.f + index + 1, size * (_size - index - 1));
			break;

		case DatumTypes::String:
			_data.s[index].~basic_string();
			memmove(_data.s + index, _data.s + index + 1, size * (_size - index - 1));
			break;

		case DatumTypes::Vector:
			memmove(_data.v + index, _data.v + index + 1, size * (_size - index - 1));
			break;

		case DatumTypes::Matrix:
			memmove(_data.m + index, _data.m + index + 1, size * (_size - index - 1));
			break;

		case DatumTypes::Pointer:
			memmove(_data.p + index, _data.p + index + 1, size * (_size - index - 1));
			break;

		case DatumTypes::Table:
			memmove(_data.t + index, _data.t + index + 1, size * (_size - index - 1));
			break;
		}
		--_size;
		return true;
	}

	void Datum::PopBack()
	{
		if (_size == 0)
			throw std::runtime_error("Datum is empty.");

		if (_type == DatumTypes::String)
			_data.s[_size - 1].~basic_string();
		--_size;
	}

	void Datum::Clear()
	{
		if (_type == DatumTypes::String && !_IsExternal)
		{
			for (size_t i = 0; i < _size; ++i)
				_data.s[i].~basic_string();
		}

		if (_IsExternal)
			_data.vp = nullptr;

		_size = 0;
	}

	void Datum::Resize(size_t newSize)
	{
		assert(!_IsExternal);
		if (_type == DatumTypes::Unknown || _capacity == 0)
			throw std::runtime_error("Memory not initialized.");

		if (_type == DatumTypes::String)
		{
			for (size_t i = newSize; i < _size; ++i)
				_data.s[i].~basic_string();
		}

		size_t size = DatumTypeSizes[static_cast<int>(_type)];
		void* data = realloc(_data.vp, newSize * size);
		_data.vp = data;
		
		if (newSize > _size)
		{
			switch (_type)
			{
			case DatumTypes::Integer:
				for (size_t i = _size; i < newSize; ++i)
					PushBack(int{});
				break;

			case DatumTypes::Float:
				for (size_t i = _size; i < newSize; ++i)
					PushBack(float{});
				break;

			case DatumTypes::String:
				for (size_t i = _size; i < newSize; ++i)
					PushBack(std::string{});
				break;

			case DatumTypes::Vector:
				for (size_t i = _size; i < newSize; ++i)
					PushBack(glm::vec4{});
				break;

			case DatumTypes::Matrix:
				for (size_t i = _size; i < newSize; ++i)
					PushBack(glm::mat4{});
				break;

			case DatumTypes::Pointer:
				for (size_t i = _size; i < newSize; ++i)
				{
					RTTI* p{nullptr};
					PushBack(p);
				}
				break;

			case DatumTypes::Table:
				for (size_t i = _size; i < newSize; ++i)
				{
					Scope* t{ nullptr };
					PushBack(t);
				}
				break;
			}
		}

		_size = newSize;
		_capacity = _size;
	}

	std::string Datum::ToString(size_t index) const
	{
		ValidateIndex(index);

		if (_type == DatumTypes::String)
			return _data.s[index];

		if (_type == DatumTypes::Pointer)
			return _data.p[index]->ToString();

		char buffer[256] = { '\0' };

		switch (_type)
		{
		case DatumTypes::Integer:
			sprintf_s(buffer, sizeof(buffer), "%d", _data.i[index]);
			break;

		case DatumTypes::Float:
			sprintf_s(buffer, sizeof(buffer), "%4.2f", _data.f[index]);
			break;

		case DatumTypes::Vector:
			sprintf_s(buffer, sizeof(buffer), "vec4(%4.2f, %4.2f, %4.2f, %4.2f)", _data.v[index].x, _data.v[index].y, _data.v[index].z, _data.v[index].w);
			break;

		case DatumTypes::Matrix:
			sprintf_s(buffer, sizeof(buffer), "mat4(%4.2f, %4.2f, %4.2f, %4.2f\n %4.2f, %4.2f, %4.2f, %4.2f\n %4.2f, %4.2f, %4.2f, %4.2f\n %4.2f, %4.2f, %4.2f, %4.2f)", 
				_data.m[index][0].x, _data.m[index][0].y, _data.m[index][0].z, _data.m[index][0].w,
				_data.m[index][1].x, _data.m[index][1].y, _data.m[index][1].z, _data.m[index][1].w, 
				_data.m[index][2].x, _data.m[index][2].y, _data.m[index][2].z, _data.m[index][2].w,
				_data.m[index][3].x, _data.m[index][3].y, _data.m[index][3].z, _data.m[index][3].w);
			break;

		default:
			break;
		}

		return std::string(buffer);
	}

	void Datum::SetIntFromString(const std::string& string, size_t index)
	{
		int num;

		sscanf_s(string.c_str(), "%d", &num);
		Set(num, index);
	}

	void Datum::SetFloatFromString(const std::string& string, size_t index)
	{
		float num;

		sscanf_s(string.c_str(), "%f", &num);
		Set(num, index);
	}

	void Datum::SetVecFromString(const std::string& string, size_t index)
	{
		glm::vec4 vec;

		sscanf_s(string.c_str(), "vec4(%f, %f, %f, %f)", &vec.x, &vec.y, &vec.z, &vec.w);
		Set(vec, index);
	}

	void Datum::SetMatFromString(const std::string& string, size_t index)
	{
		glm::mat4 mat;

		sscanf_s(string.c_str(), "mat4(%f, %f, %f, %f\n %f, %f, %f, %f\n %f, %f, %f, %f\n %f, %f, %f, %f)",
			&mat[0].x, &mat[0].y, &mat[0].z, &mat[0].w,
			&mat[1].x, &mat[1].y, &mat[1].z, &mat[1].w,
			&mat[2].x, &mat[2].y, &mat[2].z, &mat[2].w,
			&mat[3].x, &mat[3].y, &mat[3].z, &mat[3].w);
		Set(mat, index);
	}

	void Datum::PushBackVectorFromString(const std::string& vectorString)
	{
		glm::vec4 vec;

		sscanf_s(vectorString.c_str(), "vec4(%f, %f, %f, %f)", &vec.x, &vec.y, &vec.z, &vec.w);
		PushBack(vec);
	}

	void Datum::PushBackMatrixFromString(const std::string& matrixString)
	{
		glm::mat4 mat;

		sscanf_s(matrixString.c_str(), "mat4(%f, %f, %f, %f\n %f, %f, %f, %f\n %f, %f, %f, %f\n %f, %f, %f, %f)",
			&mat[0].x, &mat[0].y, &mat[0].z, &mat[0].w,
			&mat[1].x, &mat[1].y, &mat[1].z, &mat[1].w,
			&mat[2].x, &mat[2].y, &mat[2].z, &mat[2].w,
			&mat[3].x, &mat[3].y, &mat[3].z, &mat[3].w);
		PushBack(mat);
	}

	Datum& Datum::operator=(int value)
	{
		ValidateType(DatumTypes::Integer);
		SetType(DatumTypes::Integer);

		if (_size == 0)
		{
			Reserve(1);
			PushBack(value);
		}
		else
			Set(value);

		return *this;
	}

	Datum& Datum::operator=(float value)
	{
		ValidateType(DatumTypes::Float);
		SetType(DatumTypes::Float);

		if (_size == 0)
		{
			Reserve(1);
			PushBack(value);
		}
		else
			Set(value);

		return *this;
	}

	Datum& Datum::operator=(const std::string& value)
	{
		ValidateType(DatumTypes::String);
		SetType(DatumTypes::String);

		if (_size == 0)
		{
			Reserve(1);
			PushBack(value);
		}
		else
			Set(value);

		return *this;
	}

	Datum& Datum::operator=(const glm::vec4& value)
	{
		ValidateType(DatumTypes::Vector);
		SetType(DatumTypes::Vector);

		if (_size == 0)
		{
			Reserve(1);
			PushBack(value);
		}
		else
			Set(value);

		return *this;
	}

	Datum& Datum::operator=(const glm::mat4& value)
	{
		ValidateType(DatumTypes::Matrix);
		SetType(DatumTypes::Matrix);

		if (_size == 0)
		{
			Reserve(1);
			PushBack(value);
		}
		else
			Set(value);

		return *this;
	}

	Datum& Datum::operator=(RTTI* value)
	{
		ValidateType(DatumTypes::Pointer);
		SetType(DatumTypes::Pointer);

		if (_size == 0)
		{
			Reserve(1);
			PushBack(value);
		}
		else
			Set(value);

		return *this;
	}

	Datum& Datum::operator=(Scope*& value)
	{
		ValidateType(DatumTypes::Table);
		SetType(DatumTypes::Table);

		if (_size == 0)
		{
			Reserve(1);
			PushBackScope(value);
		}
		else
			Set(value);

		return *this;
	}

	Scope& Datum::operator[](size_t index)
	{
		return *Get<Scope*>(index);
	}

	const Scope& Datum::operator[](size_t index) const
	{
		return *Get<Scope*>(index);
	}

	bool Datum::operator!=(const Datum& rhs) const
	{
		if (_type != rhs.Type() || _size != rhs.Size() || _IsExternal != rhs._IsExternal)
			return true;

		if (_type == DatumTypes::String)
		{
			for (size_t i = 0; i < _size; ++i)
			{
				if (_data.s[i] != rhs._data.s[i])
					return true;
			}
			return false;
		}

		if (_type == DatumTypes::Pointer)
		{
			for (size_t i = 0; i < _size; ++i)
			{
				if (!_data.p[i]->Equals(rhs._data.p[i]))
					return true;
			}
			return false;
		}

		if (_type == DatumTypes::Table)
		{
			for (size_t i = 0; i < _size; ++i)
			{
				if (!_data.t[i]->Equals(rhs._data.t[i]))
					return true;
			}
			return false;
		}

		return memcmp(_data.vp, rhs._data.vp, _size) == 0 ? false : true;
	}

	bool Datum::operator!=(int rhs) const
	{
		if (_type != DatumTypes::Integer || _size == 0 || _size > 1)
			return true;

		return _data.i[0] != rhs;
	}

	bool Datum::operator!=(float rhs) const
	{
		if (_type != DatumTypes::Float || _size == 0 || _size > 1)
			return true;

		return _data.f[0] != rhs;
	}

	bool Datum::operator!=(const std::string& rhs) const
	{
		if (_type != DatumTypes::String || _size == 0 || _size > 1)
			return true;

		return _data.s[0] != rhs;
	}

	bool Datum::operator!=(const glm::vec4& rhs) const
	{
		if (_type != DatumTypes::Vector || _size == 0 || _size > 1)
			return true;

		return _data.v[0] != rhs;
	}

	bool Datum::operator!=(const glm::mat4& rhs) const
	{
		if (_type != DatumTypes::Matrix || _size == 0 || _size > 1)
			return true;

		return _data.m[0] != rhs;
	}

	bool Datum::operator!=(const RTTI* rhs) const
	{
		if (_type != DatumTypes::Pointer || _size == 0 || _size > 1)
			return true;

		return !_data.p[0]->Equals(rhs);
	}

	bool Datum::operator==(const Datum& rhs) const
	{
		return !operator!=(rhs);
	}

	bool Datum::operator==(int rhs) const
	{
		return !operator!=(rhs);
	}

	bool Datum::operator==(float rhs) const
	{
		return !operator!=(rhs);
	}

	bool Datum::operator==(const std::string& rhs) const
	{
		return !operator!=(rhs);
	}

	bool Datum::operator==(const glm::vec4& rhs) const
	{
		return !operator!=(rhs);
	}

	bool Datum::operator==(const glm::mat4& rhs) const
	{
		return !operator!=(rhs);
	}

	bool Datum::operator==(const RTTI* rhs) const
	{
		return !operator!=(rhs);
	}
}