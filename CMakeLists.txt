set (CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project("Batch GCD" VERSION 1.0)

set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

# Boost
find_package(Boost REQUIRED COMPONENTS system filesystem)
add_definitions( "-lboost_system" )
add_definitions( "-lboost_filesystem" )

# GMP
find_package(GMP REQUIRED)

# Threads
find_package(Threads REQUIRED)

add_executable(batchgcd src/batchgcd.cpp
                        src/utils.cpp)

# add_executable(gmp_overflow src/test/gmp_import_overflow.cpp
#                             src/utils.cpp)

target_link_libraries(batchgcd gmp gmpxx ${Boost_LIBRARIES}
                                         ${CMAKE_THREAD_LIBS_INIT})
# target_link_libraries(gmp_overflow gmp gmpxx ${Boost_LIBRARIES}
#                                              ${CMAKE_THREAD_LIBS_INIT})
