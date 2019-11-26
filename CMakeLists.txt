cmake_minimum_required(VERSION 3.13.4 FATAL_ERROR)
project("Batch GCD" VERSION 1.0)

set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

# Boost
find_package(Boost REQUIRED COMPONENTS system filesystem)
add_definitions( "-lboost_system" )
add_definitions( "-lboost_filesystem" )

# GMP
find_package(GMP REQUIRED)

add_executable(batchgcd src/batchgcd.cpp
                        src/utils.cpp)

target_link_libraries(batchgcd gmp gmpxx ${Boost_LIBRARIES})

# enable_testing()
# add_test(test batchgcd)
