#pragma once
#include "RTTI.h"
#include "Vector.h"
#include "Datum.h"
#include "HashMap.h"

namespace FieaGameEngine
{
	struct Signature final
	{
		inline bool operator==(const Signature& rhs) const
		{
			return _name == rhs._name
				&& _type == rhs._type
				&& _size == rhs._size
				&& _offset == rhs._offset;
		}

		inline bool operator!=(const Signature& rhs) const
		{
			return !operator==(rhs);
		}

		std::string _name;
		Datum::DatumTypes _type;
		std::size_t _size;
		std::size_t _offset;
	};

	class TypeManager final
	{
	public:
		/// <summary>
		/// Function to create an instance of a TypeManager. Does not create if it already exists.
		/// </summary>
		static void CreateInstance();

		/// <summary>
		/// Function to get the instance of the TypeManager.
		/// </summary>
		/// <returns> Pointer to the TypeManager instance. </returns>
		static TypeManager* GetInstance();

		/// <summary>
		/// Function thart deletes the TypeManager instance.
		/// </summary>
		static void DestroyInstance();

		/// <summary>
		/// Function to populate the HashMap with IdType and Vector of Signature pairs.
		/// </summary>
		/// <param name="signatures"> Vector of signatures for the object of type "Child". </param>
		/// <typeparam name="Child"> The type for which the map is being populated. </typeparam>
		/// <typeparam name="Parent"> The parent type of the type for which the map is being populated. </typeparam>
		template<typename Child, typename Parent>
		inline void RegisterType(const Vector<Signature>& signatures)
		{
			Vector<Signature> allSignatures;
			if (Parent::TypeIdClass() != Attributed::TypeIdClass())
				allSignatures = (*_signatureMap.Find(Parent::TypeIdClass())).second;

			Vector<Signature>::ConstIterator it = signatures.begin();
			while (it != signatures.end())
			{
				allSignatures.PushBack(*it);
				++it;
			}

			_signatureMap.Insert(make_pair(Child::TypeIdClass(), allSignatures));
		}

		HashMap<RTTI::IdType, Vector<Signature>> _signatureMap;

	private:
		inline static TypeManager* _instance;
	};
}