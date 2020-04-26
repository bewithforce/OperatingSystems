cmake_minimum_required(VERSION 3.15)
project(OperatingSystems)

set(CMAKE_CXX_STANDARD 20)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread -lrt")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

#add_executable(lab1 lab1/main.cpp)

#add_executable(task3 lab2/task3.cpp)
#add_executable(task2_1 lab2/task2_1.cpp lab2/p1.cpp lab2/p2.cpp lab2/p0.cpp)
#add_executable(task2_2 lab2/task2_2.cpp)
#add_executable(task4 lab2/task4.cpp)
#add_executable(p2 lab2/p2.cpp)
#add_executable(p1 lab2/p1.cpp)
#add_executable(p0 lab2/p0.cpp)

add_executable(test_cpp test.cpp)
add_executable(test_c test.c)

add_executable(lab3_tasks_1.2-2.4 lab3/task1.2-2.4.cpp)
add_executable(lab3_task_3 lab3/task3.cpp)
add_executable(lab3_task_4 lab3/task4.cpp)
add_executable(lab3_task_4.1 lab3/task4.1.cpp)
add_executable(lab3_task_4.2 lab3/task4.2.cpp)

