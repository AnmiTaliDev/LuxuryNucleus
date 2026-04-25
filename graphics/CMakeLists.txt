add_library(video_fbcon OBJECT fbcon.cpp)
target_link_libraries(LuxuryNucleus PRIVATE video_fbcon)