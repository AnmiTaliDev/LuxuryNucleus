#include <library/libfb.hpp>
using namespace Library;

void FB::newline()
{
    row++;
    column = 0;
}

void FB::next_column()
{
    if (column++ == width)
        newline();
}

unsigned FB::TwoD_row()
{
    return row * width;
}

unsigned FB::TwoD_plus_column(volatile unsigned &row)
{
    return row + column;
}

unsigned FB::TwoD()
{
    volatile unsigned row = TwoD_row();
    return TwoD_plus_column(row);
}

FB::FB(const unsigned width_, const unsigned height_)
{
    width = width_;
    height = height_;
    column = 0;
    row = 0;
}