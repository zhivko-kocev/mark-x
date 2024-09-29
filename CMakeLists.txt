cmake_minimum_required(VERSION 3.29)
project(mark_x C)

set(CMAKE_C_STANDARD 11)

add_executable(mark_x main.c)

install(TARGETS mark_x DESTINATION bin)
install(FILES setup-project-bash.sh setup-project-zsh.sh DESTINATION bin)
