cmake_minimum_required(VERSION 3.28)
project(mark_x C)

set(CMAKE_C_STANDARD 11)

add_executable(mark_x mark_xi/script.c mark_xi/utils/utils.c)
target_link_libraries(mark_x -ljansson)
add_executable(mark main.c)

install(TARGETS mark_x DESTINATION bin/mark_xi)
install(TARGETS mark DESTINATION bin)
install(FILES mark_xi/setup.sh DESTINATION bin/mark_xi PERMISSIONS WORLD_EXECUTE WORLD_READ WORLD_WRITE OWNER_READ OWNER_EXECUTE OWNER_WRITE GROUP_READ GROUP_EXECUTE GROUP_WRITE)
install(FILES mark_js/mark.js DESTINATION bin/mark_xi PERMISSIONS WORLD_EXECUTE WORLD_READ OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE)
install(DIRECTORY mark_xi/skeletons DESTINATION bin/mark_xi)
install(DIRECTORY mark_xi/templates DESTINATION bin/mark_xi)

