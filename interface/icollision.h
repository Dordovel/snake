#ifndef COLLISION_INTERFACE
#define COLLISION_INTERFACE

#include "./istatic.h"

class ICollision
{
	public:

		virtual bool collision(const IStatic& object) noexcept = 0;
		virtual bool collision(int x, int y) noexcept = 0;

		virtual ~ICollision() = default;
};

#endif //COLLISION_INTERFACE
