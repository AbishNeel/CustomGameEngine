#include "DefaultIncrement.h"

namespace FieaGameEngine
{
	inline size_t DefaultIncrement::operator()(size_t size, size_t capacity) const
	{
		return size + capacity;
	}
}