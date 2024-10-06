cmake_minimum_required(VERSION 3.28)
project(mark_x C)

set(CMAKE_C_STANDARD 11)

add_executable(mark_x mark_xi/script.c mark_xi/utils/utils.c)
target_link_libraries(mark_x -ljansson)

install(TARGETS mark_x DESTINATION bin)
install(FILES mark_xi/setup-project-bash.sh DESTINATION bin)
install(FILES mark_js/mark.js DESTINATION bin PERMISSIONS WORLD_EXECUTE WORLD_READ OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE)

