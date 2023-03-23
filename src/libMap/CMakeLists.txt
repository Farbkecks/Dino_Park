add_library(Map MapObjectType.cpp Map.cpp MapObject.h MapObject.cpp)

target_include_directories(Map PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Map Dino)