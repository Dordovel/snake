#include "../header/terminal.h"

#include <ncurses.h>

void Terminal::init() noexcept
{
    initscr();

	keypad(stdscr, true);
	noecho();
	curs_set(0);
}

void Terminal::init_color() noexcept
{
	start_color();
}

void Terminal::register_color(int index, Color color) noexcept
{
	init_pair(index, color, COLOR_BLACK);
}

void Terminal::set_color(int color) noexcept
{
	bkgd(COLOR_PAIR(color));
}

void Terminal::update() noexcept
{
	refresh();
}

void Terminal::close() noexcept
{
	endwin();
}

void Terminal::clear() noexcept
{
	erase();
}

int Terminal::width() const noexcept
{
	return getmaxx(stdscr);
}

int Terminal::height() const noexcept
{
	return getmaxy(stdscr);
}

int Terminal::input() const noexcept
{
	return getch();
}

void Terminal::block_input(bool flag) noexcept
{
	nodelay(stdscr, !flag);
}

void Terminal::draw(IObject& object) noexcept
{
	move(object.get_y(), object.get_x());

	attron(COLOR_PAIR(object.get_color()));
	addstr(object.get_pointer().data());
	attroff(COLOR_PAIR(object.get_color()));
}
