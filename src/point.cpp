#include "../header/point.h"

void Point::init(int x, int width, int y, int height) noexcept
{
	this->_uidX = decltype(this->_uidX)(x, width);
	this->_uidY = decltype(this->_uidY)(y, height);
}

Point::Point(std::string_view pointer, int color):Object(pointer, color)
{
}

void Point::update() noexcept
{
	this->set_position(this->_uidX(this->_rd), this->_uidY(this->_rd));
}

void update() noexcept;
