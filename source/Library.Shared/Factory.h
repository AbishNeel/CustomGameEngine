#pragma once
#include <string>
#include <memory>
#include "HashMap.h"
#include <gsl/gsl>

namespace FieaGameEngine
{
	/// <summary>
	/// Factory class that maintains a list of Factories that create derived types of the given type.
	/// </summary>
	template<typename T>
	class Factory
	{
	public:
		/// <summary>
		/// Function that finds and returns a Factory associated with the given class name.
		/// </summary>
		/// <param name="className"> The name of the type of Factory to be found. </param>
		/// <returns> Pointer to the Factory associated with the class name. </returns>
		inline static Factory* Find(const std::string& className);

		/// <summary>
		/// Function that finds and returns a Factory associated with the given class name.
		/// </summary>
		/// <param name="className"> The name of the type of Factory to be found. </param>
		/// <returns> Pointer to the newly created object by the Factory associated with the class name. Calling context is now responsible for deleting the pointer. </returns>
		inline static gsl::owner<T*> Create(const std::string& className);

		/// <summary>
		/// Function that clears the list of Factories.
		/// </summary>
		inline static void Clear();

		virtual gsl::owner<T*> Create() const = 0;

		virtual const std::string& ClassName() const = 0;

		virtual ~Factory() = default;

	protected:
		/// <summary>
		/// Function that adds a Factory to the list of Factories.
		/// </summary>
		/// <param name="className"> The name to be associated with the Factory. </param>
		/// <param name="factory"> Reference to the Factory to be added. </param>
		inline static void Add(const std::string& className, Factory& factory);
		 
		/// <summary>
		/// Function that removes a Factory to the list of Factories.
		/// </summary>
		/// <param name="factory"> Reference to the Factory to be removed. </param>
		inline static void Remove(const Factory& factory);

	private:
		inline static HashMap<std::string, Factory*> Factories {17};
	};

#define ConcreteFactory(ConcreteProductType, AbstractProductType)													\
class ConcreteProductType ## Factory final : public FieaGameEngine::Factory<FieaGameEngine::AbstractProductType>	\
{																													\
	public:																											\
		ConcreteProductType ## Factory() : _className{std::string(#ConcreteProductType)}							\
		{																											\
			Add(_className, *this);																					\
		}																											\
		gsl::owner<FieaGameEngine::AbstractProductType*> Create() const override									\
		{																											\
			return new ConcreteProductType{};																		\
		}																											\
		const std::string& ClassName() const override																\
		{																											\
			return _className;																						\
		}																											\
		~ConcreteProductType ## Factory()																			\
		{																											\
			Remove(*this);																							\
		}																											\
	private:																										\
		std::string _className;																						\
};

}
#include "Factory.inl"