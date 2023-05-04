#include "Factory.h"

namespace FieaGameEngine
{
	template<typename T>
	inline Factory<T>* Factory<T>::Find(const std::string& className)
	{
		if (!Factories.ContainsKey(className))
			return nullptr;
		return Factories.Find(className)->second;
	}

	template<typename T>
	inline gsl::owner<T*> Factory<T>::Create(const std::string& className)
	{
		assert(Factories.ContainsKey(className));

		return Factories.Find(className)->second->Create();
	}

	template<typename T>
	inline void Factory<T>::Add(const std::string& className, Factory& factory)
	{
		assert(!Factories.ContainsKey(className));
		Factories.Insert(std::make_pair(className, &factory));
	}

	template<typename T>
	inline void Factory<T>::Remove(const Factory& factory)
	{
		if (!Factories.ContainsKey(factory.ClassName()))
			return;

		Factories.Remove(factory.ClassName());
	}

	template<typename T>
	inline void Factory<T>::Clear()
	{
		for (auto it = Factories.begin(); it != Factories.end(); it = Factories.begin())
			Remove(*(it->second));
	}
}