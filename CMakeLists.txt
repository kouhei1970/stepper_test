cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(stepper_test C CXX ASM)
set(CMAKE_C_STNDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})
pico_sdk_init()
add_executable(
  stepper_test
  stepper_test.cpp)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(
  stepper_test 
  pico_stdlib 
  hardware_pwm)

# create map/bin/hex file etc.
pico_add_extra_outputs(stepper_test)
