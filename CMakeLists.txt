cmake_minimum_required(VERSION 3.15)
project(OperatingSystems)

set(CMAKE_CXX_STANDARD 20)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread -lrt")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

#add_executable(lab1 lab1/main.cpp)

#add_executable(lab2_task3 lab2/task3.cpp)
#add_executable(lab2_task2_1 lab2/task2_1.cpp lab2/p1.cpp lab2/p2.cpp lab2/p0.cpp)
#add_executable(lab2_task2_2 lab2/task2_2.cpp)
#add_executable(lab2_task4 lab2/task4.cpp)
#add_executable(lab2_p2 lab2/p2.cpp)
#add_executable(lab2_p1 lab2/p1.cpp)
#add_executable(lab2_p0 lab2/p0.cpp)

add_executable(test_cpp test.cpp)
add_executable(test_c test.c)

#add_executable(lab3_tasks_1.2-2.4 lab3/task1.2-2.4.cpp)
#add_executable(lab3_task_3 lab3/task3.cpp)
#add_executable(lab3_task_4 lab3/task4.cpp)
#add_executable(lab3_task_4.1 lab3/task4.1.cpp)
#add_executable(lab3_task_4.2 lab3/task4.2.cpp)

add_executable(lab5_task1.1 lab5/task1.1.cpp)
add_executable(lab5_task1.2 lab5/task1.2.cpp)
add_executable(lab5_task2.1 lab5/task2.1.cpp)
add_executable(lab5_task2.2 lab5/task2.2.cpp)
add_executable(lab5_task3.client lab5/task3.client.cpp)
add_executable(lab5_task3.server lab5/task3.server.cpp)
add_executable(lab5_task4 lab5/task4.cpp)

add_executable(lab6 lab6/task.cpp)
add_executable(varya "lab6/varya_6(11).cpp")