#ifndef OBJECT
#define OBJECT

#include "../interface/iobject.h"

class Object : virtual public IObject
{
	private:
		std::string _ch = " ";
		int _x, _y;
		int _color;

	public:
		Object(std::string_view ch, int color);
		Object() = default;

		void set_position(int x, int y) noexcept;
		void set_pointer(std::string_view ch, int color) noexcept;

		int get_x() const noexcept override;
		int get_y() const noexcept override;
		const std::string& get_pointer() const noexcept override;
		int get_color() const noexcept override;

		bool collision(const IStatic& object) noexcept override;
		bool collision(int x, int y) noexcept override;

		~Object() = default;
};

#endif //OBJECT
