#pragma once
#include "IJsonParseHelper.h"
#include "JsonParseCoordinator.h"
#include "Vector.h"

namespace UnitTests
{
	/// <summary>
	/// Helper class which can parse only integer data. 
	/// </summary>
	class IntegerParseHelper final : public FieaGameEngine::IJsonParseHelper
	{
		RTTI_DECLARATIONS(IntegerParseHelper, FieaGameEngine::IJsonParseHelper);

	public:
		/// <summary>
		/// Wrapper that can hold integer data and can be used to parse only integer data.
		/// </summary>
		class IntWrapper final : public FieaGameEngine::JsonParseCoordinator::Wrapper
		{
			RTTI_DECLARATIONS(IntWrapper, FieaGameEngine::JsonParseCoordinator::Wrapper);

		public:
			IntWrapper() = default;

			/// <summary>
			/// Function that creates a new instanc of an IntWrapper.
			/// </summary>
			/// <returns> shared_ptr to the newly created IntWrapper. </returns>
			std::shared_ptr<Wrapper> Create() const override;

			~IntWrapper() = default;

			FieaGameEngine::Vector<std::int32_t> Data;
		};

		/// <summary>
		/// Function that starts the Handling of a value associated with a given key.
		/// </summary>
		bool StartHandler(FieaGameEngine::JsonParseCoordinator::Wrapper& wrapper, const std::string& key, const Json::Value& value, std::size_t index = 0) override;

		/// <summary>
		/// Function that completes the Handling of a value associated with a given key.
		/// </summary>
		bool EndHandler(FieaGameEngine::JsonParseCoordinator::Wrapper& wrapper, const std::string& key) override;

		/// <summary>
		/// Function that creates a new instance of an IntegerParseHelper.
		/// </summary>
		/// <returns> shared_ptr to the newly created IntegerParseHelper.</returns>
		std::shared_ptr<IJsonParseHelper> Create() const override;

		~IntegerParseHelper() = default;
	};
}