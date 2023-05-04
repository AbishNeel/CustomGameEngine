#pragma once
#include "pch.h"

namespace FieaGameEngine
{
	struct DefaultIncrement final
	{
		size_t operator()(size_t size, size_t capacity) const;
	};
}

#include "DefaultIncrement.inl"