#ifndef COLLISION_INTERFACE
#define COLLISION_INTERFACE

#include "./istatic.h"

class ICollision
{
	public:

		virtual bool collision(IStatic& object) noexcept = 0;

		virtual ~ICollision() = default;
};

#endif //COLLISION_INTERFACE
