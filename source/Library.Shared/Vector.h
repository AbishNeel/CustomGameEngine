#pragma once
#include <stdio.h>
#include <cassert>

namespace FieaGameEngine
{
	/// <summary>
	/// Templated Vector class.
	/// </summary>
	template <typename T>
	class Vector final
	{
	public:
		/// <summary>
		/// Iterator struct that contains a pointer to an element in the Vector array. 
		/// </summary>
		struct Iterator final
		{
			friend Vector;

			/// <summary>
			/// Default constructor for Iterator.
			/// </summary>
			Iterator() = default;

			/// <summary>
			/// Not equals operator for Iterator.
			/// </summary>
			/// <param name="rhs"> A const reference to the Iterator we want to compare "this" Iterator to. </param>
			/// <returns> True if the Iterators point to different addresses, false if they do. </returns>
			bool operator !=(const Iterator& rhs) const;

			/// <summary>
			/// Equals operator for Iterator.
			/// </summary>
			/// <param name="rhs"> A const reference to the Iterator we want to compare "this" Iterator to. </param>
			/// <returns> True if the Iterators point to the same addresses, false if they do not. </returns>
			bool operator ==(const Iterator& rhs) const;

			/// <summary>
			/// Prefix increment operator which makes the Iterator point to the next element in the Vector.
			/// </summary>
			/// <returns> A reference to "this" Iterator after incrementing. </returns>
			Iterator& operator++();

			/// <summary>
			/// Postfix increment operator which makes the Iterator point to the next element in the Vector.
			/// </summary>
			/// <returns> A copy of "this" Iterator before incrementing. </returns>
			Iterator operator++(int);

			/// <summary>
			/// Dereference operator for Iterator.
			/// </summary>
			/// <returns> A reference to the object stored at the location the Iterator is currently pointing to. </returns>
			T& operator*() const;
		private:
			/// <summary>
			/// Parameterized constructor for Iterator.
			/// </summary>
			/// <param name="owner"> The Vector to which "this" Iterator belongs to. </param>
			/// <param name="item"> The item in the Vector to which "this" Iterator points to. </param>
			Iterator(const Vector& owner, T* item);

			const Vector* _owner{ nullptr };
			T* _item{ nullptr };	
		};

		/// <summary>
		/// ConstIterator struct that contains a pointer to an element in the Vector array.
		/// </summary>
		struct ConstIterator final
		{
			friend Vector; 
			/// <summary>
			/// Default constructor for ConstIterator.
			/// </summary>
			ConstIterator() = default;

			/// <summary>
			/// Type-cast constructor for ConstIterator, which initializes "this" ConstIterator with an Iterator.
			/// </summary>
			/// <param name="it"> Const reference to the Iterator with which which "this" ConstIterator is to be initialized with. </param>
			ConstIterator(const Iterator& it);

			/// <summary>
			/// Not equals operator for ConstIterator.
			/// </summary>
			/// <param name="rhs"> A const reference to the ConstIterator we want to compare "this" ConstIterator to. </param>
			/// <returns> True if the ConstIterators point to different addresses, false if they do. </returns>
			bool operator !=(const ConstIterator& rhs) const;

			/// <summary>
			/// Equals operator for ConstIterator.
			/// </summary>
			/// <param name="rhs"> A const reference to the ConstIterator we want to compare "this" ConstIterator to. </param>
			/// <returns> True if the ConstIterators point to the same addresses, false if they do not. </returns>
			bool operator ==(const ConstIterator& rhs) const;

			/// <summary>
			/// Prefix increment operator which makes the ConstIterator point to the next element in the Vector.
			/// </summary>
			/// <returns> A reference to "this" ConstIterator after incrementing. </returns>
			ConstIterator& operator++();

			/// <summary>
			/// Postfix increment operator which makes the ConstIterator point to the next element in the Vector.
			/// </summary>
			/// <returns> A copy of "this" ConstIterator before incrementing. </returns>
			ConstIterator operator++(int);

			/// <summary>
			/// Dereference operator for ConstIterator.
			/// </summary>
			/// <returns> A const reference to the object stored at the location the ConstIterator is currently pointing to. </returns>
			const T& operator*() const;

			/// <summary>
			/// Greater than operator for ConstIterator.
			/// </summary>
			/// <param name="rhs"> A const reference to the ConstIterator we want to compare "this" ConstIterator to. </param>
			/// <returns> True if the passed in ConstIterator points to a location furthur than "this" ConstIterator, false if not. </returns>
			bool operator<(const ConstIterator& rhs) const;

			/// <summary>
			/// Less than operator for ConstIterator.
			/// </summary>
			/// <param name="rhs"> A const reference to the ConstIterator we want to compare "this" ConstIterator to. </param>
			/// <returns> False if the passed in ConstIterator points to a location furthur than "this" ConstIterator, true if not. </returns>
			bool operator>(const ConstIterator& rhs) const;
		private:
			/// <summary>
			/// Parameterized constructor for ConstIterator.
			/// </summary>
			/// <param name="owner"> The Vector to which "this" ConstIterator belongs to. </param>
			/// <param name="item"> The item in the Vector to which "this" ConstIterator points to. </param>
			ConstIterator(const Vector& owner, T* item);

			const Vector* _owner{ nullptr };
			T* _item{ nullptr };
		};

		/// <summary>
		/// Default constructor for Vector.
		/// </summary>
		Vector() = default;

		/// <summary>
		/// Parameterized constructor for Vector which takes in a capacity to initialize the Vector with.
		/// </summary>
		/// <param name="list"> Capacity with which the Vector is to be initialized. </param>
		Vector(std::size_t capacity);

		/// <summary>
		/// Parameterized constructor for Vector which takes in an initializer list.
		/// </summary>
		/// <param name="list"> Initializer list which contains the elements with which the Vector is to be initialized. </param>
		Vector(std::initializer_list<T> list);

		/// <summary>
		/// Copy constructor for Vector.
		/// </summary>
		/// <param name="other"> A const reference to the Vector which we want to deep-copy onto "this" Vector. </param>
		Vector(const Vector& other);

		/// <summary>
		/// Move constructor for Vector.
		/// </summary>
		/// <param name="other"> rvalue reference to the Vector we wish to move onto "this" one. </param>
		Vector(Vector&& other) noexcept;

		/// <summary>
		/// Copy assignment operator for Vector.
		/// </summary>
		/// <param name="rhs"> A const reference to the Vector which we want to deep-copy onto "this" Vector. </param>
		/// <returns> A reference to "this" Vector after performing the deep-copy. </returns>
		Vector& operator=(const Vector& rhs);

		/// <summary>
		/// Move assignment operator for Vector.
		/// </summary>
		/// <param name="rhs"> An rvalue reference to the Vector we wish to move onto "this" one. </param>
		/// <returns></returns>
		Vector& operator=(Vector&& rhs) noexcept;

		/// <summary>
		/// Destructor for Vector which cleans up any heap allocated memory.
		/// </summary>
		~Vector();

		/// <summary>
		/// Reserve method to reserve a specified size of memory for the Vector to use.
		/// </summary>
		/// <param name="capacity"> The size of memory to be reserved. </param>
		void Reserve(std::size_t capacity);

		/// <summary>
		/// Push back method which appends an element to the back of the Vector by calling the object's copy constructor.
		/// </summary>
		/// <param name="value"> Const reference to the object to be placed at the back of the array. </param>
		void PushBack(const T& value);

		/// <summary>
		/// Push back method which appends an element to the back of the Vector by calling the object's move constructor.
		/// </summary>
		/// <param name="value"> An rvalue reference to the value to be placed at the back of the array. </param>
		void PushBack(T&& value);

		/// <summary>
		/// Appends the object to the back of the Vector. The object's constructor is called only inside the method and hence the object 
		/// is "constructed in place".
		/// </summary>
		template <typename... Args>
		void EmplaceBack(Args&&... args);

		/// <summary>
		/// Front method which returns a reference to the element at the front of the Vector.
		/// </summary>
		/// <returns> A reference to the element at the front of the Vector. Cannot be discarded. </returns>
		[[nodiscard]] T& Front();

		/// <summary>
		/// Back method which returns a reference to the element at the back of the Vector.
		/// </summary>
		/// <returns> A reference to the element at the back of the Vector. Cannot be discarded. </returns>
		[[nodiscard]] T& Back();

		/// <summary>
		/// Front method which returns a const reference to the element at the front of the Vector.
		/// </summary>
		/// <returns> A const reference to the element at the front of the Vector. Cannot be discarded. </returns>
		[[nodiscard]] const T& Front() const;

		/// <summary>
		/// Back method which returns a const reference to the element at the back of the Vector.
		/// </summary>
		/// <returns> A const reference to the element at the back of the Vector. Cannot be discarded. </returns>
		[[nodiscard]] const T& Back() const;

		/// <summary>
		/// PopBack method which deletes the element at the back of the Vector.
		/// </summary>
		void PopBack();

		/// <summary>
		/// Clears the entire array, but does not affect capacity.
		/// </summary>
		void Clear();

		/// <summary>
		/// Shrinks the capacity of the Vector to match the size of the Vector.
		/// </summary>
		void ShrinkToFit();

		/// <summary>
		/// Begin method which returns an Iterator that points to the first element in the Vector.
		/// </summary>
		/// <returns> An Iterator that points to the first element in the Vector.</returns>
		Iterator begin();

		/// <summary>
		/// Begin method which returns a ConstIterator that points to the first element in the Vector.
		/// </summary>
		/// <returns> A ConstIterator that points to the first element in the Vector.</returns>
		ConstIterator begin() const;

		/// <summary>
		/// CBegin method which returns a ConstIterator that points to the first element in the Vector.
		/// </summary>
		/// <returns> A ConstIterator that points to the first element in the Vector.</returns>
		ConstIterator cbegin();

		/// <summary>
		/// End method which returns an Iterator that points to one past the last element in the Vector.
		/// </summary>
		/// <returns></returns>
		Iterator end();

		/// <summary>
		/// End method which returns a ConstIterator that points to one past the last element in the Vector.
		/// </summary>
		/// <returns> A ConstIterator that points to one past the last element in the Vector. </returns>
		ConstIterator end() const;

		/// <summary>
		/// End method which returns a ConstIterator that points to one past the last element in the Vector.
		/// </summary>
		/// <returns> A ConstIterator that points to one past the last element in the Vector. </returns>
		ConstIterator cend();

		/// <summary>
		/// At method that can be used to find an element at a particular index of the Vector.
		/// </summary>
		/// <param name="index"> The index of the element that is to be accessed. </param>
		/// <returns> A reference to the element at the specified index. </returns>
		T& at(size_t index);

		/// <summary>
		/// At method that can be used to find an element at a particular index of the Vector.
		/// </summary>
		/// <param name="index"> The index of the element that is to be accessed. </param>
		/// <returns> A const reference to the element at the specified index. </returns>
		const T& at(size_t index) const;

		/// <summary>
		/// Random access getter that can be used to find an element at a particular index of the Vector.
		/// </summary>
		/// <param name="index"> The index of the element that is to be accessed. </param>
		/// <returns> A reference to the element at the specified index. </returns>
		T& operator[](size_t index);

		/// <summary>
		/// Random access getter that can be used to find an element at a particular index of the Vector.
		/// </summary>
		/// <param name="index"> The index of the element that is to be accessed. </param>
		/// <returns> A const reference to the element at the specified index. </returns>
		const T& operator[](size_t index) const;

		/// <summary>
		/// Find method that can be used to find a specific element in the Vector.
		/// </summary>
		/// <param name="value"> The value which is to be searched for in the Vector, </param>
		/// <param name="equalityFunctor">  A functor that provides an implementation for comparison between two objects of the type passed in. </param>
		/// <returns> An Iterator that points to the first occurance of the element if found, end() Iterator otherwise. </returns>
		template <typename EqualityFunctor = DefaultEquality<T>>
		Iterator Find(const T& value, EqualityFunctor equalityFunctor = EqualityFunctor{});

		/// <summary>
		/// Find method that can be used to find a specific element in the Vector.
		/// </summary>
		/// <param name="value"> The value which is to be searched for in the Vector, </param>
		/// <param name="equalityFunctor">  A functor that provides an implementation for comparison between two objects of the type passed in. </param>
		/// <returns> A ConstIterator that points to the first occurance of the element if found, end() ConstIterator otherwise. </returns>
		template <typename EqualityFunctor = DefaultEquality<T>>
		ConstIterator Find(const T& value, EqualityFunctor equalityFunctor = EqualityFunctor{}) const;

		/// <summary>
		/// Remove method which removes a specified element from the Vector.
		/// </summary>
		/// <param name="value"> Const reference to the element which is to be removed. </param>
		/// <param name="equalityFunctor"> A functor that provides an implementation for comparison between two objects of the type passed in. </param>
		/// <returns> True if the value was successfully removed, false if not. </returns>
		template <typename EqualityFunctor = DefaultEquality<T>>
		bool Remove(const T& value, EqualityFunctor equalityFunctor = EqualityFunctor{});

		/// <summary>
		/// Ranged remove method which removes all elements in a specified range from the Vector.
		/// </summary>
		/// <param name="begin"> The ConstIterator pointing to the start of the removal range (inclusive). </param>
		/// <param name="end"> The ConstIterator pointing to the end of the removal range (exclusive). </param>
		/// <returns> True if the values were successfully removed, false if not. </returns>
		bool Remove(ConstIterator begin, ConstIterator end);

		/// <summary>
		/// Size function which returns the size of the Vector.
		/// </summary>
		/// <returns> The size of the Vector. </returns>
		const std::size_t Size() const;

		/// <summary>
		/// Capacity function which returns the capacity of the Vector.
		/// </summary>
		/// <returns> The capacity of the Vector. </returns>
		const std::size_t Capacity() const;

		/// <summary>
		/// IsEmpty method to check if the Vector is empty.
		/// </summary>
		/// <returns> True if the Vector is empty, false if not. </returns>
		const bool IsEmpty() const;

		bool operator!=(const Vector& rhs) const;
		bool operator==(const Vector& rhs) const;

	private:
		T* _data{ nullptr };
		std::size_t _size{ 0 };
		std::size_t _capacity{ 0 };
	};
}

#include "Vector.inl"