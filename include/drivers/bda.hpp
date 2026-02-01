namespace BDA
{
    enum video_type
    {
        VIDEO_TYPE_NONE = 0x00,
        VIDEO_TYPE_COLOUR = 0x20,
        VIDEO_TYPE_MONOCHROME = 0x30,
    };

    extern enum video_type video_type();
}