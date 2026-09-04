cmake_minimum_required(VERSION 4.0)
project(notebook)

set(CMAKE_CXX_STANDARD 20)

add_executable(notebook
        LinkedList.cpp
        DoubleLinkedList.cpp
        Stack.cpp
        Queue.cpp
        Deque.cpp)
