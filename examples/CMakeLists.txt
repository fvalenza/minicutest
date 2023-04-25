
set( MCU_EXAMPLE_SOURCES
    src/mcu_suite1.c
    src/mcu_main.c

)

add_executable(mcu_example ${MCU_EXAMPLE_SOURCES})

target_include_directories(mcu_example
    PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

target_link_libraries(mcu_example PRIVATE minicutest)
