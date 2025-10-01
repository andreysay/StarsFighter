/*
*  TimerHandler.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn 02.06.2025
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "framework/TimersHandler.hpp"
#include "framework/Core.hpp"

namespace SF
{
	uint32_t TimerKey::TimerKeyCounter = 0;
	std::unique_ptr<TimersHandler> TimersHandler::GameTimersManager{ nullptr };

	//----------------------------------------------------------------------
	Timer::Timer(std::weak_ptr<Object> InObjectWeakPtr, std::function<void()> InCallback, float InTimeInterval, bool bInRepeated)
		: TimeListener{ InObjectWeakPtr, InCallback }
		, TimeInterval{ InTimeInterval }
		, bRepeated{ bInRepeated }
		, TimeElapsed{ 0.0f }
	{
	}
	//------------------------------------------------------------------
	void Timer::TickTime(float DeltaTime)
	{
		if (Expired())
		{
			auto Message = ("Timer is expired!");
			WriteLog(GLog, GLoglevel, Message);
			return;
		}

		TimeElapsed += DeltaTime;
		if(TimeElapsed >= TimeInterval)
		{
			TimeListener.second();
			if(bRepeated)
			{
				TimeElapsed = 0.0f;
			}
			else
			{
				SetExpired();
			}
		}
	}
	//------------------------------------------------------------------
	bool Timer::Expired() const
	{
		return bExpired || TimeListener.first.expired() || TimeListener.first.lock()->IsPendingDestroy();
	}
	//------------------------------------------------------------------
	void Timer::SetExpired()
	{
		bExpired = true;
	}
	//------------------------------------------------------------------
	TimersHandler& TimersHandler::Get()
	{
		if(!GameTimersManager)
		{
			GameTimersManager = std::unique_ptr<TimersHandler>{ new TimersHandler };
		}
		return *GameTimersManager;
	}
	//------------------------------------------------------------------
	void TimersHandler::UpdateTimer(float DeltaTime)
	{
		for (auto& [index, LTimer] : Timers)
		{
			if (!LTimer.Expired())
			{
				LTimer.TickTime(DeltaTime);
			}
		}
	}
	//------------------------------------------------------------------
	void TimersHandler::ExpireTimer(TimerKey Key)
	{
		auto IterTimer = Timers.find(Key);
		if(IterTimer != Timers.end())
		{
			IterTimer->second.SetExpired();
		}
		else
		{
			auto Message = ("TimersHandler::ExpireTimer: Invalid timer index: %u", Key.GetTimerKey());
			WriteLog(GLog, GLoglevel, Message);
		}
	}
	//------------------------------------------------------------------
	void TimersHandler::EraseExpiredTimers()
	{
		for(auto TimerIter = Timers.begin(); TimerIter != Timers.end();)
		{
			if(TimerIter->second.Expired())
			{
				TimerIter = Timers.erase(TimerIter);
			}
			else
			{
				++TimerIter;
			}
		}
	}
	//----------------------------------------------------------------------
	TimersHandler::TimersHandler()
	{
	}
	//------------------------------------------------------------------
	TimerKey::TimerKey()
		: Key{ GenerateTimerKey() }
	{
	}
}// namespace SF