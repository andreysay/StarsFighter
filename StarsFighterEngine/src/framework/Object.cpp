#include "framework/Object.hpp"
#include "framework/Core.hpp"

namespace SF
{

	Object::~Object()
	{
		WriteLog(GLog, GLoglevel, "Object is being destroyed");
	}
	void Object::Destroy()
	{
		bHasPendingDestroy = true;
	}
}