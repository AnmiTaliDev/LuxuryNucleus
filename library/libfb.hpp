namespace Library
{
    class FB
    {
        public:
        unsigned long long column = 0, row = 0, width, height;
        bool newline_at_end;
        void newline();
        void next_column();
        unsigned TwoD_row();
        unsigned TwoD_plus_column(unsigned &);
        unsigned TwoD();
        FB(const unsigned long long width, const unsigned long long height);
    };
}