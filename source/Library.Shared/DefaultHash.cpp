#pragma once
#include "pch.h"
#include "DefaultHash.h"

namespace FieaGameEngine
{
	std::size_t AdditiveHash(const std::byte* data, std::size_t size)
	{
		size_t sum = 37;
		for (size_t i = 0; i < size; ++i)
			sum += static_cast<size_t>(data[i]);
		return sum;
	}
}