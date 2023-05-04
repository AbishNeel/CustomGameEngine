#pragma once
#include "Vector.h"
#include "SList.h"
#include "DefaultHash.h"
#include "DefaultEquality.h"

namespace FieaGameEngine
{
	/// <summary>
	/// HashMap which maintains an unordered set of Key-Value pairs
	/// </summary>
	template <typename TKey, typename TValue>
	class HashMap final
	{
	public:
		using PairType = std::pair<const TKey, TValue>;
		using ChainType = SList<PairType>;
		using HashFunctor = std::function <std::size_t(const TKey&)>;
		using KeyComparator = std::function<bool(const TKey&, const TKey&)>;

		/// <summary>
		/// Iterator struct for HashMap which points to a Key-Value pair in the HashMap.
		/// </summary>
		struct Iterator final
		{
			friend HashMap;

			using size_type = std::size_t;
			using difference_type = std::ptrdiff_t;
			using value_type = PairType;
			using reference = PairType&;
			using const_reference = const PairType&;
			using pointer = PairType*;
			using iterator_category = std::forward_iterator_tag;

			Iterator() = default;

			/// <summary>
			/// Not equal to operator for Iterator.
			/// </summary>
			/// <param name="rhs"> A reference to the Iterator we are comparing with "this" one. </param>
			/// <returns> False if both Iterators point to the same Key-Value pair, true if not. </returns>
			bool operator !=(const Iterator& rhs) const;

			/// <summary>
			/// Equal to operator for Iterator.
			/// </summary>
			/// <param name="rhs"> A reference to the Iterator we are comparing with "this" one. </param>
			/// <returns> True if both Iterators point to the same Key-Value pair, false if not. </returns>
			bool operator ==(const Iterator& rhs) const;

			/// <summary>
			/// Prefix increment operator for Iterator which makes it point to the next Key-Value pair in the HashMap.
			/// </summary>
			/// <returns> A reference to "this" Iterator after incrementing. </returns>
			Iterator& operator++();

			/// <summary>
			/// Postfix increment operator for Iterator which makes it point to the next Key-Value pair in the HashMap.
			/// </summary>
			/// <returns> A copy of "this" Iterator before incrementing. </returns>
			Iterator operator++(int);

			/// <summary>
			/// Iterator dereference operator.
			/// </summary>
			/// <returns> A reference to the Key-Value pair that "this" Iterator points to. </returns>
			PairType& operator*() const;

			/// <summary>
			/// Iterator arrow dereference operator.
			/// </summary>
			/// <returns> A pointer to the Key-Value pair that "this" Iterator points to. </returns>
			PairType* operator->() const;

		private:
			/// <summary>
			/// Constructor for Iterator.
			/// </summary>
			/// <param name="owner"> The HashMap that "this" Iterator belongs to. </param>
			/// <param name="vecIt"> The bucket to which "this" Iterator points to. </param>
			/// <param name="listIt"> The SList element "this" Iterator points to. </param>
			Iterator(const HashMap& owner, const typename Vector<ChainType>::Iterator vecIt, const typename ChainType::Iterator listIt);

			const HashMap* _owner{ nullptr };
			typename Vector<ChainType>::Iterator _vecIt {};
			typename ChainType::Iterator _listIt {};
		};

		/// <summary>
		/// ConstIterator struct for HashMap which points to a const Key-Value pair in the HashMap.
		/// </summary>
		struct ConstIterator final
		{
			friend HashMap;

			using size_type = std::size_t;
			using difference_type = std::ptrdiff_t;
			using value_type = PairType;
			using reference = PairType&;
			using const_reference = const PairType&;
			using pointer = PairType*;
			using iterator_category = std::forward_iterator_tag;

			ConstIterator() = default;

			/// <summary>
			/// Typecast constructor for ConstIterator to construct a ConstIterator from an Iterator.
			/// </summary>
			/// <param name="it"> The Iterator with which the ConsIterator is to be constructed. </param>
			ConstIterator(const Iterator& it);

			/// <summary>
			/// Not equal to operator for ConstIterator.
			/// </summary>
			/// <param name="rhs"> A reference to the ConstIterator we are comparing with "this" one. </param>
			/// <returns> False if both ConstIterators point to the same Key-Value pair, true if not. </returns>
			bool operator !=(const ConstIterator& rhs) const;

			/// <summary>
			/// Equal to operator for ConstIterator.
			/// </summary>
			/// <param name="rhs"> A reference to the ConstIterator we are comparing with "this" one. </param>
			/// <returns> True if both ConstIterators point to the same Key-Value pair, false if not. </returns>
			bool operator ==(const ConstIterator& rhs) const;

			/// <summary>
			/// Prefix increment operator for ConstIterator which makes it point to the next Key-Value pair in the HashMap.
			/// </summary>
			/// <returns> A reference to "this" ConstIterator after incrementing. </returns>
			ConstIterator& operator++();

			/// <summary>
			/// Postfix increment operator for ConstIterator which makes it point to the next Key-Value pair in the HashMap.
			/// </summary>
			/// <returns> A copy of "this" ConstIterator before incrementing. </returns>
			ConstIterator operator++(int);

			/// <summary>
			/// ConstIterator dereference operator.
			/// </summary>
			/// <returns> A const reference to the Key-Value pair that "this" ConstIterator points to. </returns>
			const PairType& operator*() const;

			/// <summary>
			/// Iterator arrow dereference operator.
			/// </summary>
			/// <returns> A pointer to the const Key-Value pair that "this" Iterator points to. </returns>
			const PairType* operator->() const;

		private:
			/// <summary>
			/// Constructor for ConstIterator.
			/// </summary>
			/// <param name="owner"> The HashMap that "this" ConstIterator belongs to. </param>
			/// <param name="vecIt"> The bucket to which "this" ConstIterator points to. </param>
			/// <param name="listIt"> The SList element "this" ConstIterator points to. </param>
			ConstIterator(const HashMap& owner, const typename Vector<ChainType>::ConstIterator vecIt, const typename ChainType::ConstIterator listIt);
			
			const HashMap* _owner{ nullptr };
			typename Vector<ChainType>::ConstIterator _vecIt{};
			typename ChainType::ConstIterator _listIt{};
		};
		
		/// <summary>
		/// Constructor for HashMap. 
		/// </summary>
		/// <param name="capacity"> The capacity to be reserved on the HashMap. Defaulted to 11. </param>
		/// <param name="hashFunctor"> The hash function that is to be used by this HashMap for inserts and retrievals of elements. Defaulted to DefaultHash. </param>
		/// <param name="keyComparator"> Function that only compares the keys between two key-value pairs. Defaulted to DefaultEquality. </param>
		explicit HashMap(std::size_t capacity = 11, HashFunctor hashFunctor = DefaultHash<TKey>{}, KeyComparator keyComparator = DefaultEquality<TKey>{});

		/// <summary>
		/// Constructor for HashMap.
		/// </summary>
		/// <param name="list"> The list of PairTypes "this" HashMap is to be initialized with. </param>
		/// <param name="hashFunctor"> The hash function that is to be used by this HashMap for inserts and retrievals of elements. Defaulted to DefaultHash. </param>
		/// <param name="capacity"> The capacity to be reserved on the HashMap. Defaulted to 11. </param>
		/// <param name="keyComparator"> Function that only compares the keys between two key-value pairs. Defaulted to DefaultEquality. </param>
		HashMap(std::initializer_list<PairType> list, std::size_t capacity = 11, HashFunctor hashFunctor = DefaultHash<TKey>{}, KeyComparator keyComparator = DefaultEquality<TKey>{});

		HashMap(const HashMap& other) = default;
		HashMap(HashMap&& other) noexcept = default;
		HashMap& operator=(const HashMap& rhs) = default;
		HashMap& operator=(HashMap&& rhs) noexcept = default;
		~HashMap() = default;

		/// <summary>
		/// Index operator for HashMap. If the key isn't found, a key-value is formed with the key and a default constructed value and inserted.
		/// </summary>
		/// <param name="key"> The key which is to be searched for in the HashMap. </param>
		/// <returns> A reference to the Value that is part of the Key-Value pair that was found/inserted. </returns>
		TValue& operator[](const TKey& key);
		
		/// <summary>
		/// Insert function for HashMap which inserts the passed in pair. If the key already exists, no insert takes place but an Iterator to the existing Key-Value pair is returned.
		/// </summary>
		/// <param name="pair"> A reference to the pair to be inserted. </param>
		/// <returns> An Iterator to the newly inserted/existing element and whether or not the insert took place. </returns>
		std::pair<Iterator, bool> Insert(const PairType& pair);
		
		/// <summary>
		/// At function for HashMap.
		/// </summary>
		/// <param name="key"> The key which is to be searched for in the HashMap. </param>
		/// <returns>  A reference to the Value that is part of the Key-Value pair that was found. </returns>
		TValue& At(const TKey& key);

		/// <summary>
		/// At function for HashMap.
		/// </summary>
		/// <param name="key"> The key which is to be searched for in the HashMap. </param>
		/// <returns> A const reference to the Value that is part of the Key-Value pair that was found. </returns>
		const TValue& At(const TKey& key) const;

		/// <summary>
		/// ContainsKey function for HashMap to check whether a given Key exists in the HashMap or not.
		/// </summary>
		/// <param name="key"> The key which is to be searched for in the HashMap. </param>
		/// <returns> True if the HashMap contains the given key, false if not. </returns>
		bool ContainsKey(const TKey& key) const;

		/// <summary>
		/// Begin method for HashMap.
		/// </summary>
		/// <returns> An Iterator that points to the first element in the HashMap. </returns>
		Iterator begin();

		/// <summary>
		/// End method for HashMap. 
		/// </summary>
		/// <returns> An Iterator that points past the last element in the HashMap. </returns>
		Iterator end();

		/// <summary>
		/// Begin method for HashMap.
		/// </summary>
		/// <returns> A ConstIterator that points to the first element in the HashMap. </returns>
		ConstIterator begin() const;

		/// <summary>
		/// End method for HashMap. 
		/// </summary>
		/// <returns> A ConstIterator that points past the last element in the HashMap. </returns>
		ConstIterator end() const;

		/// <summary>
		/// CBegin method for HashMap.
		/// </summary>
		/// <returns> A ConstIterator that points to the first element in the HashMap. </returns>
		ConstIterator cbegin();

		/// <summary>
		/// CEnd method for HashMap. 
		/// </summary>
		/// <returns> A ConstIterator that points past the last element in the HashMap. </returns>
		ConstIterator cend();

		/// <summary>
		/// Find function for HashMap that searches the HashMap for the given key. 
		/// </summary>
		/// <param name="key"> The key which is to be searched for in the HashMap. </param>
		/// <returns> An Iterator which points to the key-value pair associated with the passed in key. </returns>
		Iterator Find(const TKey& key);

		/// <summary>
		/// Find function for HashMap that searches the HashMap for the given key. 
		/// </summary>
		/// <param name="key"> The key which is to be searched for in the HashMap. </param>
		/// <returns> A ConstIterator which points to the key-value pair associated with the passed in key. </returns>
		ConstIterator Find(const TKey& key) const;

		/// <summary>
		/// Clear method which clears up the entire HashMap. 
		/// </summary>
		void Clear();

		/// <summary>
		/// Resize method to change the capacity of the HashMap while maintaining existing elements.
		/// </summary>
		/// <param name="newSize"> The new size to which the HashMap is to be resized. </param>
		void Resize(std::size_t newSize);

		/// <summary>
		/// Remove method which uses a key to remove the associated key value pair from the HashMap.
		/// </summary>
		/// <param name="key"> The key associated with the key-value pair which is to be removed from the HashMap. </param>
		/// <returns> True if the key was found and associated key-value pair was succesfully removed, false if not. </returns>
		bool Remove(const TKey& key);

		/// <summary>
		/// Capacity function for HashMap.
		/// </summary>
		/// <returns> The capacity of the HashMap. </returns>
		std::size_t Capacity() const;

		/// <summary>
		/// Size function for HashMap.
		/// </summary>
		/// <returns> The size of the HashMap. </returns>
		std::size_t Size() const;

		/// <summary>
		/// LoadFactor function for HashMap.
		/// </summary>
		/// <returns> The load factor of the HashMap. </returns>
		std::size_t LoadFactor() const;
		
	private:

		/// <summary>
		/// Returns the hashed index for a particular key.
		/// </summary>
		/// <param name="key"> The key to be hashed. </param>
		/// <returns> The hashed index of the passed in key for a particular size of the HashMap. </returns>
		size_t GetIndex(const TKey& key) const;

		Vector<ChainType> _vector{};
		std::size_t _size{ 0 };
		std::size_t _loadFactor{ 0 };

		HashFunctor _hashFunctor{ DefaultHash<TKey>{} };
		KeyComparator _keyComparator{ DefaultEquality<TKey>{} };
	};
}

#include "HashMap.inl"