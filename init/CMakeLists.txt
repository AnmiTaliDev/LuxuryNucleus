add_library(init_prepare OBJECT prepare.cpp)
target_link_libraries(LuxuryNucleus PRIVATE init_prepare)

add_library(init_general OBJECT general.cpp)
target_link_libraries(LuxuryNucleus PRIVATE init_general)