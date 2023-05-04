#pragma once
#include "pch.h"
#include "Scope.h"
#include "Factory.h"

using namespace std;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Scope);

	Scope::Scope(size_t capacity)
		: _map{ capacity }, _orderVector{ capacity }
	{
	}

	Scope::Scope(const Scope& other)
		: _map{ other._map.Capacity() }, _orderVector{ other.Size() }
	{
		Vector<HashMap<string, Datum>::PairType*>::ConstIterator it = other._orderVector.begin();
		while (it != other._orderVector.end())
		{
			HashMap<string, Datum>::PairType* pair = *it;

			Datum& currentDatum = Append(pair->first);

			if (pair->second.Type() == Datum::DatumTypes::Table)
			{
				currentDatum.Reserve(pair->second.Size());

				for (size_t i = 0; i < pair->second.Size(); ++i)
				{
					Scope* newScope = pair->second[i].Clone();
					newScope->_parent = this;
					currentDatum.PushBackScope(newScope);
				}
			}
			else
				currentDatum = pair->second;
			++it;
		}
	}

	Scope::Scope(Scope&& other) noexcept
		: _map{ move(other._map) }, _orderVector{ move(other._orderVector) }
	{
		for (auto it = _orderVector.begin(); it != _orderVector.end(); ++it)
		{
			Datum& currentDatum = (*it)->second;
			if (currentDatum.Type() == Datum::DatumTypes::Table)
			{
				for (size_t i = 0; i < currentDatum.Size(); ++i)
					currentDatum.Get<Scope*>(i)->_parent = this;
			}
		}

		if(other._parent != nullptr)
			delete(other.Orphan());
	}

	Scope& Scope::operator=(const Scope& rhs)
	{
		if (this != &rhs)
		{
			Clear();

			Vector<HashMap<string, Datum>::PairType*>::ConstIterator it = rhs._orderVector.begin();
			while (it != rhs._orderVector.end())
			{
				HashMap<string, Datum>::PairType* pair = *it;

				Append(pair->first);
				Datum& currentDatum = _map[pair->first];

				if (pair->second.Type() == Datum::DatumTypes::Table)
				{
					currentDatum.Reserve(pair->second.Size());

					for (size_t i = 0; i < pair->second.Size(); ++i)
					{
						Scope* newScope = pair->second[i].Clone();
						newScope->_parent = this;
						currentDatum.PushBackScope(newScope);
					}
				}
				else
					currentDatum = pair->second;
				++it;
			}
		}
		return *this;
	}

	Scope& Scope::operator=(Scope&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Clear();

			_map = move(rhs._map);
			_orderVector = move(rhs._orderVector);
			if (rhs._parent != nullptr)
				delete(rhs.Orphan());
		}
		return *this;
	}

	Scope::~Scope()
	{
		Clear();
	}

	Scope* Scope::Clone() const
	{
		return new Scope{ *this };
	}

	void Scope::Clear()
	{
		if (Size() == 0)
			return;

		ForEachNestedScope([](Datum& datum)
			{
				for (size_t i = 0; i < datum.Size(); ++i)
					delete (&datum[i]);
			});

		_map.Clear();
		_orderVector.Clear();
	}

	Datum& Scope::Append(const string& key)
	{
		HashMap<string, Datum>::PairType newPair = make_pair(key, Datum{});
		pair<HashMap<string, Datum>::Iterator, bool> insertResult = _map.Insert(newPair);

		if (insertResult.second)
			_orderVector.PushBack(&*(insertResult.first));

		return insertResult.first->second;
	}

	Scope& Scope::AppendScope(const string& key, const string& concreteType)
	{
		Datum& appendedDatum = Append(key);
		if (appendedDatum.Type() != Datum::DatumTypes::Unknown && appendedDatum.Type() != Datum::DatumTypes::Table)
			throw runtime_error("Datum for specified key already exists with incompatible type.");

		Scope* newScope;
		if (concreteType == "Scope"s)
			newScope = new Scope{};
		else
			newScope = Factory<Scope>::Create(concreteType);

		newScope->_parent = this;
		appendedDatum.PushBackScope(newScope);
		return *newScope;
	}

	Datum* Scope::Find(const string& key)
	{
		HashMap<string, Datum>::Iterator it = _map.Find(key);
		if (it == _map.end())
			return nullptr;
		else
			return &it->second;
	}

	const Datum* Scope::Find(const string& key) const
	{
		HashMap<string, Datum>::ConstIterator it = _map.Find(key);
		if (it == _map.end())
			return nullptr;
		else
			return &it->second;
	}

	pair<Datum*, size_t> Scope::FindContainedScope(const Scope* scope)
	{
		assert(scope != nullptr);

		Datum* parentDatum = nullptr;
		size_t index = 0;

		ForEachNestedScope([&parentDatum, &index, &scope](Datum& datum) 
			{ 
				parentDatum = &datum;
				index = datum.Find(scope); 
				if (index < datum.Size()) 
					return;
				parentDatum = nullptr; 
			});

		return make_pair(parentDatum, index);
	}

	const pair<Datum*, size_t> Scope::FindContainedScope(const Scope* scope) const
	{
		assert(scope != nullptr);

		Datum* parentDatum = nullptr;
		size_t index = 0;

		ForEachNestedScope([&parentDatum, &index, &scope](Datum& datum)
			{
				parentDatum = &datum;
				index = datum.Find(scope);
				if (index < datum.Size())
					return;
				parentDatum = nullptr;
			});

		return make_pair(parentDatum, index);
	}

	Datum* Scope::Search(const string& key)
	{
		Scope* outScope = this;
		return Search(key, outScope);
	}

	const Datum* Scope::Search(const string& key) const
	{
		Scope* outScope = const_cast<Scope*>(this);
		return Search(key, outScope);
	}

	Datum* Scope::Search(const string& key, Scope*& outScope)
	{
		assert(outScope != nullptr);

		Datum* result = Find(key);
		if (result == nullptr && _parent != nullptr)
		{
			outScope = this;
			result = _parent->Search(key, outScope);
		}

		return result;
	}

	const Datum* Scope::Search(const string& key, Scope*& outScope) const
	{
		assert(outScope != nullptr);

		const Datum* result = Find(key);
		if (result == nullptr && _parent != nullptr)
			result = _parent->Search(key, outScope);

		outScope = const_cast<Scope*>(this);
		return result;
	}

	void Scope::Adopt(Scope& childScope, const string& key)
	{
		if (&childScope == this || IsDescendantOf(childScope))
			throw runtime_error("Cannot adopt self or ancestor.");

		Datum& parentDatum = Append(key);
		if (parentDatum.Type() != Datum::DatumTypes::Unknown && parentDatum.Type() != Datum::DatumTypes::Table)
			throw runtime_error("Datum for specified key already exists with incompatible type.");

		Scope* child = childScope.Orphan();
		child->_parent = this;
		parentDatum.PushBackScope(child);
	}

	gsl::owner<Scope*> Scope::Orphan()
	{
		if (_parent != nullptr)
		{
			pair<Datum*, size_t> result = _parent->FindContainedScope(this);
			result.first->RemoveAt(result.second);
			_parent->_orderVector.Remove(_parent->_orderVector[result.second]);
			_parent = nullptr;
		}
		return this;
	}

	void Scope::ForEachNestedScope(NestedScopeFunction func) const
	{
		Vector<HashMap<string, Datum>::PairType*>::ConstIterator it = _orderVector.begin();
		while (it != _orderVector.end())
		{
			Datum& datum = (*it)->second;
			if (datum.Type() == Datum::DatumTypes::Table)
				func(datum);
			++it;
		}
	}

	bool Scope::operator!=(const Scope& rhs) const
	{
		return !Equals(&rhs);
	}

	bool Scope::operator==(const Scope& rhs) const
	{
		return Equals(&rhs);
	}

	bool Scope::Equals(const RTTI* rhs) const
	{
		if (rhs == nullptr)
			return false;

		const Scope* otherScope = rhs->As<Scope>();

		if (Size() != otherScope->Size())
			return false;

		bool result = true;
		Vector<HashMap<string, Datum>::PairType*>::ConstIterator otherIt = otherScope->_orderVector.begin();
		ForEachNestedScope([&result, &otherIt](Datum& datum) 
			{ 
				if (datum != (*otherIt)->second) 
				{ 
					result = false; 
					return; 
				} 
				++otherIt; 
			});
		return result;
	}

	bool Scope::IsDescendantOf(const Scope& potentialAncestor) const
	{
		if (_parent == nullptr)
			return false;
		if (_parent == &potentialAncestor)
			return true;

		return IsDescendantOf(*_parent);
	}

	bool Scope::IsAncestorOf(const Scope& potentialDescendant) const
	{
		return potentialDescendant.IsDescendantOf(*this);
	}

	Datum& Scope::operator[](const string& key)
	{
		return Append(key);
	}

	Datum& Scope::operator[](size_t index)
	{
		if (index >= _orderVector.Size())
			throw out_of_range("Index is out of bounds");

		return _orderVector[index]->second;
	}

	const Datum& Scope::operator[](size_t index) const
	{
		if (index >= _orderVector.Size())
			throw out_of_range("Index is out of bounds");

		return _orderVector[index]->second;
	}

	Scope* Scope::GetParent()
	{
		return _parent;
	}

	const Scope* Scope::GetParent() const
	{
		return _parent;
	}

	std::size_t Scope::Size() const
	{
		return _orderVector.Size();
	}
}