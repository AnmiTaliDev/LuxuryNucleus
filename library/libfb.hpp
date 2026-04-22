namespace Library
{
    class FB
    {
        public:
        unsigned column, row, width, height;
        void newline();
        void next_column();
        unsigned TwoD_row();
        unsigned TwoD_plus_column(volatile unsigned &);
        unsigned TwoD();
        FB(const unsigned, const unsigned);
    };
}