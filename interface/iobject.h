#ifndef OBJECT_INTERFACE
#define OBJECT_INTERFACE

#include "./icollision.h"

#include <string>
#include <string_view>

class IObject : public ICollision, public IStatic
{
	public:
		virtual const std::string& get_pointer() const noexcept = 0;
		virtual int get_color() const noexcept = 0;

		virtual ~IObject() = default;
};

#endif //OBJECT_INTERFACE

