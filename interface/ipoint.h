#ifndef POINT_INTERFACE
#define POINT_INTERFACE

#include "./iobject.h"

class IPoint : virtual public IObject
{
	public:

		virtual void update() noexcept = 0;

		virtual ~IPoint() = default;

};


#endif //POINT_INTERFACE
