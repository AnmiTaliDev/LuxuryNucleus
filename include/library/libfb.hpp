namespace Library
{
    namespace libfb
    {
        class libfb
        {
            public:
            //bool not_newlined_at_end = false;
            unsigned row = 0, column = 0;
            const unsigned &width, &height;
            void _rst_col();
            void newline();
            unsigned _calc_row_pos();
            unsigned _calc_col_pos(const unsigned &__row_pos);
            unsigned TwoDto1D();
            libfb(const unsigned &_width, const unsigned &_height);
        };
    }
}