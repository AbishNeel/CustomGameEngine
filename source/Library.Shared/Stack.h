#pragma once
#include "SList.h"
#include <cstddef>

namespace FieaGameEngine
{
	template <typename T>
	class Stack final
	{
	public:
		template <typename... Args>
		void Emplace(Args&&... args);

		void Push(const T& value);

		void Push(T&& value);

		void Pop();

		[[nodiscard]] T& Top();
		[[nodiscard]] const T& Top() const;
		std::size_t Size() const;

		bool IsEmpty() const;

		void Clear();

	private:
		SList<T> _list;
	};
}
#include "Stack.inl"