#pragma once
#include "Scope.h"

namespace FieaGameEngine

{
	class Attributed : public Scope
	{
		RTTI_DECLARATIONS(Attributed, Scope);

	public:
		/// <summary>
		/// Function to append an auxiliary attribute to the Attributed object.
		/// </summary>
		/// <param name="name"> The name of the attribute to be appended. </param>
		/// <returns> Reference to the Datum created by appending the attribute name. </returns>
		/// <exception cref="runtime_error"> Throws if a prescribed attribute already exists with the same name. </exception>
		Datum& AppendAuxiliaryAttribute(const std::string& name);

		/// <summary>
		/// Function to get all the attributes of the Attributed object.
		/// </summary>
		/// <returns> A Vector containing the names of all the attributes of the object. </returns>
		const Vector<std::string> Attributes() const;

		/// <summary>
		/// Function to get all the prescribed attributes of the Attributed object.
		/// </summary>
		/// <returns> A Vector containing the names of all the prescribed attributes of the object. </returns>
		const Vector<std::string> PrescribedAttributes() const;

		/// <summary>
		/// Function to get all the auxiliary attributes of the Attributed object.
		/// </summary>
		/// <returns> A Vector containing the names of all the auxiliary attributes of the object. </returns>
		const Vector<std::string> AuxiliaryAttributes() const;

		/// <summary>
		/// Function to check if a given name is an attribute of the object.
		/// </summary>
		/// <param name="name"> The name of the prescribed attribute to check the object for. </param>
		/// <returns> True if it is an attribute, false if it is not. </returns>
		bool IsAttribute(const std::string& name) const;

		/// <summary>
		/// Function to check if a given name is a prescribed attribute of the object.
		/// </summary>
		/// <param name="name"> The name of the prescribed attribute to check the object for. </param>
		/// <returns> True if it is a prescribed attribute, false if it is not. </returns>
		bool IsPrescribedAttribute(const std::string& name) const;

		/// <summary>
		/// Function to check if a given name is an auxiliary attribute of the object.
		/// </summary>
		/// <param name="name"> The name of the auxiliary attribute to check the object for. </param>
		/// <returns> True if it is an auxiliary attributed, false if it is not. </returns>
		bool IsAuxiliaryAttribute(const std::string& name) const;

	protected:

		virtual Attributed* Clone() const override = 0;

		/// <summary>
		/// Constructor to construct an Attributed object.
		/// </summary>
		/// <param name="typeID"> The type ID of the class. </param>
		Attributed(RTTI::IdType typeID);

		/// <summary>
		/// Copy constructor for Attributed to construct an Attributed by copying over the contents of another one.
		/// </summary>
		/// <param name="other"> The Attributed with which "this" Attributed is to be initialized with. </param>
		Attributed(const Attributed& other);

		/// <summary>
		/// Copy assignment operator for Attributed copy over the contents of another Attributed onto "this" one.
		/// </summary>
		/// <param name="rhs"> The Attributed to be copied onto "this" one. </param>
		/// <returns> Reference to "this" Attributed after copying. </returns>
		Attributed& operator=(const Attributed& rhs);

		/// <summary>
		/// Move constructor for Attributed to construct an Attributed by moving over the contents of another one.
		/// </summary>
		/// <param name="other"> The Attributed with which "this" Attributed is to be initialized with. </param>
		Attributed(Attributed&& other) noexcept;

		/// <summary>
		/// Move assignment operator for Attributed move over the contents of another Attributed onto "this" one.
		/// </summary>
		/// <param name="rhs"> The Attributed to be moved onto "this" one. </param>
		/// <returns> Reference to "this" Attributed after moving. </returns>
		Attributed& operator=(Attributed&& rhs) noexcept;

		virtual ~Attributed() = default;

		/// <summary>
		/// Function to populate the Attributed object with all of it's prescribed attributes.
		/// </summary>
		/// <param name="typeID"> The type ID of the class. </param>
		void Populate(RTTI::IdType typeID);

		/// <summary>
		/// Function to fix the external pointers of the Datums to point to the members of "this" Attributed object, after copying or moving.
		/// </summary>
		/// <param name="typeID"> The type ID of the object. </param>
		void UpdateExternalPointers(RTTI::IdType typeID);
	};
}