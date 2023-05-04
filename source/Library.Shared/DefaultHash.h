#pragma once
#include <stdlib.h>

namespace FieaGameEngine
{
	std::size_t AdditiveHash(const std::byte* data, std::size_t size);
}

#include "DefaultHash.inl"