#ifndef SECOND
#define SECOND

#include "./snake.h"
#include "../header/point.h"

class Second
{
    private:
        Snake _snake;
        bool _status;
        Second* _pointer;

    public:
        Second();

        void set_program_status(bool status) noexcept;

        void operator()(Point* point) noexcept;

        Snake& get_snake() noexcept;

        ~Second() = default;
};

#endif //SECOND
