#include <library/libfb.hpp>
using namespace Library;

void FB::newline()
{
    row++;
    column = 0;
}

void FB::next_column()
{
    if (++column == width)
        newline();
}

unsigned FB::TwoD_row()
{
    return row * width;
}

unsigned FB::TwoD_plus_column(unsigned &row)
{
    return row + column;
}

unsigned FB::TwoD()
{
    unsigned row = TwoD_row();
    return TwoD_plus_column(row);
}

FB::FB(const unsigned long long _width, const unsigned long long _height)
{
    width = _width;
    height = _height;
}