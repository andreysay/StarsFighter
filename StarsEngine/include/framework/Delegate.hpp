#pragma once
#include <functional>
#include <memory>
//#include "framework/Object.hpp"

namespace SF
{
	class Object;
	//! Delegate class for event handling
	template<typename... Args>
	class Delegate
	{
	public:
		template<typename ClassName>
		void BindDelegate(std::weak_ptr<Object> ObjPtr, void(ClassName::*Callback)(Args...))
		{
			std::function<bool(Args...)> NewCallback = [ObjPtr, Callback](Args... ArgsList) -> bool
			{
				if (!ObjPtr.expired())
				{
					if (auto Obj = ObjPtr.lock())
					{
						(static_cast<ClassName*>(Obj.get())->*Callback)(ArgsList...);
						return true; // Callback executed successfully
					}
					return false; // Object is no longer valid
				}
			};
			DelegateCallbacks.push_back(NewCallback);
		}

		void Broadcast(Args... InArgs)
		{
			for (auto Iter = DelegateCallbacks.begin(); Iter != DelegateCallbacks.end();)
			{
				if ((*Iter)(InArgs...))
				{
					++Iter; // Move to the next callback
				}
				else
				{
					// If the callback not valid, remove it
					Iter = DelegateCallbacks.erase(Iter);
				}
			}
		}

	private:
		std::vector<std::function<bool(Args...)>> DelegateCallbacks;
	};
}