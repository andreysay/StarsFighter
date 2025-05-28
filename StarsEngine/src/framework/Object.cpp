#include "framework/Object.hpp"
#include "framework/Core.hpp"
#include "framework/Delegate.hpp"

namespace SF
{

	Object::~Object()
	{
		WriteLog(GLog, GLoglevel, "Object is being destroyed");
	}
	void Object::Destroy()
	{
		OnDestroy.Broadcast(this);
		bHasPendingDestroy = true;
	}
	std::weak_ptr<Object> Object::GetWeakPtr()
	{
		return weak_from_this();
	}
	std::weak_ptr<const Object> Object::GetWeakPtr() const
	{
		return weak_from_this();
	}
}