#include "./header/object.h"
#include "./header/terminal.h"
#include "./header/snake.h"
#include "./header/point.h"
#include "./header/second.h"

#include <vector>
#include <charconv>
#include <thread>


#define KEY_DOWN	0402
#define KEY_UP		0403
#define KEY_LEFT	0404
#define KEY_RIGHT	0405
#define KEY_ENTER	10

int main()
{
	Terminal terminal;
	terminal.init();

	terminal.init_color();
	terminal.block_input(false);

	terminal.register_color(2, Color::WHITE);
	terminal.register_color(3, Color::CYAN);
	terminal.register_color(5, Color::GREEN);
	terminal.register_color(6, Color::RED);
	terminal.register_color(7, Color::YELLOW);

	const int width = terminal.width();
	const int height = terminal.height();

	Object map[width][height];


	Object value;

	for(int x = 0; x < width; ++x)
	{
		value.set_pointer("-", 2);
		value.set_position(x, 0);

		map[x][0] = value;

		value.set_position(x, height -1);
		map[x][height - 1] = value;
	}

	for(int y = 1; y < (height - 1); ++y)
	{
		for(int x = 0; x < width; ++x)
		{
			value.set_position(x, y);

			if(x == 0 || x == (width -1))
			{
				value.set_pointer("|", 2);
			}
			else
			{
				value.set_pointer(" ", 1);
			}

			map[x][y] = value;
		}
	}

	int input = 0;

	int x, y, x_1, y_1;

	bool run = true;
	bool over = false;
	bool point_move = false;

	Snake snake;
	snake.head.set_pointer("*", 2);
	snake.head.set_position(10, 10);

	Point point("#", 2);
	point.init(1, width, 1, height);
	point.set_position(10,15);

	Object score("0", 5);
	score.set_position((width / 2), 1);

	Second second;
	second.get_snake().head.set_pointer("*", 2);
	second.get_snake().head.set_position(10, 15);
	second.set_program_status(run);

	Snake& secondSnake = second.get_snake();

	std::thread pt(second, &point);

	while(run)
	{
		for(int y = 0; y < height; ++y)
		{
			for(int x = 0; x < width; ++x)
			{
				terminal.draw(map[x][y]);
			}
		}

		terminal.draw(point);
		terminal.draw(score);

		terminal.draw(secondSnake.head);
		for(auto& tail : secondSnake.tails)
		{
			terminal.draw (tail);
		}

		terminal.draw(snake.head);
		for(auto& tail : snake.tails)
		{
			terminal.draw(tail);
		}

		if(point_move)
		{
			point.update();
			point_move = false;
		}

		if(snake.head.collision(point))
		{
			if((snake.tails.size() % 2) == 0)
				snake.tails.emplace_back(snake.head.get_pointer(), 7);
			else
				snake.tails.emplace_back(snake.head.get_pointer(), 3);

			int score_int;

			std::string_view point_char = score.get_pointer();
			std::from_chars(point_char.data(), point_char.data() + point_char.size(), score_int);
			
			score_int += 10;

			char point_char_buf[10];
			std::to_chars(point_char_buf,  point_char_buf + 10, score_int);

			score.set_pointer(point_char_buf, score.get_color());

			point_move = true;
		}

		input = terminal.input();

		if(input != -1)
		{
			x = snake.head.get_x();
			y = snake.head.get_y();

			switch(input)
			{
				case KEY_UP:
				{
					if(y > 1)
						snake.head.set_position(x, (y - 1));
					else
						snake.head.set_position(x, (height - 1));
					break;
				}
				case KEY_DOWN:
				{
					if(y < height)
						snake.head.set_position(x, (y + 1));
					else
						snake.head.set_position(x, 1);
					break;
				}
				case KEY_LEFT:
				{
					if(x > 1)
						snake.head.set_position((x - 1), y);
					else
						snake.head.set_position((width - 1), y);
					break;
				}
				case KEY_RIGHT:
				{
					if(x < width)
						snake.head.set_position((x + 1), y);
					else
						snake.head.set_position(1, y);
					break;
				}
				case KEY_ENTER:
				{
					run = false;
					break;
				}

				default: break;
			}

			for(auto& tail : snake.tails)
			{
				if(!snake.head.collision(tail))
				{
					x_1 = tail.get_x();
					y_1 = tail.get_y();

					tail.set_position(x, y);

					x = x_1;
					y = y_1;
				}
				else
				{
					run = false;
					over = true;
				}
			}
		}
		
		input = 0;
		terminal.update();
	}

	if(over)
	{
		terminal.clear();
		terminal.update();
		score.set_pointer("Game Over. Your score: " + score.get_pointer(), 6);
		score.set_position((width / 2) - (score.get_pointer().size() / 2), score.get_y());
		terminal.draw(score);

		terminal.block_input(true);
		terminal.input();
	}

	terminal.close();

	second.set_program_status(false);
	pt.join();

	return 0;
}
