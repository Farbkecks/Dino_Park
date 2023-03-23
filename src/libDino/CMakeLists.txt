add_library(Dino Dino.cpp Herbivore.cpp Carnivore.cpp DinoNames.h)
target_include_directories(Dino PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Dino Map)