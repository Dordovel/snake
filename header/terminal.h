#ifndef TERMINAL
#define TERMINAL

#include "../interface/iobject.h"
#include "../color.h"

class Terminal
{
	public:
		Terminal() = default;
		Terminal(const Terminal&) = delete;
		Terminal& operator= (const Terminal&) = delete;

		Terminal(Terminal&&) = default;
		Terminal& operator=(Terminal&&) = default;

		void draw(IObject& object) noexcept;

		int width() const noexcept;
		int height() const noexcept;

		void init() noexcept;
		void init_color() noexcept;
		void set_color(int color) noexcept;
		void update() noexcept;
		void close() noexcept;
		void clear() noexcept;

		void register_color(int index, Color color) noexcept;

		int input() const noexcept;

		~Terminal() = default;
};

#endif //TERMINAL
