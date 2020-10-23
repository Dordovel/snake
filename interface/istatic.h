#ifndef STATIC_INTERFACE
#define  STATIC_INTERFACE

class IStatic
{
	public:

		virtual int get_x() const noexcept = 0;
		virtual int get_y() const noexcept = 0;

		virtual ~IStatic() = default;
};

#endif //STATIC_INTERFACE
