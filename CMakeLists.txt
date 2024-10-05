cmake_minimum_required(VERSION 3.28)
project(mark_x C)

set(CMAKE_C_STANDARD 11)

add_executable(mark_x mark_xi/script.c mark_xi/utils/utils.c)
target_link_libraries(mark_x -ljansson)
#add_executable(mark main.c)

#install(TARGETS mark_x DESTINATION bin)
#install(FILES setup-project-bash.sh DESTINATION bin)
