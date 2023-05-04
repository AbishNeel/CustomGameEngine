#pragma once
#include "RTTI.h"
#include "EventQueue.h"
#include "GameTime.h"

namespace FieaGameEngine
{
	class GameState final : public RTTI
	{
		RTTI_DECLARATIONS(GameState, RTTI);

	public:
		GameState(EventQueue& eventQueue, GameTime& gameTime);

		EventQueue& GetEventQueue() const;

		GameTime& GetGameTime() const;

	private:
		EventQueue* _eventQueue;
		GameTime* _gameTime;
	};
}