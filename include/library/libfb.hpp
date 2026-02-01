namespace Library
{
    namespace libfb
    {
        class libfb
        {
            public:
            unsigned row, column, width;
            void _rst_col();
            void newline();
            unsigned _calc_row_pos();
            unsigned _calc_col_pos(const unsigned &__row_pos);
            unsigned D2toD1();
            libfb(const unsigned &_width);
        };
    }
}