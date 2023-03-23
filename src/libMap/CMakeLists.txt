add_library(Map MapObjectType.cpp Map.cpp MapObject.h)

target_include_directories(Map PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})