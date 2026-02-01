namespace Logging
{
    class buffer_instance
    {
        public:
        char* buffer;
        unsigned buffer_size;
        buffer_instance();
    };
    extern buffer_instance *__buffer_instance;
}