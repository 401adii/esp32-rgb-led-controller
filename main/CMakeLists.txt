# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)

idf_component_register(SRCS 
                            "main.c"
                            "colors.c"
                            "gpio_init.c"
                            "led_controller.c"
                            "rgb_controller.c"
                            "rgb_one_chan_templ.c"
                            "timer.c"
                            "cmd_console.c"
                            "rgb_cmd_manager.c"
                        INCLUDE_DIRS
                        "."
                        "../include")

