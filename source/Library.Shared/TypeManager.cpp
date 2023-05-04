#pragma once
#include "pch.h"
#include "TypeManager.h"

namespace FieaGameEngine
{
	void TypeManager::CreateInstance()
	{
		if (_instance != nullptr)
			return;

		_instance = new TypeManager();
	}

	TypeManager* TypeManager::GetInstance()
	{
		if (_instance == nullptr)
			CreateInstance();
		return _instance;
	}

	void TypeManager::DestroyInstance()
	{
		if (_instance != nullptr)
			delete(_instance);
	}
}