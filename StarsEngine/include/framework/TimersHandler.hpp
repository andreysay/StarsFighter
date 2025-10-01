/*
*  TimerHandler.hpp
*  StarsEngine
*
*  Created by Andrey Spitsyn 02.06.2025
*  Copyright 2025 Nesstronic. All rights reserved.
*/
#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include "framework/Object.hpp"

namespace SF
{
	//! Unique key for identifying timers
	struct TimerKey
	{
		TimerKey();
		bool operator==(const TimerKey& Other) const { return Key == Other.Key; } // Comparison operator for TimerKey
		uint32_t GetTimerKey() const { return Key; }
	private:
		uint32_t Key{}; // Unique key for the timer
		static uint32_t TimerKeyCounter; // Counter to generate unique keys
		static uint32_t GenerateTimerKey() { return ++TimerKeyCounter; } // Function to generate unique keys
	};

	struct TimerKeyHash
	{
		std::size_t operator()(const TimerKey& Key) const noexcept
		{
			return std::hash<uint32_t>()(Key.GetTimerKey());
		}
	};

	//! Timer class that holds a weak pointer to an object and a callback function to be executed after a certain time interval
	struct Timer
	{
		Timer() = delete;
		//! Default constructor for Timer
		Timer(std::weak_ptr<Object> InObjectWeakPtr, std::function<void()> InCallback, float InTimeInterval, bool bInRepeated = false);
		//! Runs a timer on delta time
		void TickTime(float DeltaTime);
		//! Checks if the timer is expired
		bool Expired() const;
		//! Set the timer expired
		void SetExpired();

	private:
		std::pair<std::weak_ptr<Object>, std::function<void()>> TimeListener; // Weak pointer to the object that owns the timer
		float TimeInterval{}; // Time interval for the timer
		bool bRepeated; // Whether the timer is repeated or not
		float TimeElapsed{};
		bool bExpired = false; // Whether the timer has expired or not
	};

	class TimersHandler
	{
	public:
		~TimersHandler() = default;
		TimersHandler(const TimersHandler&) = delete;
		TimersHandler& operator=(const TimersHandler&) = delete;
		TimersHandler(TimersHandler&&) = delete;
		TimersHandler& operator=(TimersHandler&&) = delete;
		//! Returns the singleton instance of TimerHandler
		static TimersHandler& Get();
		//! Registers a timer with a callback function and time interval
		//! Returns the index of the timer
		template<typename ClassName>
		TimerKey RegisterTimer(std::weak_ptr<Object> ObjWeakPtr, void (ClassName::*Callback)(), float InTimeInterval, bool bInRepeated = false)
		{
			TimerKey NewKey{};
			Timers.insert({ NewKey, Timer(ObjWeakPtr, [=] { (static_cast<ClassName*>(ObjWeakPtr.lock().get())->*Callback)(); }, InTimeInterval, bInRepeated) });
			return NewKey; // Return the index of the timer
		}

		void UpdateTimer(float DeltaTime);
		void ExpireTimer(TimerKey Key);
		void EraseExpiredTimers();

	protected:
		TimersHandler();


	private:
		static std::unique_ptr<TimersHandler> GameTimersManager;
		std::unordered_map<TimerKey, Timer, TimerKeyHash> Timers;
	};
}
