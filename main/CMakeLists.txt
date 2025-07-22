# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)

idf_component_register(SRCS 
                            "colors.c"
                            "gpio_init.c"
                            "led_controller.c"
                            "main.c"
                            "rgb_controller.c"
                            "rgb.c"
                        INCLUDE_DIRS
                        "."
                        "../include")

