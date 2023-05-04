#include "TableParseHelper.h"
#include "Factory.h"

using namespace std;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(TableParseHelper);
	RTTI_DEFINITIONS(TableParseHelper::TableWrapper);

	TableParseHelper::TableParseHelper()
	{
		Initialize();
	}

	bool TableParseHelper::StartHandler(JsonParseCoordinator::Wrapper& wrapper, const string& key, const Json::Value& value, size_t index)
	{
		TableWrapper* tableWrapper = static_cast<TableWrapper*>(&wrapper);

		if (tableWrapper == nullptr)
			return false;

		if (key == "type"s)
		{
			assert(value.isString());
			Datum& datum = _contextStack.Top().scope->Append(_contextStack.Top().key);
			datum.SetType(_datumTypeMap.Find(value.asString())->second);
		}
		else if (key == "value"s)
		{
			if(!value.isObject())
			{
				Datum& datum = _contextStack.Top().scope->Append(_contextStack.Top().key);
				SetDatumValue(datum, value, index);
			}
			else
			{
				auto& top = _contextStack.Top();
				Scope& scope = top.scope->AppendScope(top.key, _concreteTypeName);
				_contextStack.Push(TableWrapper::Context(""s, &scope));
			}
		}
		else if (key == "class"s)
		{
			assert(value.isString());
			_concreteTypeName = value.asString();
		}

		else
			_contextStack.Push(TableWrapper::Context(key, _contextStack.Top().scope));

		return true;
	}

	bool TableParseHelper::EndHandler(JsonParseCoordinator::Wrapper& wrapper, const string& key)
	{
		TableWrapper* tableWrapper = static_cast<TableWrapper*>(&wrapper);

		if (tableWrapper == nullptr)
			return false;

		if (_contextStack.Top().key == ""s)
			_contextStack.Pop();

		if (key == _contextStack.Top().key)
			_contextStack.Pop();

		return true;
	}

	shared_ptr<JsonParseCoordinator::Wrapper> TableParseHelper::TableWrapper::Create() const
	{
		return make_shared<TableParseHelper::TableWrapper>();
	}

	void TableParseHelper::Initialize()
	{
		Scope* rootScope = new Scope();
		_contextStack.Push(TableWrapper::Context("root"s, rootScope));

		_datumTypeMap.Insert(make_pair("integer"s, Datum::DatumTypes::Integer));
		_datumTypeMap.Insert(make_pair("float"s, Datum::DatumTypes::Float));
		_datumTypeMap.Insert(make_pair("string"s, Datum::DatumTypes::String));
		_datumTypeMap.Insert(make_pair("vector"s, Datum::DatumTypes::Vector));
		_datumTypeMap.Insert(make_pair("matrix"s, Datum::DatumTypes::Matrix));
		_datumTypeMap.Insert(make_pair("table"s, Datum::DatumTypes::Table));
	}

	void TableParseHelper::SetDatumValue(Datum& datum, const Json::Value& value, size_t index)
	{
		switch (datum.Type())
		{
		case Datum::DatumTypes::Integer:
			assert(value.isInt());
			if (datum.IsExternal())
				datum.Set(value.asInt(), index);
			else
				datum.PushBack(value.asInt());
			break;

		case Datum::DatumTypes::Float:
			assert(value.isDouble());
			if (datum.IsExternal())
				datum.Set(value.asFloat(), index);
			else
				datum.PushBack(value.asFloat());
			break;

		case Datum::DatumTypes::String:
			assert(value.isString());
			if (datum.IsExternal())
				datum.Set(value.asString(), index);
			else
				datum.PushBack(value.asString());
			break;

		case Datum::DatumTypes::Vector:
			assert(value.isString());
			if (datum.IsExternal())
				datum.SetVecFromString(value.asString(), index);
			else
				datum.PushBackVectorFromString(value.asString());
			break;

		case Datum::DatumTypes::Matrix:
			assert(value.isString());
			if (datum.IsExternal())
				datum.SetMatFromString(value.asString(), index);
			else
				datum.PushBackMatrixFromString(value.asString());
			break;
		}
	}

	shared_ptr<IJsonParseHelper> TableParseHelper::Create() const
	{
		return make_shared<TableParseHelper>();
	}

	bool TableParseHelper::CopyData(JsonParseCoordinator::Wrapper& wrapper)
	{
		TableWrapper* tableWrapper = static_cast<TableWrapper*>(&wrapper);
		if (tableWrapper == nullptr)
			return false;

		tableWrapper->Data = make_shared<Scope>(move(* _contextStack.Top().scope));
		return true;
	}

	TableParseHelper::~TableParseHelper()
	{
		delete(_contextStack.Top().scope);
	}

}