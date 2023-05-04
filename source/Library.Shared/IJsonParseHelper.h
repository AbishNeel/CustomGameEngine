#pragma once
#include <json/json.h>
#include "RTTI.h"
#include "JsonParseCoordinator.h"
#include <memory>

namespace FieaGameEngine
{
	/// <summary>
	/// Helper class which can be overriden to help parse different types of data.
	/// </summary>
	class IJsonParseHelper : public RTTI
	{
		RTTI_DECLARATIONS(IJsonParseHelper, RTTI);

	public:
		virtual void Initialize() {};
		virtual bool CopyData(JsonParseCoordinator::Wrapper&) { return false; };

		virtual bool StartHandler(JsonParseCoordinator::Wrapper& wrapper, const std::string& key, const Json::Value& value, std::size_t index = 0) = 0;
		virtual bool EndHandler(JsonParseCoordinator::Wrapper& wrapper, const std::string& key) = 0;
		virtual [[nodiscard]] std::shared_ptr<IJsonParseHelper> Create() const = 0;
		virtual ~IJsonParseHelper() = default;
	};
}