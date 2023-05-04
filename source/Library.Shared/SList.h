#pragma once
#include <stdio.h>

namespace FieaGameEngine
{
	/// <summary>
	/// Templated class for a singly forward linked list.
	/// </summary>
	template <typename T>
	class SList final
	{
	public:
		using size_type = std::size_t;
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using rvalue_reference = T&&;

	private:
		/// <summary>
		/// Node struct which can be considered as a singular unit/item in an SList. Contains a data field and a field 
		/// which contains the address of the next node in the SList. 
		/// </summary>
		struct Node final
		{
			/// <summary>
			/// Parameterized constructor for Node that initializes the data members with the passed in arguements.
			/// </summary>
			/// <param name="data"> The data contained by the node/the type of the SList. </param>
			/// <param name="next"> Address of the next node in the list (defaulted to nullptr). </param>
			Node(const T& data, Node* next = nullptr);

			Node* _next{ nullptr };
			T _data;
		};

	public:
		/// <summary>
		/// Iterator struct for SList that wraps a pointer to an element in the list
		/// </summary>
		struct Iterator final
		{
			friend SList;

			using size_type = SList::size_type;
			using difference_type = std::ptrdiff_t;
			using value_type = SList::value_type;
			using reference = SList::reference;
			using const_reference = SList::const_reference;
			using pointer = value_type*;
			using iterator_category = std::forward_iterator_tag;
			

			/// <summary>
			/// Default constructor for Iterator that initializes data members with default values.
			/// </summary>
			Iterator() = default;
			
			/// <summary>
			/// Equal operator to check equality between two iterators
			/// </summary>
			/// <param name="other">The iterator to compare "this" iterator against</param>
			/// <returns> A boolean which is true if the two iterators point to the same address, false if they do not. </returns>
			bool operator==(const Iterator& other) const;

			/// <summary>
			/// Not equal operator to check inequality between two iterators.
			/// </summary>
			/// <param name="other"> The iterator to compare "this" iterator against. </param>
			/// <returns> A boolean which is true if the two iterators do not point to the same address, false if they do. </returns>
			bool operator!=(const Iterator& other) const;

			/// <summary>
			/// Prefix increment operator that makes the iterator point to the next node in the list.
			/// </summary>
			/// <returns> A reference to the modified iterator. </returns>
			Iterator& operator++();

			/// <summary>
			/// Postfix increment operator that makes the iterator point to the next node in the list.
			/// </summary>
			/// <returns> A copy of the iterator before being modified. </returns>
			Iterator operator++(int);

			/// <summary>
			/// Dereference operator for Iterator.
			/// </summary>
			/// <returns> A reference to the data contained by the node that the iterator points to. </returns>
			T& operator*() const;

		private:
			/// <summary>
			/// Paramaterized constructor for Iterator that initializes data members with the passed in arguments.
			/// </summary>
			/// <param name="owner"> The list to which "this" iterator belongs to. </param>
			/// <param name="node"> The node/item that "this" iterator points to (defaulted to nullptr). </param>
			Iterator(const SList& owner, Node* node = nullptr);

			const SList* _owner{ nullptr };
			Node* _node{ nullptr };
		};

		/// <summary>
		/// Iterator struct for SList that wraps a pointer to an element in the list, but the dereference operater returns only a const 
		/// reference to the data held by the node the iterator points to.
		/// </summary>
		struct ConstIterator final
		{
			friend SList;

			using size_type = SList::size_type;
			using difference_type = std::ptrdiff_t;
			using value_type = SList::value_type;
			using reference = SList::reference;
			using const_reference = SList::const_reference;
			using pointer = value_type*;
			using iterator_category = std::forward_iterator_tag;

			/// <summary>
			/// Default constructor for ConstIterator that initializes data members with default values.
			/// </summary>
			ConstIterator() = default;

			/// <summary>
			/// Typecast constructor for ConstIterator which constructs an Iterator to ConstIterator.
			/// </summary>
			/// <param name="other"> The Iterator that the new ConstIterator is supposed to be constructed from. </param>
			explicit ConstIterator(const Iterator& other);

			/// <summary>
			/// Equal operator to check equality between two ConstIterators
			/// </summary>
			/// <param name="other">The ConstIterator to compare "this" ConstIterator against</param>
			/// <returns> A boolean which is true if the two ConstIterators point to the same address, false if they do not. </returns>
			bool operator==(const ConstIterator& other) const;

			/// <summary>
			/// Not equal operator to check inequality between two ConstIterators.
			/// </summary>
			/// <param name="other"> The ConstIterator to compare "this" ConstIterator against. </param>
			/// <returns> A boolean which is true if the two ConstIterators do not point to the same address, false if they do. </returns>
			bool operator!=(const ConstIterator& other) const;

			/// <summary>
			/// Prefix increment operator that makes the ConstIterator point to the next node in the list.
			/// </summary>
			/// <returns> A reference to the modified ConstIterator. </returns>
			ConstIterator& operator++();

			/// <summary>
			/// Postfix ConstIncrement operator that makes the ConstIterator point to the next node in the list.
			/// </summary>
			/// <returns> A copy of the ConstIterator before being modified. </returns>
			ConstIterator operator++(int);

			/// <summary>
			/// Dereference operator for ConstIterator.
			/// </summary>
			/// <returns> A const reference to the data contained by the node that the ConstIterator points to. </returns>
			const T& operator*() const;

		private:
			/// <summary>
			/// Paramaterized constructor for ConstIterator that initializes the data members with the passed in arguements.
			/// </summary>
			/// <param name="owner"> The list to which "this" ConstIterator belongs to. </param>
			/// <param name="node"> The node/item that "this" ConstIterator points to (defaulted to nullptr). </param>
			ConstIterator(const SList& owner, Node* node = nullptr);

			const SList* _owner{ nullptr };
			Node* _node{ nullptr };
		};
		
		/// <summary>
		/// Default constructor for SList that initializes data members with default values.
		/// </summary>
		SList() = default;

		/// <summary>
		/// Destructor for SList that cleans deletes any heap pointers.
		/// </summary>
		~SList();

		/// <summary>
		/// Parameterized constructor for SList that initializes the data members with the passed in initializer list.
		/// </summary>
		/// <param name="list"> Initializer list to initialize the SList with. </param>
		SList(std::initializer_list<T> list);

		/// <summary>
		/// Copy constructor for SList that constructs an SList by deep-copying another SList onto "this" one.
		/// </summary>
		/// <param name="other"> The SList from which "this" SList is to be initialized. </param>
		SList(const SList& other);

		/// <summary>
		/// Move constructor for SList that constructs an SList by taking the memory and values of a temporary SList and giving it "this" one.
		/// </summary>
		/// <param name="other"> An rvalue reference to the SList we wish to move onto "this" one. </param>
		SList(SList&& other) noexcept;

		/// <summary>
		/// Copy assignment operator for SList that deep-copies another SList onto "this" one.
		/// </summary>
		/// <param name="rhs"> The SList we wish to deep-copy into "this" SList. </param>
		/// <returns> A reference to "this" SList. </returns>
		SList& operator=(const SList& rhs);

		/// <summary>
		/// A function to push an item to the front of the SList.
		/// </summary>
		/// <param name="data"> The item to be pushed to the front of the SList. </param>
		void PushFront(const T& data);

		/// <summary>
		/// A function to push an item to the back of the SList.
		/// </summary>
		/// <param name="data"> The item to be pushed to the back of the SList. </param>
		/// <returns> An Iterator pointing to the newly inserted element. </returns>
		Iterator PushBack(const T& data);

		/// <summary>
		/// A function to construct item in-place at the back of the SList.
		/// </summary>
		/// <param name="data"> The arguments needed to construct the item to be pushed to the back of the SList. </param>
		/// <returns> An Iterator pointing to the newly inserted element. </returns>
		template <typename... Args>
		Iterator EmplaceBack(Args... args);

		/// <summary>
		/// A function to delete an item at the front of the SList.
		/// </summary>
		void PopFront();

		/// <summary>
		/// A function to delete an item from the back of the Slist.
		/// </summary>
		void PopBack();

		/// <summary>
		/// A function to clear the entire SList.
		/// </summary>
		void Clear();

		/// <summary>
		/// A function that returns a reference to the item at the front of the SList.
		/// </summary>
		/// <returns> A reference to the item at the front of the SList. Cannot be discarded. </returns>
		[[nodiscard]] T& Front();

		/// <summary>
		///  A function that returns a const reference to the item at the front of the SList.
		/// </summary>
		/// <returns> A const reference to the item at the front of the SList. Cannot be discarded. </returns>
		[[nodiscard]] const T& Front() const;
		
		/// <summary>
		/// A function that returns a reference to the item at the back of the SList.
		/// </summary>
		/// <returns> A reference to the item at the back of the SList. Cannot be discarded. </returns>
		[[nodiscard]] T& Back();

		/// <summary>
		///  A function that returns a const reference to the item at the back of the SList.
		/// </summary>
		/// <returns> A const reference to the item at the back of the SList. Cannot be discarded. </returns>
		[[nodiscard]] const T& Back() const;
		
		/// <summary>
		/// A function that returns the size of the SList.
		/// </summary>
		/// <returns> The size of the SList as a size_t. Cannot be discarded. </returns>
		[[nodiscard]] const std::size_t Size() const;

		/// <summary>
		/// A function that indicates whether or not the SList is empty.
		/// </summary>
		/// <returns> A boolean that is true if the SList is empty, false if it is not. </returns>
		bool IsEmpty() const;

		/// <summary>
		/// A function that returns an Iterator that points to the beginning of the non-const SList.
		/// </summary>
		/// <returns> An Iterator that points to the first Node/beginning of the SList. </returns>
		Iterator begin();

		/// <summary>
		/// A function that returns an Iterator that points to one element past the last element of the non-const SList.
		/// </summary>
		/// <returns> An Iterator that points to one element past the last element of the SList. </returns>
		Iterator end();
		
		/// <summary>
		/// A function that returns a ConstIterator that points to the beginning of the const SList.
		/// </summary>
		/// <returns> A ConstIterator that points to the first Node/beginning of the SList. </returns>
		ConstIterator begin() const;

		/// <summary>
		/// A function that returns a ConstIterator that points to one element past the last element of the const SList.
		/// </summary>
		/// <returns> A ConstIterator that points to one element past the last element of the SList. </returns>
		ConstIterator end() const;

		/// <summary>
		/// A function that returns a ConstIterator that points to the beginning of the SList.
		/// </summary>
		/// <returns> A ConstIterator that points to the first Node/beginning of the SList. </returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// A function that returns a ConstIterator that points to one element past the last element of the SList.
		/// </summary>
		/// <returns> A ConstIterator that points to one element past the last element of the SList. </returns>
		ConstIterator cend() const;

		/// <summary>
		/// A function that inserts an element right after the element that the passed in Iterator points to.
		/// </summary>
		/// <param name="it"> The Iterator which points to the element after which the new data item is to be inserted. </param>
		/// <param name="value"> The data item to be inserted. </param>
		/// <returns> A Iterator that points to the newly inserted element.</returns>
		Iterator InsertAfter(const Iterator& it, const T& value);

		/// <summary>
		/// A function that inserts an element right after the element that the passed in ConstIterator points to.
		/// </summary>
		/// <param name="it"> The ConstIterator which points to the element after which the new data item is to be inserted. </param>
		/// <param name="value"> The data item to be inserted. </param>
		/// <returns> A ConstIterator that points to the newly inserted element.</returns>
		ConstIterator InsertAfter(const ConstIterator& it, const T& value);

		/// <summary>
		/// A function that searches the entire SList for the passed in value and returns an Iterator that points to the element, if found.
		/// </summary>
		/// <param name="value"> The data item to search the SList for. </param>
		/// <param name="value"> A functor that provides an implementation for comparison between two objects of the type passed in. </param>
		/// <returns> An Iterator that points to the element which cointains the data item if found, or else an Iterator that points to nothing. </returns>
		template <typename EqualityFunctor = DefaultEquality<T>>
		Iterator Find(const T& value, EqualityFunctor equalityFunctor = EqualityFunctor{});

		/// <summary>
		/// A function that searches the entire SList for the passed in value and returns a ConstIterator that points to the element, if found.
		/// </summary>
		/// <param name="value"> The data item to search the SList for. </param>
		/// <param name="value"> A functor that provides an implementation for comparison between two objects of the type passed in. </param>
		/// <returns> An ConstIterator that points to the element which cointains the data item if found, or else an ConstIterator that points to nothing. </returns>
		template <typename EqualityFunctor = DefaultEquality<T>>
		ConstIterator Find(const T& value, EqualityFunctor equalityFunctor = EqualityFunctor{}) const;

		/// <summary>
		/// A function that searches for the passed in value and deletes the associated element which contains that value.
		/// </summary>
		/// <param name="value"> The value contained by the element that is to be deleted from the SList. </param>
		/// <param name="value"> A functor that provides an implementation for comparison between two objects of the type passed in. </param>
		/// <returns> A boolean if the element was successfully removed, false if not (most likely due to it not being found). </returns>
		template <typename EqualityFunctor = DefaultEquality<T>>
		bool Remove(const T& value, EqualityFunctor equalityFunctor = EqualityFunctor{});

	private:
		Node* _front { nullptr };
		Node* _back { nullptr };
		std::size_t _size { 0 };
	};
}

#include "SList.inl"