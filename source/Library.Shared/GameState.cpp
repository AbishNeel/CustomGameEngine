#include "GameState.h"

namespace FieaGameEngine
{
	RTTI_DEFINITIONS(GameState);

	GameState::GameState(EventQueue& eventQueue, GameTime& gameTime)
		: _eventQueue{ &eventQueue }, _gameTime{ &gameTime }
	{
	}

	EventQueue& GameState::GetEventQueue() const
	{
		return *_eventQueue;
	}

	GameTime& GameState::GetGameTime() const
	{
		return *_gameTime;
	}
}