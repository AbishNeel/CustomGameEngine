#pragma once
#include "pch.h"
#include "SList.h"

namespace FieaGameEngine
{
	template <typename T>
	struct DefaultEquality final
	{
		bool operator()(const T& lhs, const T& rhs) const;
	};

	template<>
	struct DefaultEquality<char*> final
	{
		bool operator()(const char* lhs, const char* rhs) const;
	};

	template<>
	struct DefaultEquality<const char*> final
	{
		bool operator()(const char* lhs, const char* rhs) const;
	};

	template<>
	struct DefaultEquality<char* const> final
	{
		bool operator()(const char* const lhs, const char* const rhs) const;
	};

	template<>
	struct DefaultEquality<const char* const> final
	{
		bool operator()(const char* const lhs, const char* const rhs) const;
	};

	template<typename TKey, typename TValue>
	struct DefaultEquality <SList<std::pair<TKey, TValue>>> final
	{
		bool operator()(const SList<std::pair<TKey, TValue>>& lhs, const SList<std::pair<TKey, TValue>>& rhs) const;
	};
}

#include "DefaultEquality.inl"