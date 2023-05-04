#pragma once
#include "pch.h"
#include "Attributed.h"
#include "TypeManager.h"

using namespace std;

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(Attributed);

	Attributed::Attributed(IdType typeID)
	{
		Populate(typeID);
	}

	Attributed::Attributed(const Attributed& other)
		: Scope{ other }
	{
		(*this)["this"s] = this;	
		UpdateExternalPointers(other.TypeIdInstance());
	}

	Attributed::Attributed(Attributed&& other) noexcept
		: Scope{ forward<Attributed&&>(other) }
	{
		(*this)["this"s] = this;
		UpdateExternalPointers(other.TypeIdInstance());
	}

	Attributed& Attributed::operator=(const Attributed& rhs)
	{
		if (this != &rhs)
		{
			Scope::operator=(rhs);
			(*this)["this"s] = this;
			UpdateExternalPointers(rhs.TypeIdInstance());
		}
		return *this;
	}

	Attributed& Attributed::operator=(Attributed&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Scope::operator=(forward<Attributed&&>(rhs));
			(*this)["this"s] = this;
			UpdateExternalPointers(rhs.TypeIdInstance());
		}
		return *this;
	}

	void Attributed::Populate(IdType typeID)
	{
		(*this)["this"s] = this;
		const Vector<Signature> vector = TypeManager::GetInstance()->_signatureMap.Find(typeID)->second;
		Vector<Signature>::ConstIterator it = vector.begin();
		while (it != vector.end())
		{
			const Signature& signature = *it;
			
			Datum& datum = Append(signature._name);
			if (datum.Type() != Datum::DatumTypes::Unknown && datum.Type() != signature._type)
				throw runtime_error("Incompatible Datum type.");

			if (signature._type == Datum::DatumTypes::Table)
				datum.SetType(Datum::DatumTypes::Table);
			else
			{
				byte* baseAddress = reinterpret_cast<byte*>(this);
				datum.SetStorage(baseAddress + signature._offset, signature._size, signature._type);
			}

			++it;
		}
	}

	void Attributed::UpdateExternalPointers(IdType typeID)
	{
		const Vector<Signature>& signatures = TypeManager::GetInstance()->_signatureMap.Find(typeID)->second;
		Vector<Signature>::ConstIterator it = signatures.begin();

		size_t orderVecIndex = 1;
		while (it != signatures.end())
		{
			const Signature& signature = *it;
			assert(signature._name == _orderVector[orderVecIndex]->first);

			Datum& datum = _orderVector[orderVecIndex]->second;

			if (datum._IsExternal)
			{
				byte* baseAddress = reinterpret_cast<byte*>(this);
				datum.SetStorage(baseAddress + signature._offset, signature._size, signature._type);
			}

			++it;
			++orderVecIndex;
		}
	}

	Datum& Attributed::AppendAuxiliaryAttribute(const string& name)
	{
		auto prescribedAttributes = PrescribedAttributes();
		if(prescribedAttributes.Find(name) != prescribedAttributes.end())
			throw runtime_error("Prescribed attribute already exists with given key.");
		
		return Append(name);
	}

	const Vector<string> Attributed::Attributes() const
	{
		Vector<string> attributes{ _orderVector.Size() };
		for (size_t i = 0; i < _orderVector.Size(); ++i)
			attributes.PushBack(_orderVector[i]->first);
		return attributes;
	}

	const Vector<string> Attributed::PrescribedAttributes() const
	{
		const Vector<Signature>& signatures = TypeManager::GetInstance()->_signatureMap.Find(TypeIdInstance())->second;
		Vector<string> presAttributes{ signatures.Size()};
		for (size_t i = 0; i < signatures.Size(); ++i)
			presAttributes.PushBack(signatures[i]._name);
		return presAttributes;
	}

	const Vector<string> Attributed::AuxiliaryAttributes() const
	{
		const Vector<Signature>& signatures = TypeManager::GetInstance()->_signatureMap.Find(TypeIdInstance())->second;
		Vector<string> auxAttributes{ _orderVector.Size() - signatures.Size() };
		for (size_t i = 1 + signatures.Size(); i < _orderVector.Size(); ++i)
			auxAttributes.PushBack(_orderVector[i]->first);
		return auxAttributes;
	}

	bool Attributed::IsAttribute(const string& name) const
	{
		return name == "this"s || IsPrescribedAttribute(name) || IsAuxiliaryAttribute(name);
	}

	bool Attributed::IsPrescribedAttribute(const string& name) const
	{
		auto presAttributes = PrescribedAttributes();
		return presAttributes.Find(name) != presAttributes.end();
	}

	bool Attributed::IsAuxiliaryAttribute(const string& name) const
	{
		auto auxAttributes = AuxiliaryAttributes();
		return auxAttributes.Find(name) != auxAttributes.end();
	}
}