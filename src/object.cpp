#include "../header/object.h"

Object::Object(std::string_view ch, int color):_ch(ch), _color(color){}

void Object::set_position(int x, int y) noexcept
{
	this->_x = x;
	this->_y = y;
}

int Object::get_x() const noexcept
{
	return this->_x;
}

int Object::get_y() const noexcept
{
	return this->_y;
}

const std::string& Object::get_pointer() const noexcept
{
	return this->_ch;
}

void Object::set_pointer(std::string_view ch, int color) noexcept
{
	this->_ch = ch;
	this->_color = color;
}

int Object::get_color() const noexcept
{
	return this->_color;
}

bool Object::collision(IStatic& object) noexcept
{
	int x = object.get_x();
	int y = object.get_y();

	return (this->_x == x) && (this->_y == y);
}
