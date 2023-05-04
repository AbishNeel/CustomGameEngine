#include "SList.h"

namespace FieaGameEngine
{
	template <typename T>
	inline SList<T>::Node::Node(const T& data, Node* next)
		: _data{ data }, _next{ next }
	{

	}

	template <typename T>
	inline SList<T>::Iterator::Iterator(const SList& owner, Node* node)
		:  _owner { &owner }, _node { node }
	{
		
	}

	template <typename T>
	inline SList<T>::ConstIterator::ConstIterator(const SList& owner, Node* node)
		: _owner{ &owner }, _node{ node }
	{

	}

	template <typename T>
	inline SList<T>::ConstIterator::ConstIterator(const Iterator& other)
		: _owner{ other._owner }, _node{ other._node }
	{
		
	}

	template <typename T>
	inline SList<T>::~SList()
	{
		Clear();
	}

	template <typename T>
	SList<T>::SList(const SList& other)
	{
		Node* cur = other._front;

		while (cur != nullptr)
		{
			PushBack(cur->_data);
			cur = cur->_next;
		}
	}

	template <typename T>
	SList<T>::SList(SList&& other) noexcept
		: _front { other._front}, _back {other._back}, _size{other._size}
	{
		other._front = nullptr;
		other._back = nullptr;
		other._size = 0;
	}

	template <typename T>
	SList<T>::SList(std::initializer_list<T> list)
	{
		for (const auto& value : list)
			PushBack(value);
	}

	template <typename T>
	SList<T>& SList<T>::operator=(const SList& rhs)
	{
		if (this != &rhs)
		{
			Clear();

			Node* cur = rhs._front;
			while (cur != nullptr)
			{
				PushBack(cur->_data);
				cur = cur->_next;
			}
		}
		return *this;
	}

	template <typename T>
	inline void SList<T>::PushFront(const T& data)
	{
		Node* newNode =  new Node(data);

		if (IsEmpty())
			_back = newNode;
		else
			newNode->_next = _front;
			
		_front = newNode;
		_size++;
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::PushBack(const T& data)
	{
		return EmplaceBack(data);
	}

	template <typename T>
	template <typename... Args>
	typename SList<T>::Iterator SList<T>::EmplaceBack(Args... args)
	{
		Node* newNode = new Node(std::forward<Args>(args)...);

		if (IsEmpty())
			_front = newNode;
		else
			_back->_next = newNode;

		_back = newNode;
		_size++;

		return Iterator{ *this, newNode };
	}

	template <typename T>
	void SList<T>::PopFront()
	{
		if (IsEmpty())
			throw std::runtime_error("List is empty");

		Node front = *_front;
		delete(_front);
		_size--;

		_front = front._next;

		if (_size == 0)
			_back = nullptr;
	}

	template <typename T>
	void SList<T>::PopBack()
	{
		if (IsEmpty())
			throw std::runtime_error("List is empty");

		Node* cur = _front;
		Node* prev = nullptr;
		while (cur->_next != nullptr)
		{
			prev = cur;
			cur = cur->_next;
		}
		delete(cur);
		_size--;

		if(prev != nullptr)
			prev->_next = nullptr;
		_back = prev;
		
		if (_size == 0)
			_front = nullptr;
	}

	template <typename T>
	inline bool SList<T>::IsEmpty() const
	{
		return _size == 0;
	}

	template <typename T>
	inline T& SList<T>::Front()
	{
		if (IsEmpty())
			throw std::runtime_error("List is empty");

		return _front->_data;
	}

	template <typename T>
	inline const T& SList<T>::Front() const
	{
		if (IsEmpty())
			throw std::runtime_error("List is empty");

		return _front->_data;
	}

	template <typename T>
	inline T& SList<T>::Back()
	{
		if (IsEmpty())
			throw std::runtime_error("List is empty");

		return _back->_data;
	}

	template <typename T>
	inline const T& SList<T>::Back() const
	{
		if(IsEmpty())
			throw std::runtime_error("List is empty");

		return _back->_data;
	}

	template <typename T>
	void SList<T>::Clear()
	{
		while (_front != nullptr)
		{
			Node* next = _front->_next;
			delete(_front);
			--_size;
			_front = next;
		}
		_front = nullptr;
		_back = nullptr;
	}

	template <typename T>
	inline const size_t SList<T>::Size() const
	{
		return _size;
	}

	template <typename T>
	inline bool SList<T>::Iterator::operator==(const Iterator& other) const
	{
		return _owner == other._owner && _node == other._node;
	}

	template <typename T>
	inline bool SList<T>::ConstIterator::operator==(const ConstIterator& other) const
	{
		return _owner == other._owner && _node == other._node;
	}

	template <typename T>
	inline bool SList<T>::Iterator::operator!=(const Iterator& other) const
	{
		return !operator==(other);
	}

	template <typename T>
	inline bool SList<T>::ConstIterator::operator!=(const ConstIterator& other) const
	{
		return !operator==(other);
	}

	template <typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator++()
	{
		if (_owner == nullptr)
			throw std::runtime_error("Iterator not associated with a container.");

		if (_node == nullptr)
			throw std::out_of_range("Iterator cannot be incremented.");

		_node = _node->_next;
		return *this;
	}

	template <typename T>
	typename SList<T>::ConstIterator& SList<T>::ConstIterator::operator++()
	{
		if (_owner == nullptr)
			throw std::runtime_error("Iterator not associated with a container.");

		if (_node == nullptr)
			throw std::out_of_range("Iterator cannot be incremented.");

		_node = _node->_next;
		return *this;
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator++(int)
	{
		if (_owner == nullptr)
			throw std::runtime_error("Iterator not associated with a container.");

		if (_node == nullptr)
			throw std::out_of_range("Iterator cannot be incremented.");

		Iterator it = *this;
		++(*this);
		return it;
	}

	template <typename T>
	typename SList<T>::ConstIterator SList<T>::ConstIterator::operator++(int)
	{
		if (_owner == nullptr)
			throw std::runtime_error("Iterator not associated with a container.");

		if (_node == nullptr)
			throw std::out_of_range("Iterator cannot be incremented.");

		ConstIterator it = *this;
		++(*this);
		return it;
	}

	template <typename T>
	inline T& SList<T>::Iterator::operator*() const
	{
		if(_owner == nullptr)
			throw std::runtime_error("Iterator does not belong to any container.");
		if (_node == nullptr)
			throw std::runtime_error("Iterator does not point to valid item.");
		return _node->_data;
	}

	template <typename T>
	inline const T& SList<T>::ConstIterator::operator*() const
	{
		if (_owner == nullptr)
			throw std::runtime_error("Iterator does not belong to any container.");
		if (_node == nullptr)
			throw std::runtime_error("Iterator does not point to valid item.");
		return _node->_data;
	}

	template <typename T>
	typename inline SList<T>::Iterator SList<T>::begin()
	{
		return Iterator { *this, _front };
	}

	template <typename T>
	typename inline SList<T>::ConstIterator SList<T>::begin() const
	{
		return ConstIterator{ *this, _front };
	}

	template <typename T>
	typename inline SList<T>::ConstIterator SList<T>::cbegin() const
	{
		return ConstIterator{ *this, _front };
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::end()
	{
		return Iterator { *this };
	}

	template <typename T>
	typename inline SList<T>::ConstIterator SList<T>::end() const
	{
		return ConstIterator{ *this };
	}

	template <typename T>
	typename inline SList<T>::ConstIterator SList<T>::cend() const
	{
		return ConstIterator{ *this };
	}

	template <typename T>
	typename SList<T>::Iterator SList<T>::InsertAfter(const Iterator& it, const T& value)
	{	
		if (this != it._owner)
			throw std::runtime_error("Iterator does not belong to the same list");

		if (IsEmpty())
		{
			PushBack(value);
			return begin();
		}
		else if (it._node == nullptr)
			throw std::runtime_error("Iterator does not point to a valid item.");

		Node* newNode = new Node{ value, it._node->_next };
		it._node->_next = newNode;
		Iterator newIterator{ *this, newNode };
		_back = newNode->_next == nullptr ? newNode : _back;
		++_size;

		return newIterator;
	}

	template <typename T>
	typename SList<T>::ConstIterator SList<T>::InsertAfter(const ConstIterator& it, const T& value)
	{
		if (this != it._owner)
			throw std::runtime_error("Iterator does not belong to the same list");

		if (IsEmpty())
		{
			PushBack(value);
			return cbegin();
		}
		else if (it._node == nullptr)
			throw std::runtime_error("Iterator does not point to a valid item.");

		Node* newNode = new Node{ value, it._node->_next };
		it._node->_next = newNode;
		ConstIterator newIterator{ *this, newNode };
		_back = newNode->_next == nullptr ? newNode : _back;
		++_size;

		return newIterator;
	}

	template <typename T>
	template <typename EqualityFunctor>
	typename SList<T>::Iterator SList<T>::Find(const T& value, EqualityFunctor equalityFunctor)
	{
		Iterator it = begin();
		for (; it != end(); ++it)
		{
			if (equalityFunctor(*it, value))
				break;
		}
		return it;
	}

	template <typename T>
	template <typename EqualityFunctor>
	typename SList<T>::ConstIterator SList<T>::Find(const T& value, EqualityFunctor equalityFunctor) const
	{
		ConstIterator it = begin();
		for (; it != end(); ++it)
		{
			if (equalityFunctor(*it, value))
				break;
		}
		return it;
	}

	template <typename T>
	template <typename EqualityFunctor>
	bool SList<T>::Remove(const T& value, EqualityFunctor equalityFunctor)
	{
		Iterator it = begin();
		
		for (Iterator prevIt = it; it != end(); ++it)
		{
			if (equalityFunctor(*it, value))
			{
				prevIt._node->_next = it._node->_next;
				if (it._node == _front)
					_front = it._node->_next;
				if (it._node == _back)
					_back = prevIt._node;
				delete(it._node);
				--_size;
				return true;
			}
			prevIt = it;
		}
		return false;
	}
}