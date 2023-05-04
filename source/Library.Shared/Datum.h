#pragma once
#include "DefaultEquality.h"
#include <stdio.h>
#include <stdexcept>

namespace FieaGameEngine
{
	class Scope;
	/// <summary>
	/// Datum class which serves as a container for various primitive data types.
	/// </summary>
	class Datum final
	{
		friend Scope;
		friend class Attributed;

	public:
		/// <summary>
		/// DatumTypes that enumerates the different data types a Datum can store.
		/// </summary>
		enum class DatumTypes
		{
			Unknown,
			Integer,
			Float,
			String,
			Vector,
			Matrix,
			Pointer,
			Table
		};

		/// <summary>
		/// Constructor that contructs a Datum and sets it's type to the specified type.
		/// </summary>
		/// <param name="type"> The type to initialize the Datum to hold. Defaulted to Unknown. </param>
		explicit Datum(DatumTypes type = DatumTypes::Unknown);

		/// <summary>
		/// Constructor that constructs a Datum with only a single specified integer.
		/// </summary>
		/// <param name="value"> The integer to construct the Datum with. </param>
		Datum(int value);

		/// <summary>
		/// Constructor that constructs a Datum with only a single specified float.
		/// </summary>
		/// <param name="value"> The float to construct the Datum with. </param>
		Datum(float value);

		/// <summary>
		/// Constructor that constructs a Datum with only a single specified string.
		/// </summary>
		/// <param name="value"> The string to construct the Datum with. </param>
		Datum(const std::string& value);

		/// <summary>
		/// Constructor that constructs a Datum with only a single specified vector.
		/// </summary>
		/// <param name="value"> The vector to construct the Datum with. </param>
		Datum(const glm::vec4& value);

		/// <summary>
		/// Constructor that constructs a Datum with only a single specified matrix.
		/// </summary>
		/// <param name="value"> The matrix to construct the Datum with. </param>
		Datum(const glm::mat4& value);

		/// <summary>
		/// Constructor that constructs a Datum with only a single specified RTTI pointer.
		/// </summary>
		/// <param name="value"> The RTTI pointer to construct the Datum with. </param>
		Datum(RTTI* value);

		/// <summary>
		/// Initializer list constructor for Datum to initialize the Datum with a list of integers.
		/// </summary>
		/// <param name="list"> The collection of integers to be pushed to the Datum. </param>
		Datum(std::initializer_list<int> list);

		/// <summary>
		/// Initializer list constructor for Datum to initialize the Datum with a list of floats.
		/// </summary>
		/// <param name="list"> The collection of floats to be pushed to the Datum. </param>
		Datum(std::initializer_list<float> list);

		/// <summary>
		/// Initializer list constructor for Datum to initialize the Datum with a list of strings.
		/// </summary>
		/// <param name="list"> The collection of strings to be pushed to the Datum. </param>
		Datum(std::initializer_list<std::string> list);

		/// <summary>
		/// Initializer list constructor for Datum to initialize the Datum with a list of vectors.
		/// </summary>
		/// <param name="list"> The collection of vectors to be pushed to the Datum. </param>
		Datum(std::initializer_list<glm::vec4> list);

		/// <summary>
		/// Initializer list constructor for Datum to initialize the Datum with a list of matrices.
		/// </summary>
		/// <param name="list"> The collection of matrices to be pushed to the Datum. </param>
		Datum(std::initializer_list<glm::mat4> list);

		/// <summary>
		/// Initializer list constructor for Datum to initialize the Datum with a list of RTTI pointers.
		/// </summary>
		/// <param name="list"> The collection of RTTI pointers to be pushed to the Datum. </param>
		Datum(std::initializer_list<RTTI*> list);

		/// <summary>
		/// Copy constructor to initialize the Datum by copying over the contents of another Datum.
		/// </summary>
		/// <param name="other"> The Datum from which "this" Datum is to be initialized. </param>
		Datum(const Datum& other);

		/// <summary>
		/// Move constructor to construct a Datum by moving the contents of another Datum onto "this" one.
		/// </summary>
		/// <param name="other"> The Datum from which the new Datum is to be constructed. </param>
		Datum(Datum&& other) noexcept;

		/// <summary>
		/// Copy assignment operator to copy the contents of another Datum onto "this" one.
		/// </summary>
		/// <param name="rhs"> The Datum whose contents are to be copied onto "this" one. </param>
		/// <returns> "This" Datum after copying. </returns>
		Datum& operator=(const Datum& other);

		/// <summary>
		/// Move assignment operator to move the contents of another Datum onto "this" one.
		/// </summary>
		/// <param name="rhs"> The Datum whose contents are to be moved onto "this" one. </param>
		/// <returns> "This" Datum after moving. </returns>
		Datum& operator=(Datum&& rhs) noexcept;

		/// <summary>
		/// Destructor for Datum which deallocates any memory owned by the Datum.
		/// </summary>
		~Datum();

		/// <summary>
		/// Scalar assignment operator to assign the first element of the Datum to the passed in integer. If Datum is empty, an element is contructed at the front.
		/// </summary>
		/// <param name="value"> The integer value to assign to the first element in the Datum. </param>
		/// <returns> A reference to the Datum after the assignment operation. </returns>
		/// <exception cref="runtime_error"> Throws if the type of the Datum is not that of an integer or not unknown. </exception>
		Datum& operator=(int value);

		/// <summary>
		/// Scalar assignment operator to assign the first element of the Datum to the passed in float. If Datum is empty, an element is contructed at the front.
		/// </summary>
		/// <param name="value"> The float value to assign to the first element in the Datum. </param>
		/// <returns> A reference to the Datum after the assignment operation. </returns>
		/// <exception cref="runtime_error"> Throws if the type of the Datum is not that of a float or not unknown. </exception>
		Datum& operator=(float value);

		/// <summary>
		/// Scalar assignment operator to assign the first element of the Datum to the passed in string. If Datum is empty, an element is contructed at the front.
		/// </summary>
		/// <param name="value"> The string value to assign to the first element in the Datum. </param>
		/// <returns> A reference to the Datum after the assignment operation. </returns>
		/// <exception cref="runtime_error"> Throws if the type of the Datum is not that of a string or not unknown. </exception>
		Datum& operator=(const std::string& value);

		/// <summary>
		/// Scalar assignment operator to assign the first element of the Datum to the passed in vector. If Datum is empty, an element is contructed at the front.
		/// </summary>
		/// <param name="value"> The vector value to assign to the first element in the Datum. </param>
		/// <returns> A reference to the Datum after the assignment operation. </returns>
		/// <exception cref="runtime_error"> Throws if the type of the Datum is not that of a vector or not unknown. </exception>
		Datum& operator=(const glm::vec4& value);

		/// <summary>
		/// Scalar assignment operator to assign the first element of the Datum to the passed in matrix. If Datum is empty, an element is contructed at the front.
		/// </summary>
		/// <param name="value"> The matrix value to assign to the first element in the Datum. </param>
		/// <returns> A reference to the Datum after the assignment operation. </returns>
		/// <exception cref="runtime_error"> Throws if the type of the Datum is not that of a matrix or not unknown. </exception>
		Datum& operator=(const glm::mat4& value);

		/// <summary>
		/// Scalar assignment operator to assign the first element of the Datum to the passed in RTTI pointer. If Datum is empty, an element is contructed at the front.
		/// </summary>
		/// <param name="value"> The RTTI pointer value to assign to the first element in the Datum. </param>
		/// <returns> A reference to the Datum after the assignment operation. </returns>
		/// <exception cref="runtime_error"> Throws if the type of the Datum is not that of an RTTI pointer or not unknown. </exception>
		Datum& operator=(RTTI* value);

		/// <summary>
		/// Function to allocate memory for the Datum.
		/// </summary>
		/// <param name="capacity"> The number of memory blocks to be allocated. </param>
		void Reserve(size_t capacity);

		/// <summary>
		/// PushBack function to push an integer to the back of the Datum.
		/// </summary>
		/// <param name="value"> The integer value to be pushed. </param>
		void PushBack(int value);

		/// <summary>
		/// PushBack function to push a floating point value to the back of the Datum.
		/// </summary>
		/// <param name="value"> The floating point value to be pushed. </param>
		void PushBack(float value);

		/// <summary>
		/// PushBack function to push a string to the back of the Datum.
		/// </summary>
		/// <param name="value"> A reference to the string value to be pushed. </param>
		void PushBack(const std::string& value);

		/// <summary>
		/// PushBack function to push a Vec4 to the back of the Datum.
		/// </summary>
		/// <param name="value"> The Vec4 value to be pushed. </param>
		void PushBack(const glm::vec4& value);

		/// <summary>
		/// PushBack function to push a Mat4 to the back of the Datum.
		/// </summary>
		/// <param name="value"> The Mat4 value to be pushed. </param>
		void PushBack(const glm::mat4& value);

		/// <summary>
		/// PushBack function to push an RTTI pointer to the back of the Datum.
		/// </summary>
		/// <param name="value"> The RTTI pointer to be pushed. </param>
		void PushBack(RTTI* value);

		/// <summary>
		/// PushBacl function to push a Vector to the back of the Datum from a string.
		/// </summary>
		/// <param name="vecString"> The string to be converted to a Vector. </param>
		void PushBackVectorFromString(const std::string& vecString);

		/// <summary>
		/// PushBacl function to push a Matrix to the back of the Datum from a string.
		/// </summary>
		/// <param name="matString"> The string to be converted to a Matrix. </param>
		void PushBackMatrixFromString(const std::string& matString);

		/// <summary>
		/// Function that removes the element at the back of the Datum.
		/// </summary>
		/// <exception cref="runtime_error"> Throws if called when the Datum is empty. </exception>
		void PopBack();

		/// <summary>
		/// Operator[] to get the nested Scope at a specified index.
		/// </summary>
		/// <param name="index"> The index of the nested Scope trying to be accessed. </param>
		/// <returns> A reference to the Scope found at the specified index. </returns>
		Scope& operator[](const size_t index);

		/// <summary>
		/// Const operator[] to get the nested Scope at a specified index.
		/// </summary>
		/// <param name="index"> The index of the nested Scope trying to be accessed. </param>
		/// <returns> A const reference to the Scope found at the specified index. </returns>
		const Scope& operator[](const size_t index) const;

		/// <summary>
		/// Get function to get a reference to the element at the specified index.
		/// </summary>
		/// <returns> A reference to the value at the specified index. </returns>
		/// <typeparam name="T"> The data type trying to be accessed. </typeparam>
		/// <exception cref="runtime error"> Throws if Datum type doesn't match the type trying to be accessed. </exception>
		/// <exception cref="runtime error"> Throws if the specified index is greater than or equal to the size of the Datum. </exception>
		template <typename T>
		T& Get(size_t index = 0);

		/// <summary>
		/// Get function to get a const reference to the element at the specified index.
		/// </summary>
		/// <returns> A const reference to the value at the specified index. </returns>
		/// <typeparam name="T"> The data type trying to be accessed. </typeparam>
		/// <exception cref="runtime error"> Throws if Datum type doesn't match the type trying to be accessed. </exception>
		/// <exception cref="runtime error"> Throws if the specified index is greater than or equal to the size of the Datum. </exception>
		template <typename T>
		const T& Get(size_t index = 0) const;

		/// <summary>
		/// Set function to set the element at a given index to the passed in integer.
		/// </summary>
		/// <param name="value"> The integer to set the value at the given index. </param>
		/// <param name="index"> The index at which the element is to be set. Defaulted 0. </param>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of an integer. </exception>
		/// <exception cref="out_of_range"> Throws if the passed in index is greater than or equal to the size of the Datum. </exception>
		void Set(int value, size_t index = 0);

		/// <summary>
		/// Set function to set the element at a given index to the passed in float.
		/// </summary>
		/// <param name="value"> The float to set the value at the given index. </param>
		/// <param name="index"> The index at which the element is to be set. Defaulted 0. </param>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a float. </exception>
		/// <exception cref="out_of_range"> Throws if the passed in index is greater than or equal to the size of the Datum. </exception>
		void Set(float value, size_t index = 0);

		/// <summary>
		/// Set function to set the element at a given index to the passed in string.
		/// </summary>
		/// <param name="value"> The string to set the value at the given index. </param>
		/// <param name="index"> The index at which the element is to be set. Defaulted 0. </param>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a string. </exception>
		/// <exception cref="out_of_range"> Throws if the passed in index is greater than or equal to the size of the Datum. </exception>
		void Set(const std::string& value, size_t index = 0);

		/// <summary>
		/// Set function to set the element at a given index to the passed in vector.
		/// </summary>
		/// <param name="value"> The vector to set the value at the given index. </param>
		/// <param name="index"> The index at which the element is to be set. Defaulted 0. </param>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a vector. </exception>
		/// <exception cref="out_of_range"> Throws if the passed in index is greater than or equal to the size of the Datum. </exception>
		void Set(const glm::vec4& value, size_t index = 0);

		/// <summary>
		/// Set function to set the element at a given index to the passed in matrix.
		/// </summary>
		/// <param name="value"> The matrix to set the value at the given index. </param>
		/// <param name="index"> The index at which the element is to be set. Defaulted 0. </param>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a matrix. </exception>
		/// <exception cref="out_of_range"> Throws if the passed in index is greater than or equal to the size of the Datum. </exception>
		void Set(const glm::mat4& value, size_t index = 0);

		/// <summary>
		/// Set function to set the element at a given index to the passed in RTTI pointer.
		/// </summary>
		/// <param name="value"> The RTTI pointer to set the value at the given index. </param>
		/// <param name="index"> The index at which the element is to be set. Defaulted 0. </param>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of an RTTI pointer. </exception>
		/// <exception cref="out_of_range"> Throws if the passed in index is greater than or equal to the size of the Datum. </exception>
		void Set(RTTI* value, size_t index = 0);

		/// <summary>
		/// Function to set the type of data the Datum can store. Once the type is set it cannot be changed.
		/// </summary>
		/// <param name="type"> The type of data the Datum can store. </param>
		void SetType(DatumTypes type);

		/// <summary>
		/// Assigns an external array of integers to the Datum. The Datum does not "own" the memory of the array assigned to it.
		/// </summary>
		/// <param name="array"> Pointer to the start of array of integers. </param>
		/// <param name="size"> The size of the array. </param>
		/// <exception cref="out_of_range"> Throws if the passed in index is greater than or equal to the size of the Datum. </exception>
		void SetStorage(int* array, size_t size);

		/// <summary>
		/// Assigns an external array of floats to the Datum. The Datum does not "own" the memory of the array assigned to it.
		/// </summary>
		/// <param name="array"> Pointer to the start of array of floats. </param>
		/// <param name="size"> The size of the array. </param>
		/// <exception cref="out_of_range"> Throws if the passed in index is greater than or equal to the size of the Datum. </exception>
		void SetStorage(float* array, size_t size);

		/// <summary>
		/// Assigns an external array of strings to the Datum. The Datum does not "own" the memory of the array assigned to it.
		/// </summary>
		/// <param name="array"> Pointer to the start of array of strings. </param>
		/// <param name="size"> The size of the array. </param>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a string. </exception>
		void SetStorage(std::string* array, size_t size);

		/// <summary>
		/// Assigns an external array of vectors to the Datum. The Datum does not "own" the memory of the array assigned to it.
		/// </summary>
		/// <param name="array"> Pointer to the start of array of vectors. </param>
		/// <param name="size"> The size of the array. </param>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a vector. </exception>
		void SetStorage(glm::vec4* array, size_t size);

		/// <summary>
		/// Assigns an external array of matrices to the Datum. The Datum does not "own" the memory of the array assigned to it.
		/// </summary>
		/// <param name="array"> Pointer to the start of array of matrices. </param>
		/// <param name="size"> The size of the array. </param>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a matrix. </exception>
		void SetStorage(glm::mat4* array, size_t size);

		/// <summary>
		/// Assigns an external array of RTTI pointers to the Datum. The Datum does not "own" the memory of the array assigned to it.
		/// </summary>
		/// <param name="array"> Pointer to the start of array of RTTI pointers. </param>
		/// <param name="size"> The size of the array. </param>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of an RTTI pointer. </exception>
		void SetStorage(RTTI** array, size_t size);

		/// <summary>
		/// Find function to find the index of a specified integer.
		/// </summary>
		/// <param name="value"> The value to be searched. </param>
		/// <returns> The index at which the specified value is stored. </returns>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of an integer. </exception>
		/// <exception cref="out_of_bounds"> Throws if the passed in value was not found. </exception>
		size_t Find(int value) const;

		/// <summary>
		/// Find function to find the index of a specified float.
		/// </summary>
		/// <param name="value"> The value to be searched. </param>
		/// <returns> The index at which the specified value is stored. </returns>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a float. </exception>
		/// <exception cref="out_of_bounds"> Throws if the passed in value was not found. </exception>
		size_t Find(float value) const;

		/// <summary>
		/// Find function to find the index of a specified string.
		/// </summary>
		/// <param name="value"> The value to be searched. </param>
		/// <returns> The index at which the specified value is stored. </returns>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a string. </exception>
		/// <exception cref="out_of_bounds"> Throws if the passed in value was not found. </exception>
		size_t Find(const std::string& value) const;

		/// <summary>
		/// Find function to find the index of a specified vector.
		/// </summary>
		/// <param name="value"> The value to be searched. </param>
		/// <returns> The index at which the specified value is stored. </returns>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a vector. </exception>
		/// <exception cref="out_of_bounds"> Throws if the passed in value was not found. </exception>
		size_t Find(const glm::vec4& value) const;

		/// <summary>
		/// Find function to find the index of a specified matrix.
		/// </summary>
		/// <param name="value"> The value to be searched. </param>
		/// <returns> The index at which the specified value is stored. </returns>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a matrix. </exception>
		/// <exception cref="out_of_bounds"> Throws if the passed in value was not found. </exception>
		size_t Find(const glm::mat4& value) const;

		/// <summary>
		/// Find function to find the index of a specified RTTI pointer.
		/// </summary>
		/// <param name="value"> The value to be searched. </param>
		/// <returns> The index at which the specified value is stored. </returns>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of an RTTI pointer. </exception>
		/// <exception cref="out_of_bounds"> Throws if the passed in value was not found. </exception>
		size_t Find(const RTTI* value) const;

		/// <summary>
		/// Removes the element at the specified index.
		/// </summary>
		/// <param name="index"> The index of the element to be removed. </param>
		/// <returns> True if the element was succesfully removed, false if the element was not found. </returns>
		/// <exception cref="runtime_error"> Throws if the type of the Datum is not defined. </exception>
		/// <exception cref="out_of_bounds"> Throws if the passed in index is out of bounds. </exception>
		bool RemoveAt(size_t index);

		/// <summary>
		/// Removes an integer by searching the Datum for the specified value.
		/// </summary>
		/// <param name="value"> The value of the integer to be removed. </param>
		/// <returns> True if the element was succesfully removed, false if the element was not found. </returns>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of an integer. </exception>
		bool Remove(int value);

		/// <summary>
		/// Removes a float by searching the Datum for the specified value.
		/// </summary>
		/// <param name="value"> The value of the float to be removed. </param>
		/// <returns> True if the element was succesfully removed, false if the element was not found. </returns>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a float. </exception>
		bool Remove(float value);

		/// <summary>
		/// Removes a string by searching the Datum for the specified value.
		/// </summary>
		/// <param name="value"> The value of the string to be removed. </param>
		/// <returns> True if the element was succesfully removed, false if the element was not found. </returns>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a string. </exception>
		bool Remove(const std::string& value);

		/// <summary>
		/// Removes a vector by searching the Datum for the specified value.
		/// </summary>
		/// <param name="value"> The value of the vector to be removed. </param>
		/// <returns> True if the element was succesfully removed, false if the element was not found. </returns>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a vector. </exception>
		bool Remove(const glm::vec4& value);

		/// <summary>
		/// Removes a matrix by searching the Datum for the specified value.
		/// </summary>
		/// <param name="value"> The value of the matrix to be removed. </param>
		/// <returns> True if the element was succesfully removed, false if the element was not found. </returns>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a matrix. </exception>
		bool Remove(const glm::mat4& value);

		/// <summary>
		/// Removes an RTTI pointer by searching the Datum for the specified value.
		/// </summary>
		/// <param name="value"> The value of the RTTI pointer to be removed. </param>
		/// <returns> True if the element was succesfully removed, false if the element was not found. </returns>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of an RTTI pointer. </exception>
		bool Remove(const RTTI* value);

		/// <summary>
		/// Template function to get a reference to the element at the front of the Datum.
		/// </summary>
		/// <returns> A reference to the value at the Front of the Datum. </returns>
		/// <typeparam name="T"> The data type trying to be accessed. </typeparam>
		/// <exception cref="runtime error"> Throws if Datum type doesn't match the type trying to be accessed. </exception>
		/// <exception cref="runtime error"> Throws if Datum is empty. </exception>
		template <typename T>
		T& Front();

		/// <summary>
		/// Template function to get a reference to the element at the back of the Datum.
		/// </summary>
		/// <typeparam name="T"> The data type trying to be accessed. </typeparam>
		/// <returns> A reference to the value at the back of the Datum. </returns>
		/// <exception cref="runtime error"> Throws if Datum type doesn't match the type trying to be accessed. </exception>
		/// <exception cref="runtime error"> Throws if Datum is empty. </exception>
		template <typename T>
		T& Back();

		/// <summary>
		/// Template function to get a const reference to the element at the front of the Datum.
		/// </summary>
		/// <returns> A const reference to the value at the Front of the Datum. </returns>
		/// <typeparam name="T"> The data type trying to be accessed. </typeparam>
		/// <exception cref="runtime error"> Throws if Datum type doesn't match the type trying to be accessed. </exception>
		/// <exception cref="runtime error"> Throws if Datum is empty. </exception>
		template <typename T>
		const T& Front() const;

		/// <summary>
		/// Template function to get a const reference to the element at the back of the Datum.
		/// </summary>
		/// <typeparam name="T"> The data type trying to be accessed. </typeparam>
		/// <returns> A const reference to the value at the back of the Datum. </returns>
		/// <exception cref="runtime error"> Throws if Datum type doesn't match the type trying to be accessed. </exception>
		/// <exception cref="runtime error"> Throws if Datum is empty. </exception>
		template <typename T>
		const T& Back() const;

		/// <summary>
		/// Clear function that clears the Datum without affecting the capacity.
		/// </summary>
		void Clear();

		/// <summary>
		/// Resizes the capacity of the Datum. If the newsize is lesser than the current size, the remaining elements get deleted. If it is greater, the remaining elements get default constructed.
		/// The size and capacity of the Datum after resizing are the same.
		/// </summary>
		/// <param name="newSize"> The new size of the Datum. </param>
		/// <exception cref="runtime_error"> Throws if the Datum type is not set or the Datum has not memory assigned. </exception>
		void Resize(size_t newSize);

		/// <summary>
		/// Function to set the integer at a specified index from a string.
		/// </summary>
		/// <param name="index"> The index at which the element is to be set. Defaulted 0. </param>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of an integer. </exception>
		/// <exception cref="out_of_range"> Throws if the passed in index is greater than or equal to the size of the Datum. </exception>
		void SetIntFromString(const std::string& string, size_t index = 0);

		/// <summary>
		/// Function to set the float at a specified index from a string.
		/// </summary>
		/// <param name="index"> The index at which the element is to be set. Defaulted 0. </param>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a float. </exception>
		/// <exception cref="out_of_range"> Throws if the passed in index is greater than or equal to the size of the Datum. </exception>
		void SetFloatFromString(const std::string& string, size_t index = 0);

		/// <summary>
		/// Function to set the vector at a specified index from a string.
		/// </summary>
		/// <param name="index"> The index at which the element is to be set. Defaulted 0. </param>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a vector. </exception>
		/// <exception cref="out_of_range"> Throws if the passed in index is greater than or equal to the size of the Datum. </exception>
		void SetVecFromString(const std::string& string, size_t index = 0);

		/// <summary>
		/// Function to set the matrix at a specified index from a string.
		/// </summary>
		/// <param name="index"> The index at which the element is to be set. Defaulted 0. </param>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a matrix. </exception>
		/// <exception cref="out_of_range"> Throws if the passed in index is greater than or equal to the size of the Datum. </exception>
		void SetMatFromString(const std::string& string, size_t index = 0);

		/// <summary>
		/// ToString method to convert the element at a specified index to a string.
		/// </summary>
		/// <param name="index"> The index of the element to be converted to a string. Defaulted to 0. </param>
		/// <returns> The string equivalent of the string at the specified index. </returns>
		/// <exception cref="out_of_range"> Throws if the index is greater than or less than the size of the Datum. </exception>
		std::string ToString(size_t index = 0) const;

		/// <summary>
		/// Function that gets the type of data being stored by the Datum.
		/// </summary>
		/// <returns> The type of data being stored by the Datum. </returns>
		DatumTypes Type() const;

		/// <summary>
		/// Function that gets the number of elements in the Datum.
		/// </summary>
		/// <returns> The number of elements being stored by the Datum. </returns>
		size_t Size() const;

		/// <summary>
		/// Function that gets the amount of data allocated to the Datum.
		/// </summary>
		/// <returns> The amount of data allocated to the Datum. </returns>
		size_t Capacity() const;

		/// <summary>
		/// Function to check if the Datum stores external data.
		/// </summary>
		/// <returns> Weather or not the Datum stores external data. </returns>
		bool IsExternal() const;

		/// <summary>
		/// Not equals operator that checks equivalence between two Datums by comparing their sizes and respective elements.
		/// </summary>
		/// <param name="rhs"> The Datum which is to be compared with "this" Datum. </param>
		/// <returns> True if they are not equivalent, false if they are. </returns>
		bool operator!=(const Datum& rhs) const;

		/// <summary>
		/// Not equals operator that checks equivalence between a Datum and an integer. Only works if the Datum is scalar and is of type integer.
		/// </summary>
		/// <param name="rhs"> The integer which is to be compared with "this" Datum. </param>
		/// <returns> True if the first and only element of the Datum is not equivalent to the passed in value, false if they are. </returns>
		bool operator!=(int rhs) const;

		/// <summary>
		/// Not equals operator that checks equivalence between a Datum and a float. Only works if the Datum is scalar and is of type float.
		/// </summary>
		/// <param name="rhs"> The float which is to be compared with "this" Datum. </param>
		/// <returns> True if the first and only element of the Datum is not equivalent to the passed in value, false if they are. </returns>
		bool operator!=(float rhs) const;

		/// <summary>
		/// Not equals operator that checks equivalence between a Datum and a string. Only works if the Datum is scalar and is of type string.
		/// </summary>
		/// <param name="rhs"> The string which is to be compared with "this" Datum. </param>
		/// <returns> True if the first and only element of the Datum is not equivalent to the passed in value, false if they are. </returns>
		bool operator!=(const std::string& rhs) const;

		/// <summary>
		/// Not equals operator that checks equivalence between a Datum and a vector. Only works if the Datum is scalar and is of type vector.
		/// </summary>
		/// <param name="rhs"> The vector which is to be compared with "this" Datum. </param>
		/// <returns> True if the first and only element of the Datum is not equivalent to the passed in value, false if they are. </returns>
		bool operator!=(const glm::vec4& rhs) const;

		/// <summary>
		/// Not equals operator that checks equivalence between a Datum and a matrix. Only works if the Datum is scalar and is of type matrix.
		/// </summary>
		/// <param name="rhs"> The matrix which is to be compared with "this" Datum. </param>
		/// <returns> True if the first and only element of the Datum is not equivalent to the passed in value, false if they are. </returns>
		bool operator!=(const glm::mat4& rhs) const;

		/// <summary>
		/// Not equals operator that checks equivalence between a Datum and an RTTI pointer. Only works if the Datum is scalar and is of type pointer.
		/// </summary>
		/// <param name="rhs"> The RTTI pointer which is to be compared with "this" Datum. </param>
		/// <returns> True if the first and only element of the Datum is not equivalent to the passed in value, false if they are. </returns>
		bool operator!=(const RTTI* rhs) const;

		/// <summary>
		/// Equals operator that checks equivalence between two Datums by comparing their sizes and respective elements.
		/// </summary>
		/// <param name="rhs"> The Datum which is to be compared with "this" Datum. </param>
		/// <returns> True if they are equivalent, false if they are not. </returns>
		bool operator==(const Datum& rhs) const;

		/// <summary>
		/// Equals operator that checks equivalence between a Datum and an integer. Only works if the Datum is scalar and is of type integer.
		/// </summary>
		/// <param name="rhs"> The integer which is to be compared with "this" Datum. </param>
		/// <returns> True if the first and only element of the Datum is equivalent to the passed in value, false if they are not. </returns>
		bool operator==(int rhs) const;

		/// <summary>
		/// Equals operator that checks equivalence between a Datum and a float. Only works if the Datum is scalar and is of type float.
		/// </summary>
		/// <param name="rhs"> The float which is to be compared with "this" Datum. </param>
		/// <returns> True if the first and only element of the Datum is equivalent to the passed in value, false if they are not. </returns>
		bool operator==(float rhs) const;

		/// <summary>
		/// Equals operator that checks equivalence between a Datum and a string. Only works if the Datum is scalar and is of type string.
		/// </summary>
		/// <param name="rhs"> The string which is to be compared with "this" Datum. </param>
		/// <returns> True if the first and only element of the Datum is equivalent to the passed in value, false if they are not. </returns>
		bool operator==(const std::string& rhs) const;

		/// <summary>
		/// Not equals operator that checks equivalence between a Datum and a vector. Only works if the Datum is scalar and is of type vector.
		/// </summary>
		/// <param name="rhs"> The vector which is to be compared with "this" Datum. </param>
		/// <returns> True if the first and only element of the Datum is equivalent to the passed in value, false if they are not. </returns>
		bool operator==(const glm::vec4& rhs) const;

		/// <summary>
		/// Equals operator that checks equivalence between a Datum and a matrix. Only works if the Datum is scalar and is of type matrix.
		/// </summary>
		/// <param name="rhs"> The matrix which is to be compared with "this" Datum. </param>
		/// <returns> True if the first and only element of the Datum is equivalent to the passed in value, false if they are not. </returns>
		bool operator==(const glm::mat4& rhs) const;

		/// <summary>
		/// Equals operator that checks equivalence between a Datum and an RTTI pointer. Only works if the Datum is scalar and is of type pointer.
		/// </summary>
		/// <param name="rhs"> The RTTI pointer which is to be compared with "this" Datum. </param>
		/// <returns> True if the first and only element of the Datum is equivalent to the passed in value, false if they are not. </returns>
		bool operator==(const RTTI* rhs) const;
	
	private:

		/// <summary>
		/// Validates if the type of Datum is either not set yet, or if it matches the passed in types matches the Datum type. Exception is thrown if validation fails.
		/// </summary>
		/// <param name="type"> The type to validate against the type of this Datum. </param>
		/// <exception cref="runtime_error"> Throws if the type passed in doesn't match the type of the Datum, or if the passed in type is not unknown (not set). </exception>
		void ValidateType(DatumTypes type) const;

		/// <summary>
		/// Validates that the passed in index is not out of bounds.
		/// </summary>
		/// <param name="index"> The index against which bounds checking is to performed. </param>
		/// <exception cref="out_of_range"> Throws if the passed in index is greater than equal to the size of the Datum. </exception>
		void ValidateIndex(size_t index) const;

		/// <summary>
		/// PushBack function to push a Scope pointer to the back of the Datum.
		/// </summary>
		/// <param name="value"> The Scope pointer to be pushed. </param>
		void PushBackScope(Scope* value);

		/// <summary>
		/// Set function to set the element at a given index to the passed in Scope pointer.
		/// </summary>
		/// <param name="value"> The Scope pointer to set the value at the given index. </param>
		/// <param name="index"> The index at which the element is to be set. Defaulted 0. </param>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a Scope pointer. </exception>
		/// <exception cref="out_of_range"> Throws if the passed in index is greater than or equal to the size of the Datum. </exception>
		void Set(Scope* value, size_t index = 0);

		/// <summary>
		/// Removes a Scope pointer by searching the Datum for the specified value.
		/// </summary>
		/// <param name="value"> The value of the Scope pointer to be removed. </param>
		/// <returns> True if the element was succesfully removed, false if the element was not found. </returns>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a Scope pointer. </exception>
		bool Remove(const Scope* value);

		/// <summary>
		/// Find function to find the index of a specified Scope pointer.
		/// </summary>
		/// <param name="value"> The value to be searched. </param>
		/// <returns> The index at which the specified value is stored. </returns>
		/// <exception cref="runtime_error"> Throws if the Datum type is not that of a Scope pointer. </exception>
		/// <exception cref="out_of_bounds"> Throws if the passed in value was not found. </exception>
		size_t Find(const Scope* value) const;

		/// <summary>
		/// Scalar assignment operator to assign the first element of the Datum to the passed in Scope pointer. If Datum is empty, an element is contructed at the front.
		/// </summary>
		/// <param name="value"> The Scope pointer value to assign to the first element in the Datum. </param>
		/// <returns> A reference to the Datum after the assignment operation. </returns>
		/// <exception cref="runtime_error"> Throws if the type of the Datum is not that of an Scope pointer or not unknown. </exception>
		Datum& operator=(Scope*& value);

		/// <summary>
		/// Assigns an external array of any type to the Datum. The Datum does not "own" the memory of the array assigned to it.
		/// </summary>
		/// <param name="array"> Pointer to the start of array. </param>
		/// <param name="size"> The size of the array. </param>
		/// <param name="type"> The type of data held by the array. </param>
		void SetStorage(void* array, size_t size, DatumTypes type);

		union DatumValues final
		{
			void* vp;
			int* i;
			float* f;
			std::string* s;
			glm::vec4* v;
			glm::mat4* m;
			RTTI** p;
			Scope** t;
		};

		DatumValues _data{ _data.vp };
		std::size_t _size{ 0 };
		std::size_t _capacity{ 0 };
		DatumTypes _type{ DatumTypes::Unknown };
		bool _IsExternal{ false };

		static constexpr std::size_t DatumTypeSizes[8] =
		{
			0,
			sizeof(std::int32_t),
			sizeof(float),
			sizeof(std::string),
			sizeof(glm::vec4),
			sizeof(glm::mat4),
			sizeof(RTTI*),
			sizeof(Scope*)
		};
	};
}

#include "Datum.inl"