add_library(debug_logger OBJECT logger.cpp)
target_link_libraries(lnucleus PRIVATE debug_logger)