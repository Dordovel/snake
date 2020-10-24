#ifndef POINTER
#define POINTER

#include "./object.h"
#include "../interface/ipoint.h"

#include <random>

class Point : public Object, public IPoint
{
	private:
		std::random_device _rd;
		std::uniform_int_distribution<int> _uidY;
		std::uniform_int_distribution<int> _uidX;

	public:
		Point(std::string_view pointer, int color);
		Point() = default;

		void init(int x, int width, int y, int height) noexcept;

		void update() noexcept override;

		~Point() = default;
};


#endif //POINTER
