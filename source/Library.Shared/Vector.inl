#include <stdexcept>

namespace FieaGameEngine
{
	template <typename T>
	Vector<T>::Vector(std::size_t capacity)
	{
		Reserve(capacity);
	}

	template <typename T>
	Vector<T>::Vector(std::initializer_list<T> list)
	{
		for (const auto& value : list)
			PushBack(value);
	}

	template <typename T>
	Vector<T>::Vector(Vector&& other) noexcept
		: _data{other._data}, _size { other._size }, _capacity { other._capacity}
	{
		other._data = nullptr;
		other._size = 0;
		other._capacity = 0;
	}

	template <typename T>
	Vector<T>::Vector(const Vector& other)
	{
		Reserve(other.Size());

		ConstIterator it = other.begin();
		while (it != other.end())
			PushBack(*it++);
	}

	template <typename T>
	Vector<T>& Vector<T>::operator=(const Vector& rhs)
	{
		if (this != &rhs)
		{
			Clear();
			Reserve(rhs.Size());

			ConstIterator it = rhs.begin();
			while (it != rhs.end())
				PushBack(*it++);
		}
		return *this;
	}

	template<typename T>
	Vector<T>& Vector<T>::operator=(Vector&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Clear();
			ShrinkToFit();

			_data = rhs._data;
			_size = rhs._size;
			_capacity = rhs._capacity;

			rhs._data = nullptr;
			rhs._size = 0;
			rhs._capacity = 0;
		}
		return *this;
	}

	template <typename T>
	Vector<T>::~Vector()
	{
		Clear();
		ShrinkToFit();
	}

	template <typename T>
	inline Vector<T>::Iterator::Iterator(const Vector& owner, T* item) 
		: _owner{ &owner }, _item{ item }
	{

	}

	template <typename T>
	inline Vector<T>::ConstIterator::ConstIterator(const Vector& owner, T* item)
		: _owner{ &owner }, _item{ item }
	{

	}

	template <typename T>
	inline Vector<T>::ConstIterator::ConstIterator(const Iterator& it)
		: _owner{ it._owner }, _item{ it._item }
	{

	}

	template <typename T>
	inline const std::size_t Vector<T>::Size() const
	{
		return _size;
	}

	template <typename T>
	inline const std::size_t Vector<T>::Capacity() const
	{
		return _capacity;
	}

	template <typename T>
	inline const bool Vector<T>::IsEmpty() const
	{
		return _size == 0;
	}

	template <typename T>
	void Vector<T>::Reserve(std::size_t capacity)
	{
		if (capacity > _capacity)
		{
			T* data = reinterpret_cast<T*>(realloc(_data, capacity * sizeof(T)));
			assert(data != nullptr);

			_data = data;
			_capacity = capacity;
		}
	}

	template <typename T>
	inline T& Vector<T>::operator[](size_t index)
	{
		return at(index);
	}

	template <typename T>
	inline const T& Vector<T>::operator[](size_t index) const
	{
		return at(index);
	}

	template <typename T>
	inline T& Vector<T>::at(size_t index)
	{
		if (index >= _size)
			throw std::out_of_range("Index out of range.");

		return _data[index];
	}

	template <typename T>
	inline const T& Vector<T>::at(size_t index) const
	{
		if (index >= _size)
			throw std::out_of_range("Index out of range.");

		return _data[index];
	}

	template<typename T>
	void Vector<T>::PushBack(const T& value)
	{
		EmplaceBack(value);
	}

	template<typename T>
	void Vector<T>::PushBack(T&& value)
	{
		EmplaceBack(std::move(value));
	}

	template<typename T>
	template<typename... Args>
	void Vector<T>::EmplaceBack(Args&&... args)
	{
		if (_size == _capacity)
			Reserve(std::max(_capacity + _size, size_t(1)));

		new (_data + _size) T(std::forward<Args>(args)...);
		++_size;
	}

	template<typename T>
	inline T& Vector<T>::Front()
	{
		if (_size == 0)
			throw std::runtime_error("Array is empty.");

		return _data[0];
	}

	template<typename T>
	inline const T& Vector<T>::Front() const
	{
		if (_size == 0)
			throw std::runtime_error("Array is empty.");

		return _data[0];
	}

	template<typename T>
	inline T& Vector<T>::Back()
	{
		if (_size == 0)
			throw std::runtime_error("Array is empty.");

		return _data[_size - 1];
	}

	template<typename T>
	inline const T& Vector<T>::Back() const
	{
		if (_size == 0)
			throw std::runtime_error("Array is empty.");

		return _data[_size - 1];
	}

	template <typename T>
	void Vector<T>::Clear()
	{
		if (_size == 0)
			return;

		for (Iterator it = begin(); it != end(); ++it)
			it._item->~T();

		_size = 0;
	}

	template <typename T>
	void Vector<T>::ShrinkToFit()
	{
		if (_capacity == _size)
			return;

		_capacity = _size;

		if (_capacity == size_t(0))
		{
			free(_data);
			_data = nullptr;
		}
		else
		{
			T* data = reinterpret_cast<T*>(realloc(_data, _capacity * sizeof(T)));
			assert(data != nullptr);
			_data = data;
		}
	}

	template <typename T>
	void Vector<T>::PopBack()
	{
		if (_size == 0)
			return;

		_data[_size - 1].~T();
		--_size;
	}

	template<typename T>
	template<typename EqualityFunctor>
	typename Vector<T>::Iterator Vector<T>::Find(const T& value, EqualityFunctor equalityFunctor)
	{
		Iterator it;
		for ( it = begin(); it != end(); ++it)
		{
			if (equalityFunctor(*it, value))
				break;
		}
		return it;
	}

	template<typename T>
	template<typename EqualityFunctor>
	typename Vector<T>::ConstIterator Vector<T>::Find(const T& value, EqualityFunctor equalityFunctor) const
	{
		ConstIterator it;
		for (it = begin(); it != end(); ++it)
		{
			if (equalityFunctor(*it, value))
				break;
		}
		return it;
	}

	template<typename T>
	template <typename EqualityFunctor>
	bool Vector<T>::Remove(const T& value, EqualityFunctor equalityFunctor)
	{
		Iterator it = Find(value, equalityFunctor);
		if(it == end())
			return false;
		
		size_t offset = it._item - _data;
		it._item->~T();
		std::memmove(_data + offset, _data + offset + 1, sizeof(T) * (end()._item - it._item));
		--_size;
		return true;
	}

	template<typename T>
	bool Vector<T>::Remove(ConstIterator begin, ConstIterator end)
	{
		if (begin._item == end._item || begin._owner != end._owner)
			return false;

		if (begin > end)
			return false;

		size_t offsetFromStart = begin._item - _data;
		size_t offset = end._item - begin._item;

		while (begin != end)
		{
			begin._item->~T();
			++begin;
			--_size;
		}
		memmove(_data + offsetFromStart, _data + offsetFromStart + offset, sizeof(T) * offset);
		return true;
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::begin()
	{
		return Iterator{ *this, _data};
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::begin() const
	{
		return ConstIterator{ *this, _data};
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::cbegin()
	{
		return ConstIterator{ *this, _data};
	}

	template<typename T>
	inline typename Vector<T>::Iterator Vector<T>::end()
	{
		return Iterator{ *this, _data + _size };
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::end() const
	{
		return ConstIterator{ *this, _data + _size };
	}

	template<typename T>
	inline typename Vector<T>::ConstIterator Vector<T>::cend()
	{
		return ConstIterator{ *this, _data + _size };
	}

	template<typename T>
	bool Vector<T>::operator!=(const Vector& rhs) const
	{
		if (_size != rhs._size)
			return true;

		for (size_t i = 0; i < _size; ++i)
		{
			if (_data[i] != rhs._data[i])
				return true;
		}
		return false;
	}

	template<typename T>
	bool Vector<T>::operator==(const Vector& rhs) const
	{
		return !operator!=(rhs);
	}


	template<typename T>
	T& Vector<T>::Iterator::operator*() const
	{
		if (_owner == nullptr)
			throw std::runtime_error("Iterator does not belong to any container.");

		if (_owner->_data + _owner->_size <= _item)
			throw std::runtime_error("Iterator does not point to a valid element.");

		return *_item;
	}

	template<typename T>
	inline bool Vector<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return _item != rhs._item || _owner != rhs._owner;
	}

	template<typename T>
	inline bool Vector<T>::Iterator::operator==(const Iterator& rhs) const
	{
		return !operator!=(rhs);
	}

	template<typename T>
	typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
	{
		if (_owner == nullptr)
			throw std::runtime_error("Iterator does not belong to any container.");

		if (_item >= _owner->_data + _owner->_capacity)
			throw std::runtime_error("Cannot increment iterator as it has reached the end of the allocated memory.");

		_item += 1;
		return *this;
	}

	template<typename T>
	typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
	{
		Iterator it = *this;
		++(*this);
		return it;
	}


	template<typename T>
	const T& Vector<T>::ConstIterator::operator*() const
	{
		if (_owner == nullptr)
			throw std::runtime_error("Iterator does not belong to any container.");

		if (_owner->_data + _owner->_size <= _item)
			throw std::runtime_error("Iterator does not point to a valid element.");

		return *_item;
	}

	template<typename T>
	inline bool Vector<T>::ConstIterator::operator!=(const ConstIterator& rhs) const
	{
		return  _item != rhs._item || _owner != rhs._owner;
	}

	template<typename T>
	inline bool Vector<T>::ConstIterator::operator==(const ConstIterator& rhs) const
	{
		return !operator!=(rhs);
	}

	template<typename T>
	typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator++()
	{
		if (_owner == nullptr)
			throw std::runtime_error("Iterator does not belong to any container.");

		if (_item >= _owner->_data + _owner->_capacity)
			throw std::runtime_error("Cannot increment iterator as it has reached the end of the allocated memory.");

		_item += 1;
		return *this;
	}

	template<typename T>
	typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator++(int)
	{
		ConstIterator it = *this;
		++(*this);
		return it;
	}

	template<typename T>
	inline bool Vector<T>::ConstIterator::operator<(const ConstIterator& rhs) const
	{
		return  rhs._item - _item > 0;
	}

	template<typename T>
	inline bool Vector<T>::ConstIterator::operator>(const ConstIterator& rhs) const
	{
		return  _item - rhs._item > 0;
	}
}
