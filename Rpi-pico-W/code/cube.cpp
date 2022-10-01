#include "cube.hpp"


cube::cube() {}

cube::cube(uint32_t size)
{
    __leds.reserve(size);
}

cube::~cube() {}

// Not sure if this should be here
void cube::add_led(led *led)
{
    __leds.push_back(*led);
}

void cube::add_led(led &led)
{
    __leds.push_back(led);
}

void cube::add_led(std::vector<led> &leds)
{
    __leds.insert(__leds.begin(), leds.begin(), leds.end());
}

void cube::add_leds(uint8_t x, uint8_t y, uint8_t z)
{
    led new_led(x, y, z);
    __leds.push_back(new_led);
}

void cube::clr_leds()
{
    __leds.clear();
}

void cube::display()
{
    if (__display_led == 0)
    {
        __display_led = 1;
        __display_start = get_absolute_time();
    }
    if (__display_led == 1 &&  absolute_time_diff_us(__display_start, get_absolute_time()) <= 140)
    {
        __leds.at(__display_led_counter).__on();
    }
    else
    {
        __display_led = 0;
        __leds.at(__display_led_counter).__off();

        ++__display_led_counter;
        if (__display_led_counter >= __leds.size()) __display_led_counter = 0;
    }
}

void cube::display(uint64_t display_time_ms)
{
    if (__display_state == 0)
    {
        __display_state = 1;
        __display_led_time = SCALE_S_TO_US / (__leds.size()*DISPLAY_FREQ);
        __display_time = display_time_ms*SCALE_MS_TO_US;
        __display_start = get_absolute_time();

        /* To prevent from partial display assign value at which all leds turn on at least once*/
        if (__display_time < __display_led_time * __leds.size())
            __display_time = __display_led_time * __leds.size();
    }
    if (absolute_time_diff_us(__display_start, get_absolute_time()) <= __display_time)
    {
        if (__display_led == 0)
        {
            __display_led = 1;
            __display_led_start = get_absolute_time();
        }
        if ( __display_led == 1
            && absolute_time_diff_us(__display_led_start, get_absolute_time()) <= __display_led_time )
        {
            __leds.at(__display_led_counter).__on();
        }
        else
        {
            __display_led = 0;
            __leds.at(__display_led_counter).__off();

            ++__display_led_counter;
            if (__display_led_counter >= __leds.size()) __display_led_counter = 0;
        }
    }
    else
        __display_state = 2;
}

flag cube::get_display_state()
{
    return __display_state;
}

void cube::reset_display_state()
{
    __display_state = 0;
}
