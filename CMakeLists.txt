cmake_minimum_required(VERSION 3.0)
project(BMICalculator)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(BMICalculator main.c window.c application.c)
target_link_libraries(BMICalculator ${GTK3_LIBRARIES})
