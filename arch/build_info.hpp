namespace Information
{
    namespace Build
    {
        extern const volatile char
            *const volatile Architecture,
            *const volatile ExecFileType,
            *const volatile BuildDate = __DATE__,
            *const volatile BuildTime = __TIME__;
    }
}