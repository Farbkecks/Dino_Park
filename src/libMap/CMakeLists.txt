add_library(Map MapObjectType.h Map.cpp MapObject.h)

target_include_directories(Map PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})