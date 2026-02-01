#include <library/libfb.hpp>
using namespace Library::libfb;

void libfb::_rst_col()
{
    column = 0;
}

void libfb::newline()
{
    _rst_col();
    row++;
}

unsigned libfb::_calc_row_pos()
{
    return row * width;
}

unsigned libfb::_calc_col_pos(const unsigned &__row_pos)
{
    return __row_pos + column;
}

unsigned libfb::D2toD1()
{
    return _calc_col_pos(_calc_row_pos());
}

libfb::libfb(const unsigned &_width):row(0),column(0)
{
    width = _width;
}