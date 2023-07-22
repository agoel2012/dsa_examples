cmake_minimum_required(VERSION 3.16)

project(QueueExamples)

include_directories(include)
add_executable(TaskScheduler task_scheduler.cpp)
target_compile_options(TaskScheduler PRIVATE -g -O3 -Werror -Wall)
target_compile_features(TaskScheduler PRIVATE cxx_std_17)
add_executable(FurthestPeak furthest_peak.cpp)
target_compile_options(FurthestPeak PRIVATE -g -O3 -Werror -Wall)
add_executable(TrappingWater2 trapping_water2.cpp)
target_compile_options(TrappingWater2 PRIVATE -g -O3 -Werror -Wall)
