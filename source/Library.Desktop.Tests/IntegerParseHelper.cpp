#include "pch.h"
#include "IntegerParseHelper.h"

using namespace FieaGameEngine;
using namespace std;

namespace UnitTests
{
	RTTI_DEFINITIONS(IntegerParseHelper);
	RTTI_DEFINITIONS(IntegerParseHelper::IntWrapper);

	bool IntegerParseHelper::StartHandler(JsonParseCoordinator::Wrapper& wrapper, const string&, const Json::Value& value, size_t)
	{
		IntWrapper* intWrapper = static_cast<IntegerParseHelper::IntWrapper*>(&wrapper);
		if (intWrapper == nullptr)
			return false;
		
		intWrapper->Data.PushBack(value.asInt());
		return true;
	}

	bool IntegerParseHelper::EndHandler(JsonParseCoordinator::Wrapper&, const string&)
	{
		return true;
	}

	shared_ptr<JsonParseCoordinator::Wrapper> IntegerParseHelper::IntWrapper::Create() const
	{
		return make_shared<IntWrapper>();
	}

	shared_ptr<IJsonParseHelper> IntegerParseHelper::Create() const
	{
		return make_shared<IntegerParseHelper>();
	}
}