#include "../header/second.h"
#include <thread>

void Second::set_program_status(bool status) noexcept
{
    this->_status = status;
}

Second::Second():_pointer(this){}

void Second::operator()(Point* point) noexcept
{
    int x, y, x_1, y_1;

    while(this->_pointer->_status)
    {
        x = this->_pointer->_snake.head.get_x();
        y = this->_pointer->_snake.head.get_y();
        
        if(!this->_pointer->_snake.head.collision(*point))
        {
            x_1 = point->get_x();
            y_1 = point->get_y();

            if(!this->_pointer->_snake.tails.empty())
            {
                for(auto& tail : this->_pointer->_snake.tails)
                {
                    if(x > x_1)
                    {
                        if(!tail.collision((x - 1), y))
                        {
                            this->_pointer->_snake.head.set_position(x - 1, y);
                        }
                    }
                    if(x < x_1)
                    {
                        if(!tail.collision((x + 1), y))
                        {
                            this->_pointer->_snake.head.set_position((x + 1), y);
                        }
                    }
                    if(y > y_1)
                    {
                        if(!tail.collision(x, (y - 1)))
                        {
                            this->_pointer->_snake.head.set_position(x, (y - 1));
                        }
                    }
                    if(y < y_1)
                    {
                        if(!tail.collision(x, (y + 1)))
                        {
                            this->_pointer->_snake.head.set_position(x, (y + 1));
                        }
                    }

                    x_1 = tail.get_x();
                    y_1 = tail.get_y();

                    tail.set_position(x, y);

                    x = x_1;
                    y = y_1;
                }
            }
            else
            {
                if(x > x_1)
                {
                    this->_pointer->_snake.head.set_position(x - 1, y);
                }
                if(x < x_1)
                {
                    this->_pointer->_snake.head.set_position((x + 1), y);
                }
                if(y > y_1)
                {
                    this->_pointer->_snake.head.set_position(x, (y - 1));
                }
                if(y < y_1)
                {
                    this->_pointer->_snake.head.set_position(x, (y + 1));
                }
            }
            
        }
        else
        {
            if((this->_pointer->_snake.tails.size() % 2) == 0)
                this->_pointer->_snake.tails.emplace_back(this->_pointer->_snake.head.get_pointer(), 7);
            else
                this->_pointer->_snake.tails.emplace_back(this->_pointer->_snake.head.get_pointer(), 3);

            point->update();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }
}

Snake& Second::get_snake() noexcept
{
    return this->_snake;
}
