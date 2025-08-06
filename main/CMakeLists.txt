# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)

idf_component_register(SRCS 
                            "main.c"
                            "colors.c"
                            "gpio_init.c"
                            "ledc_8bit_lowspeed.c"
                            "rgb_controller.c"
                            "rgb_one_chan_templ.c"
                            "timer.c"
                            "console_init.c"
                            "rgb_cmd.c"
                            "bt.c"
                        INCLUDE_DIRS
                        "."
                        "../include")

