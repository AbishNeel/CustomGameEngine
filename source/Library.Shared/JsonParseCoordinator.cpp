#include "pch.h"
#include "JsonParseCoordinator.h"
#include <fstream>
#include "IJsonParseHelper.h"
#include "DefaultEquality.h"
#include "Factory.h"
#include "Scope.h"

using namespace std;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(JsonParseCoordinator::Wrapper);

	JsonParseCoordinator::JsonParseCoordinator(shared_ptr<Wrapper> wrapper)
		: _wrapper{ move(wrapper)}
	{
	}

	JsonParseCoordinator::JsonParseCoordinator(JsonParseCoordinator&& other) noexcept
		: _helpers { move(other._helpers) }, _wrapper{ move(other._wrapper) }
	{
	}

	JsonParseCoordinator& JsonParseCoordinator::operator=(JsonParseCoordinator&& rhs) noexcept
	{
		if (this != &rhs)
		{
			_helpers = move(rhs._helpers);
			_wrapper = move(rhs._wrapper);
		}
		return *this;
	}

	gsl::owner<JsonParseCoordinator*> JsonParseCoordinator::Clone() const
	{
		JsonParseCoordinator* newParser = new JsonParseCoordinator{ _wrapper->Create() };
		for (auto& helper : _helpers)
			newParser->AddHelper(helper->Create());

		return newParser;
	}

	void JsonParseCoordinator::AddHelper(shared_ptr<IJsonParseHelper> helper)
	{
		for (auto& existingHelper : _helpers)
		{
			if (existingHelper->TypeIdClass() == helper->TypeIdClass())
				return;
		}
		_helpers.PushBack(helper);
	}

	void JsonParseCoordinator::RemoveHelper(shared_ptr<IJsonParseHelper> helper)
	{
		for (auto& value : _helpers)
		{
			if(value->TypeIdClass() == value->TypeIdClass())
				_helpers.Remove(value);
		}
	}

	shared_ptr<JsonParseCoordinator::Wrapper> JsonParseCoordinator::GetWrapper() const
	{
		return _wrapper;
	}

	void JsonParseCoordinator::SetWrapper(shared_ptr<Wrapper> wrapper)
	{
		_wrapper = wrapper;
	}

	void JsonParseCoordinator::DeserializeObject(istream& stream)
	{
		Json::Value jsonValue;
		stream >> jsonValue;
		ParseMembers(jsonValue);
		for (auto& helper : _helpers)
		{
			if(helper->CopyData(*_wrapper))
				break;
		}
	}

	void JsonParseCoordinator::DeserializeObjectFromFile(const std::string& fileName)
	{
		std::ifstream fileStream(fileName, std::ifstream::binary);
		if (!fileStream.good())
			throw runtime_error("Could not read Json file.");

		DeserializeObject(fileStream);
	}

	void JsonParseCoordinator::DeserializeObject(const Json::String& jsonString)
	{
		stringstream string(jsonString);
		DeserializeObject(string);
	}

	void JsonParseCoordinator::ParseMembers(const Json::Value& jsonValue, size_t index)
	{
		auto keys = jsonValue.getMemberNames();
		for (const auto& key : keys)
		{
			auto valueToParse = jsonValue[key];
			Parse(key, valueToParse, index);
		}
	}

	void JsonParseCoordinator::Parse(const string& key, const Json::Value& jsonValue, size_t index)
	{
		if (jsonValue.isObject())
		{
			_wrapper->IncrementDepth();
			for (auto& helper : _helpers)
			{
				if (helper->StartHandler(*_wrapper, key, jsonValue, index))
				{
					ParseMembers(jsonValue);
					helper->EndHandler(*_wrapper, key);
					break;
				}
			}
			_wrapper->DecrementDepth();
		}
		else if (jsonValue.isArray())
		{
			size_t i = 0;
			for (const auto& element : jsonValue)
			{
				if (element.isObject())
				{
					_wrapper->IncrementDepth();
					Parse(key, element,i);
					_wrapper->DecrementDepth();
				}
				else
					Parse(key, element, i);
				++i;
			}
		}
		else
		{
			for (auto& helper : _helpers)
			{
				if (helper->StartHandler(*_wrapper, key, jsonValue, index))
				{
					helper->EndHandler(*_wrapper, key);
					break;
				}
			}
		}
	}

	Vector<shared_ptr<IJsonParseHelper>>& JsonParseCoordinator::GetHelpers()
	{
		return _helpers;
	}

	void JsonParseCoordinator::Wrapper::IncrementDepth()
	{
		++_nestingDepth;
	}

	void JsonParseCoordinator::Wrapper::DecrementDepth()
	{
		--_nestingDepth;
	}

	uint32_t JsonParseCoordinator::Wrapper::Depth() const
	{
		return _nestingDepth; 
	}
}