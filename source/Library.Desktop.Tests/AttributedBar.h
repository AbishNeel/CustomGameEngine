#pragma once
#include "AttributedFoo.h"
#include "TypeManager.h"
#include "Factory.h"

namespace UnitTests
{
	class AttributedBar : public UnitTests::AttributedFoo
	{
		RTTI_DECLARATIONS(AttributedBar, UnitTests::AttributedFoo);

	public:
		static const std::size_t ArraySize = 5;

		AttributedBar();
		AttributedBar(const AttributedBar&) = default;
		AttributedBar(AttributedBar&&) noexcept = default;
		AttributedBar& operator =(const AttributedBar&) = default;
		AttributedBar& operator=(AttributedBar&&) noexcept = default;
		virtual ~AttributedBar() = default;

		int ExternalBarInteger = 0;
		float ExternalBarFloat = 0;
		std::string ExternalBarString;

		virtual AttributedBar* Clone() const override;

		bool Equals(const RTTI* rhs) const override;

		static FieaGameEngine::Vector<FieaGameEngine::Signature> Signatures();
	};

	ConcreteFactory(AttributedBar, Scope);
}