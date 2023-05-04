#include "HashMap.h"

namespace FieaGameEngine
{
	template <typename TKey, typename TValue>
	HashMap<TKey, TValue>::HashMap(std::size_t capacity, HashFunctor hashFunctor, KeyComparator keyComparator)
		: _vector { capacity }, _hashFunctor { hashFunctor }, _keyComparator { keyComparator }
	{
		_vector.Reserve(capacity);
		for (size_t i = 0; i < capacity; ++i)
			_vector.EmplaceBack();
	}

	template <typename TKey, typename TValue>
	HashMap<TKey, TValue>::HashMap(std::initializer_list<PairType> list, std::size_t capacity, HashFunctor hashFunctor, KeyComparator keyComparator)
		: _hashFunctor{ hashFunctor }, _keyComparator { keyComparator }
	{
		_vector.Reserve(capacity);
		for (size_t i = 0; i < capacity; ++i)
			_vector.EmplaceBack();
		
		for (const auto& value : list)
			Insert(value);
	}

	template <typename TKey, typename TValue>
	inline HashMap<TKey, TValue>::Iterator::Iterator(const HashMap& owner, const typename Vector<ChainType>::Iterator vecIt, const typename ChainType::Iterator listIt)
		: _owner { &owner }, _vecIt { vecIt }, _listIt { listIt }
	{

	}

	template <typename TKey, typename TValue>
	inline HashMap<TKey, TValue>::ConstIterator::ConstIterator(const HashMap& owner, const typename Vector<ChainType>::ConstIterator vecIt, const typename ChainType::ConstIterator listIt)
		: _owner{ &owner }, _vecIt{ vecIt }, _listIt{ listIt }
	{

	}

	template <typename TKey, typename TValue>
	inline HashMap<TKey, TValue>::ConstIterator::ConstIterator(const Iterator& it)
		: _owner{ it._owner }, _vecIt{ it._vecIt }, _listIt{ it._listIt }
	{

	}

	template <typename TKey, typename TValue>
	inline std::size_t HashMap<TKey, TValue>::Capacity() const
	{
		return _vector.Capacity();
	}

	template <typename TKey, typename TValue>
	inline std::size_t HashMap<TKey, TValue>::Size() const
	{
		return _size;
	}

	template <typename TKey, typename TValue>
	inline std::size_t HashMap<TKey, TValue>::LoadFactor() const
	{
		return _loadFactor;
	}

	template <typename TKey, typename TValue>
	void HashMap<TKey, TValue>::Clear()
	{
		for (size_t i = 0; i < _vector.Size(); ++i)
			_vector[i].Clear();
		_size = 0;
		_loadFactor = 0;
	}

	template <typename TKey, typename TValue>
	std::pair<typename HashMap<TKey, TValue>::Iterator, bool> HashMap<TKey, TValue>::Insert(const PairType& pair)
	{
		Iterator it = Find(pair.first);
		if (it != end())
			return std::make_pair(it, false);

		ChainType& list = _vector[GetIndex(pair.first)];

		if (list.IsEmpty())
			++_loadFactor;
		++_size;

		return std::make_pair(Iterator{ *this, _vector.Find(list), list.EmplaceBack(std::move(pair)) }, true);
	}

	template <typename TKey, typename TValue>
	bool HashMap<TKey, TValue>::ContainsKey(const TKey& key) const
	{
		return Find(key) != end();
	}

	template <typename TKey, typename TValue>
	TValue& HashMap<TKey, TValue>::At(const TKey& key)
	{
		Iterator it = Find(key);
		if(it == end())
			throw std::runtime_error("Key does not exist.");
		return (*it).second;
	}

	template <typename TKey, typename TValue>
	const TValue& HashMap<TKey, TValue>::At(const TKey& key) const
	{
		ConstIterator it = Find(key);
		if (it == end())
			throw std::runtime_error("Key does not exist.");
		return (*it).second;
	}

	template <typename TKey, typename TValue>
	TValue& HashMap<TKey, TValue>::operator[](const TKey& key)
	{
		if (!ContainsKey(key))
			Insert(std::make_pair(key, TValue{}));
		return At(key);
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::Iterator HashMap<TKey, TValue>::Find(const TKey& key)
	{
		ChainType& list = _vector[GetIndex(key)];

		typename ChainType::Iterator listIt = list.Find(std::make_pair(key, TValue{}), 
			[&](const PairType& lhs, const PairType& rhs) { return _keyComparator(lhs.first, rhs.first); });

		typename Vector<ChainType>::Iterator vecIt;
		if (listIt == list.end())
		{
			vecIt = _vector.end();
			listIt = {};
		}
		else
			vecIt = _vector.Find(list);

		return Iterator{ *this, vecIt, listIt };
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::ConstIterator HashMap<TKey, TValue>::Find(const TKey& key) const
	{
		const ChainType& list = _vector[GetIndex(key)];

		typename ChainType::ConstIterator listIt = list.Find(std::make_pair(key, TValue{}),
			[&](const PairType& lhs, const PairType& rhs) { return _keyComparator(lhs.first, rhs.first); });
		
		typename Vector<ChainType>::ConstIterator vecIt;
		if (listIt == list.end())
		{
			vecIt = _vector.end();
			listIt = {};
		}
		else
			vecIt = _vector.Find(list);

		return ConstIterator{ *this, vecIt, listIt };
	}

	template <typename TKey, typename TValue>
	bool HashMap<TKey, TValue>::Remove(const TKey& key)
	{
		Iterator it = Find(key);
		if (it == end())
			return false;

		ChainType& list = *(it._vecIt);
		list.Remove(*it);

		if (list.IsEmpty())
			--_loadFactor;
		--_size;
		return true;
	}

	template <typename TKey, typename TValue>
	void HashMap<TKey, TValue>::Resize(std::size_t newSize)
	{
		Vector<ChainType> newVector{ newSize };
		for (size_t i = 0; i < newVector.Capacity(); ++i)
			newVector.EmplaceBack();

		_loadFactor = 0;
		Iterator it = begin();
		while (it != end())
		{
			size_t hashCode = _hashFunctor((*it).first) % newVector.Capacity();
			ChainType& list = newVector[hashCode];
			
			if (list.IsEmpty())
				++_loadFactor;

			list.PushBack(*it);
			++it;
		}

		_vector = newVector;
	}

	template<typename TKey, typename TValue>
	size_t HashMap<TKey, TValue>::GetIndex(const TKey& key) const
	{
		return _hashFunctor(key) % _vector.Size();
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::Iterator HashMap<TKey, TValue>::begin()
	{
		if (_size == 0)
			return end();

		typename Vector<ChainType>::Iterator it = _vector.begin();
		while ((*it).IsEmpty())
			++it;
		return Iterator{ *this, it, (*it).begin() };
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::Iterator HashMap<TKey, TValue>::end()
	{
		return Iterator{ *this, _vector.end(), {} };
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::ConstIterator HashMap<TKey, TValue>::begin() const
	{
		if (_size == 0)
			return end();

		typename Vector<ChainType>::ConstIterator it = _vector.begin();
		while ((*it).IsEmpty())
			++it;
		return ConstIterator{ *this, it, (*it).begin() };
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::ConstIterator HashMap<TKey, TValue>::end() const
	{
		return ConstIterator{ *this, _vector.end(), {} };
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::ConstIterator HashMap<TKey, TValue>::cbegin()
	{
		if (_size == 0)
			return cend();

		typename Vector<ChainType>::ConstIterator it = _vector.cbegin();
		while ((*it).IsEmpty())
			++it;
		return ConstIterator{ *this, it, (*it).begin() };
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::ConstIterator HashMap<TKey, TValue>::cend()
	{
		return ConstIterator{ *this, _vector.cend(), {} };
	}


	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::PairType& HashMap<TKey, TValue>::Iterator::operator*() const
	{
		return *_listIt;
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::PairType* HashMap<TKey, TValue>::Iterator::operator->() const
	{
		return &(*_listIt);
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::Iterator& HashMap<TKey, TValue>::Iterator::operator++()
	{
		if (++_listIt == (*_vecIt).end())
		{
			while (typename Vector<ChainType>::ConstIterator{ ++_vecIt } != _owner->_vector.end())
			{
				if (!(*_vecIt).IsEmpty())
				{
					_listIt = (*_vecIt).begin();
					return *this;
				}
			}
			_listIt = {};
		}
		return *this;
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::Iterator HashMap<TKey, TValue>::Iterator::operator++(int)
	{
		Iterator it = *this;
		++(*this);
		return it;
	}

	template <typename TKey, typename TValue>
	inline bool HashMap<TKey, TValue>::Iterator::operator!=(const Iterator& rhs) const
	{
		return _listIt != rhs._listIt || _vecIt != rhs._vecIt || _owner != rhs._owner;
	}

	template <typename TKey, typename TValue>
	inline bool HashMap<TKey, TValue>::Iterator::operator==(const Iterator& rhs) const
	{
		return !operator!=(rhs);
	}

	template <typename TKey, typename TValue>
	const typename HashMap<TKey, TValue>::PairType& HashMap<TKey, TValue>::ConstIterator::operator*() const
	{
		return *_listIt;
	}

	template <typename TKey, typename TValue>
	const typename HashMap<TKey, TValue>::PairType* HashMap<TKey, TValue>::ConstIterator::operator->() const
	{
		return &(*_listIt);
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::ConstIterator& HashMap<TKey, TValue>::ConstIterator::operator++()
	{
		if (++_listIt == (*_vecIt).end())
		{
			while (++_vecIt!= _owner->_vector.end())
			{
				if (!(*_vecIt).IsEmpty())
				{
					_listIt = (*_vecIt).begin();
					return *this;
				}
			}
			_listIt = {};
		}
		return *this;
	}

	template <typename TKey, typename TValue>
	typename HashMap<TKey, TValue>::ConstIterator HashMap<TKey, TValue>::ConstIterator::operator++(int)
	{
		ConstIterator it = *this;
		++(*this);
		return it;
	}

	template <typename TKey, typename TValue>
	inline bool HashMap<TKey, TValue>::ConstIterator::operator!=(const ConstIterator& rhs) const
	{
		return _listIt != rhs._listIt || _vecIt != rhs._vecIt || _owner != rhs._owner;
	}

	template <typename TKey, typename TValue>
	inline bool HashMap<TKey, TValue>::ConstIterator::operator==(const ConstIterator& rhs) const
	{
		return !operator!=(rhs);
	}
}