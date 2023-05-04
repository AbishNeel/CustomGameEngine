#pragma once
#include "Datum.h"
#include "Vector.h"
#include "HashMap.h"
#include <gsl/gsl>
#include <stdio.h>

namespace FieaGameEngine
{
	class Scope : public FieaGameEngine::RTTI
	{
		RTTI_DECLARATIONS(Scope, FieaGameEngine::RTTI);

	public:
		using NestedScopeFunction = std::function<void(Datum&)>;

		/// <summary>
		/// Constructor for Scope.
		/// </summary>
		/// <param name="capacity"> The capacity with which the Scope is to be initialized with. Defaulted to 17. </param>
		explicit Scope(std::size_t capacity = 17);

		/// <summary>
		/// Copy constructor for Scope, to construct a Scope by copying over the contents of an existing Scope.
		/// </summary>
		/// <param name="other"> Reference to the Scope to be copied over to the newly constrcuted Scope. </param>
		Scope(const Scope& other);

		/// <summary>
		/// Move constructor for Scope, to construct a Scope by moving the contents of another Scope into the newly constructed Scope.
		/// </summary>
		/// <param name="other"> Rvalue reference to the Scope to be moved into the newly constructed Scope. </param>
		Scope(Scope&& other) noexcept;

		/// <summary>
		/// Copy assignment operator for Scope to copy over the contents of an existing Scope, onto "this" Scope.
		/// </summary>
		/// <param name="rhs"> Reference to the Scope to be copied over to "this" Scope. </param>
		/// <returns> Reference to "this" Scope after copying. </returns>
		Scope& operator=(const Scope& rhs);
		
		/// <summary>
		/// Move assignment operator for Scope to move the contents of an existing Scope, into "this" Scope.
		/// </summary>
		/// <param name="rhs"> Rvalue reference to the Scope to be moved into "this" Scope. </param>
		/// <returns> Reference to "this" Scope after moving. </returns>
		Scope& operator=(Scope&& rhs) noexcept;

		/// <summary>
		/// Destructor for Scope, which is responsible for deallocating any memory owned by the Scope.
		/// </summary>
		virtual ~Scope();

		/// <summary>
		/// Find function to find the the Datum associated with a given string key. Searches for the key only in "this" Scope.
		/// </summary>
		/// <param name="key"> The key with which the Scope is to be queried. </param>
		/// <returns> The address of the Datum associated with the passed in keu. Returns nullptr if the key was not found. </returns>
		Datum* Find(const std::string& key);

		/// <summary>
		/// Find function to find the the Datum associated with a given string key. Searches for the key only in "this" Scope.
		/// </summary>
		/// <param name="key"> The key with which the Scope is to be queried. </param>
		/// <returns> The const address of the Datum associated with the passed in keu. Returns nullptr if the key was not found. </returns>
		const Datum* Find(const std::string& key) const;

		/// <summary>
		/// Function to Find the Datum and index within which the passed in Scope lies. Searches for the Scope only in "this" Scope. 
		/// </summary>
		/// <param name="scope"> Address of the Scope to be searched for. </param>
		/// <returns> A std::pair where the first part of the tuple is the Datum within which the given Scope was found (nullptr if not found),
		/// and the second part of the "tuple" is the index of the Datum within "this" Scope. </returns>
		std::pair<Datum*, size_t> FindContainedScope(const Scope* scope);
		
		/// <summary>
		/// Function to Find the Datum and index within which the passed in Scope lies. Searches for the Scope only in "this" Scope. 
		/// </summary>
		/// <param name="scope"> Address of the Scope to be searched for. </param>
		/// <returns> A const std::pair where the first part of the tuple is the Datum within which the given Scope was found (nullptr if not found),
		/// and the second part of the "tuple" is the index of the Datum within "this" Scope. </returns>
		const std::pair<Datum*, size_t> FindContainedScope(const Scope* scope) const;
		
		/// <summary>
		/// Function to search the Scope for the Datum associated with the passed in key. Searches "this" Scope and all parent Scopes recursively until the key is found.
		/// </summary>
		/// <param name="key"> The key with which the Scope is to be queried. </param>
		/// <returns> The address of the Datum associated with the passed in key. nullptr if the key was not found. </returns>
		Datum* Search(const std::string& key);

		/// <summary>
		/// Function to search the Scope for the Datum associated with the passed in key. Searches "this" Scope and all parent Scopes recursively until the key is found.
		/// </summary>
		/// <param name="key"> The key with which the Scope is to be queried. </param>
		/// <returns> The const address of the Datum associated with the passed in key. nullptr if the key was not found. </returns>
		const Datum* Search(const std::string& key) const;

		/// <summary>
		/// Function to search the Scope for the Datum associated with the passed in key. Searches "this" Scope and all parent Scopes recursively until the key is found.
		/// </summary>
		/// <param name="key"> The key with which the Scope is to be queried. </param>
		/// <param name="outScope"> Address of Scope to be searched. Used as an output paramater and is set to the Scope within which the given key was found. </param>
		/// <returns> The address of the Datum associated with the passed in key. nullptr if the key was not found. </returns>
		Datum* Search(const std::string& key, Scope*& outScope);

		/// <summary>
		/// Function to search the Scope for the Datum associated with the passed in key. Searches "this" Scope and all parent Scopes recursively until the key is found.
		/// </summary>
		/// <param name="key"> The key with which the Scope is to be queried. </param>
		/// <param name="outScope"> Address of Scope to be searched. Used as an output paramater and is set to the Scope within which the given key was found. </param>
		/// <returns> The const address of the Datum associated with the passed in key. nullptr if the key was not found. </returns>
		const Datum* Search(const std::string& key, Scope*& outScope) const;

		/// <summary>
		/// Function to Append a string-Datum pair to the Scope. If the key already exists, the existing Datum associated with the key is returned.
		/// </summary>
		/// <param name="key"> The key with which the new Datum is to be associated with. </param>
		/// <returns> Reference to the existing/created Datum associated with the key. </returns>
		Datum& Append(const std::string& key);

		/// <summary>
		/// Function to append a Datum and then insert a default heap constructed Scope into the Datum with the associated key.
		/// </summary>
		/// <param name="key"> The key with which the Append function is to be called. </param>
		/// /// <param name="concreteType"> The name of the type of the concrete Scope to be created. Defaulted to "Scope". </param>
		/// <returns> Reference to the newly inserted Scope. </returns>
		/// <exception cref="runtime_error"> Throws if the appended Datum is not of type Unknown or of type Table. </exception>
		Scope& AppendScope(const std::string& key, const std::string& concreteType = "Scope");

		/// <summary>
		/// Function to get the parent of the Scope.
		/// </summary>
		/// <returns> Address of the parent of the Scope. nullptr if Scope has no parent. </returns>
		Scope* GetParent();

		/// <summary>
		/// Function to get the parent of the Scope.
		/// </summary>
		/// <returns> Const address of the parent of the Scope. nullptr if Scope has no parent. </returns>
		const Scope* GetParent() const;

		/// <summary>
		/// Function to adopt a Scope as a child of "this" Scope. The Scope is now "owns" the adopted Scope and is responsible for freeing memory of the adopted Scope.
		/// </summary>
		/// <param name="childScope"> Reference to the Scope to be adopted. </param>
		/// <param name="key"> The key associated with the Datum into which the Scope is to be inserted. </param>
		/// <exception cref="runtime_error"> Throws if the appended Datum is not of type Unknown or of type Table. </exception>
		/// <exception cref="runtime_error"> Throws if the Scope to adopt is the "this" Scope itself, or if it's an ancestor of "this" Scope. </exception>
		void Adopt(Scope& childScope, const std::string& key);

		/// <summary>
		/// Function to Orphan the Scope. Removes itself from the Datum of the parent Scope and sets parent to nullptr.
		/// </summary>
		/// <returns> Pointer to the Scope after orphaning which the calling context is now the owner of. Cannot be discarded. </returns>
		[[nodiscard]] gsl::owner<Scope*> Orphan();

		/// <summary>
		/// Function to Clear the contents of the Scope. Frees any allocated memory allocated to the Scope.
		/// </summary>
		virtual void Clear();

		/// <summary>
		/// Function which essentially wraps the Append method for syntactic convenience.
		/// </summary>
		/// <param name="key"> The key with which the Append method is to be called. </param>
		/// <returns> Reference to the result returned from the Append call. </returns>
		Datum& operator[](const std::string& key);

		/// <summary>
		/// Function which returns the Datum at the specified index.
		/// </summary>
		/// <param name="index"> The index of the Datum to be accessed. </param>
		/// <returns> Reference to the Datum at the given index. </returns>
		/// <exception cref="out_of_range"> Throws if the specified index is greater than or equal to the Size of the Scope. </exception>
		Datum& operator[](std::size_t index);

		/// <summary>
		/// Function which returns the Datum at the specified index.
		/// </summary>
		/// <param name="index"> The index of the Datum to be accessed. </param>
		/// <returns> Const reference to the Datum at the given index. </returns>
		/// <exception cref="out_of_range"> Throws if the specified index is greater than or equal to the Size of the Scope. </exception>
		const Datum& operator[](std::size_t index) const ;

		/// <summary>
		/// Not equal operator for Scope which compares the contents of "this" Scope with the passed in Scope. 
		/// </summary>
		/// <param name="rhs"> The Scope with which "this" Scope is to be compared. </param>
		/// <returns> True if their contents are not equivalent, false if they are. </returns>
		bool operator!=(const Scope& rhs) const;

		/// <summary>
		/// Equal operator for Scope which compares the contents of "this" Scope with the passed in Scope. 
		/// </summary>
		/// <param name="rhs"> The Scope with which "this" Scope is to be compared. </param>
		/// <returns> True if their contents are equivalent, false if they are not. </returns>
		bool operator==(const Scope& rhs) const;

		/// <summary>
		/// Equals function for Scope which compares the contents of "this" Scope with the passed in Scope. 
		/// </summary>
		/// <param name="rhs"> The Scope with which "this" Scope is to be compared. </param>
		/// <returns> True if their contents are equivalent, false if they are not. </returns>
		bool Equals(const RTTI* rhs) const override;

		/// <summary>
		/// Function that checks if the Scope is an ancestor of the passed in Scope.
		/// </summary>
		/// <param name="potentialDescendant"> The Scope whose ancestor is to be verified. </param>
		/// <returns> True if the Scope is an ancestor of the passed in Scope, false if it is not. </returns>
		bool IsAncestorOf(const Scope& potentialDescendant) const;

		/// <summary>
		/// Function that checks if the Scope is a descendant of the passed in Scope.
		/// </summary>
		/// <param name="potentialDescendant"> The Scope whose ancestor is to be verified. </param>
		/// <returns> True if the Scope is an ancestor of the passed in Scope, false if it is not. </returns>
		bool IsDescendantOf(const Scope& potentialAncestor) const;

		/// <summary>
		/// Function to get the size of the Scope.
		/// </summary>
		/// <returns> The size of the Scope. </returns>
		std::size_t Size() const;

	protected:
		/// <summary>
		/// Clone function that returns a new heap allocated Scope object, by copy constructing it with "this" Scope.
		/// </summary>
		/// <returns> Pointer to the newly created Scope. </returns>
		virtual Scope* Clone() const;

		void ForEachNestedScope(NestedScopeFunction func) const;

		HashMap<std::string, Datum> _map;
		Vector<HashMap<std::string, Datum>::PairType*> _orderVector;
		Scope* _parent { nullptr };
	};
}