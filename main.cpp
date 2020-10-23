#include "./header/object.h"
#include "./header/terminal.h"

#include <vector>
#include <charconv>
#include <random>


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

	terminal.register_color(1, Color::BLACK);
	terminal.register_color(2, Color::WHITE);
	terminal.register_color(3, Color::CYAN);
	terminal.register_color(4, Color::WHITE);
	terminal.register_color(5, Color::GREEN);
	terminal.register_color(6, Color::RED);

	terminal.set_color(1);

	const int width = terminal.width();
	const int height = terminal.height();

	Object map[width][height];

	Object head("*", 3);
	head.set_position(10, 10);

	std::vector<Object> tails;

	Object point("@", 4);
	point.set_position(10,15);

	Object score("0", 5);
	score.set_position((width / 2), 1);


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

	int x;
	int y;

	bool run = true;
	bool over = false;

	std::random_device rd;
	std::uniform_int_distribution<int> uidY(1, (height - 1));
	std::uniform_int_distribution<int> uidX(1, (width - 1));

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
		
		for(auto& tail : tails)
		{
			terminal.draw(tail);
		}

		terminal.draw(head);

		input = terminal.input();

		x = head.get_x();
		y = head.get_y();

		if(head.collision(point))
		{
			tails.emplace_back(head.get_pointer(), head.get_color());
			int score_int;

			std::string_view point_char = score.get_pointer();
			std::from_chars(point_char.data(), point_char.data() + point_char.size(), score_int);
			
			score_int += 10;

			char point_char_buf[3];
			std::to_chars(point_char_buf,  point_char_buf + 3, score_int);

			score.set_pointer(point_char_buf, score.get_color());

			point.set_position(uidX(rd), uidY(rd));
		}

		switch(input)
		{
			case KEY_UP:
			{
				if(y > 1)
					head.set_position(x, y - 1);
				else
					head.set_position(x, height - 1);
				break;
			}
			case KEY_DOWN:
			{
				if(y < height)
					head.set_position(x, y + 1);
				else
					head.set_position(x, 1);
				break;
			}
			case KEY_LEFT:
			{
				if(x > 1)
					head.set_position(x - 1, y);
				else
					head.set_position(width - 1, y);
				break;
			}
			case KEY_RIGHT:
			{
				if(x < width)
					head.set_position(x + 1, y);
				else
					head.set_position(1, y);
				break;
			}
			case KEY_ENTER:
			{
				run = false;
				break;
			}
		}

		for(auto& tail : tails)
		{
			if(!head.collision(tail))
			{
				int x_1 = tail.get_x();
				int y_1 = tail.get_y();

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

		terminal.clear();
		terminal.update();
	}

	if(over)
	{
		terminal.clear();
		terminal.update();
		score.set_pointer("Game Over. Your score: " + score.get_pointer(), score.get_color());
		score.set_position((width / 2) - (score.get_pointer().size() / 2), score.get_y());
		terminal.draw(score);

		terminal.input();
	}

	terminal.close();

	return 0;
}
