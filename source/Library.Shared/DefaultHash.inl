#include "DefaultHash.h"

namespace FieaGameEngine
{
	template<typename T>
	struct DefaultHash final
	{
		std::size_t operator()(const T& key)
		{
			return AdditiveHash(reinterpret_cast<const std::byte*>(&key), sizeof(T));
		}
	};

	template<>
	struct DefaultHash<char*> final
	{
		std::size_t operator()(const char* key)
		{
			size_t sum = 0;
			size_t i = 0;
			while (key[i] != '\0')
				sum += key[i++];
			return sum;
		}
	};

	template<>
	struct DefaultHash<std::string> final
	{
		std::size_t operator()(const std::string& key)
		{
			return AdditiveHash(reinterpret_cast<const std::byte*>(key.c_str()), key.size());
		}
	};
}