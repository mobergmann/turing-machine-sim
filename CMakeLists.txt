cmake_minimum_required(VERSION 3.25)
project(turing_machine_simulator)

set(CMAKE_CXX_STANDARD 20)

add_library(libtmsim)
target_sources(libtmsim PUBLIC include/tm)
target_compile_features(libtmsim PUBLIC cxx_std_20)
target_include_directories(libtmsim
        PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
)
set_target_properties(libtmsim PROPERTIES LINKER_LANGUAGE CXX)

# build example on option
option(TM_SIM_BUILD_EXAMPLE "Build an example for the turing machine simulator library" OFF)
if (TM_SIM_BUILD_EXAMPLE)
    add_executable(tmsim_example example/main.cpp)
    target_link_libraries(tmsim_example libtmsim)
endif()