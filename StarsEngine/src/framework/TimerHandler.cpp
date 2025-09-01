/*
*  TimerHandler.cpp
*  StarsEngine
*
*  Created by Andrey Spitsyn 02.06.2025
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#include "framework/TimerHandler.hpp"
#include "framework/Core.hpp"

namespace SF
{
	uint32_t TimerKey::TimerKeyCounter = 0;
	std::unique_ptr<TimerHandler> TimerHandler::TimersHandler{ nullptr };

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
			return;

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
	TimerHandler& TimerHandler::Get()
	{
		if(!TimersHandler)
		{
			TimersHandler = std::unique_ptr<TimerHandler>{ new TimerHandler };
		}
		return *TimersHandler;
	}
	//------------------------------------------------------------------
	void TimerHandler::UpdateTimer(float DeltaTime)
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
	void TimerHandler::ExpireTimer(TimerKey Key)
	{
		auto IterTimer = Timers.find(Key);
		if(IterTimer != Timers.end())
		{
			IterTimer->second.SetExpired();
		}
		else
		{
			auto Message = ("TimerHandler::ExpireTimer: Invalid timer index: %u", Key.GetTimerKey());
			WriteLog(GLog, GLoglevel, Message);
		}
	}
	//------------------------------------------------------------------
	void TimerHandler::EraseExpiredTimers()
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
	TimerHandler::TimerHandler()
	{
	}
	//------------------------------------------------------------------
	TimerKey::TimerKey()
		: Key{ 0 }
	{
	}
}// namespace SF